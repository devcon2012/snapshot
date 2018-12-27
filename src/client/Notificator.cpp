/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notificator.cpp
 * Author: klaus
 * 
 * Created on 2. Dezember 2018, 12:35
 */

#include "Notificator.hpp"
#include <iostream>
#include <thread>

void Notificator::_init()
    {
    notifyfd = inotify_init() ;
    fill = 0 ;
    cursor = NULL ;
    }

Notificator::Notificator()
    {
    _init() ;
    }

Notificator::Notificator(const char * p)
    {
    _init() ;
    AddPath(p) ;
    }

Notificator::Notificator(const path_t &p)
    {
    _init() ;
    AddPath(p) ;
    }

Notificator::Notificator(const Notificator& orig)
    {
    throw "TODO" ;
    }

void Notificator::AddPath(const char * path)
    {
    int wd = inotify_add_watch(notifyfd, path, IN_ALL_EVENTS);
    
    if (wd == -1) 
        {
        perror("inotify_add_watch") ;
        }
    else
        {
        wdmap[wd] = std::string(path) ;
        }
    }

inotify_event_t * Notificator::NextEvent()
    {
    if ( ! cursor || (cursor >= buf + fill) )
        {
        fill = read(notifyfd, buf, BUF_LEN);
        if (fill <= 0) 
            {
            fprintf(stderr, "read() from inotify fd returned <= 0!");
            exit(EXIT_FAILURE);
            }
        cursor = buf ;
        }
    auto event = (inotify_event_t *) cursor ;
    cursor += sizeof(struct inotify_event) + event->len;
    // std::cerr << "Event " << event->len << " bytes \n" ;
    return event ;
    }

        
void Notificator::AddPath(const path_t &p)
    {
    AddPath( p.c_str() ) ;
    }

Notificator::~Notificator()
    {
    close(notifyfd) ;
    }

const path_t * Notificator::GetCookiePath(uint32_t cookie)
    {
    auto p = cookiemap.find(cookie) ;
    if ( p == cookiemap.end() )
        return NULL ;
    else
        return & ( p->second ) ;
    }

void Notificator::SetCookiePath(uint32_t cookie, const path_t * path) 
    {
    if(path)
        cookiemap.emplace(cookie, *path) ;
    else
        cookiemap.erase(cookie) ;
    }

NotifyEventReader::NotifyEventReader()
    {
    }

NotifyEventReader::~NotifyEventReader() 
    {
    }

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))
void NotifyEventReader::ReadEvents(Notificator &n)
    {
    static Context c {this, &n };
    t = new std::thread(NotifyEventReader::Runner, &c) ;
    
    }

void NotifyEventReader::OnClose(int wd, const path_t &p)
    {
    // std::cerr << "Close: " << p.c_str() << std::endl ;
    }

void NotifyEventReader::OnCreate(int wd, const path_t &p)
    {
    // std::cerr << "Create: " << p.c_str() << std::endl ;
    }

void NotifyEventReader::OnDelete(int wd, const path_t &p)
    {
    // std::cerr << "Delete: " << p.c_str() << std::endl ;
    }

void NotifyEventReader::OnMove(int wd, const path_t &from, const path_t &to)  
    {
    // std::cerr << "Move: " << from.c_str() << " to " << to.c_str() << std::endl ;
    }

void NotifyEventReader::Runner(NotifyEventReader::Context *c) 
    {
    NotifyEventReader *self = c->self ;
    Notificator *n = c->n ;
    self->run = true ;
    while(self->run)
        {
        auto event = n->NextEvent() ;
        int wd = event -> wd ;
        
        // DumpEvent ( event ) ;
        path_t path ; 
        if (event->len)
            path = path_t(event->name) ;
        
        if (event->mask & IN_CLOSE_WRITE)
            self->OnClose(wd, path);
        if (event->mask & IN_CREATE)
            self->OnCreate(wd, path);
        if (event->mask & IN_DELETE)
            self->OnDelete(wd, path);
        if (event->mask & IN_MOVED_FROM)
            {
            auto old = n->cookiemap.find(event->cookie) ;
            if ( old == n->cookiemap.end() )
                {
                n->cookiemap.emplace(event->cookie, path) ;
                }
            else
                {
                self->OnMove(wd, path, old->second);
                }
            }
        if (event->mask & IN_MOVED_TO)
            {
            auto old = n->cookiemap.find(event->cookie) ;
            if ( old == n->cookiemap.end() )
                {
                n->cookiemap.emplace(event->cookie, path) ;
                }
            else
                {
                self->OnMove(wd, old->second, path);
                }
            }
        }    
    }


void NotifyEventReader::Stop() 
    { 
    run = false ;
    t->join() ;
    delete t;
    t=NULL ;
    }

void NotifyEventReader::DumpEvent( inotify_event_t *e )
    { 
    std::cerr << "Event: '" << (e->len>0 ? e->name : "" ) << "' wd:"
            << e->wd << " c:" << e->cookie << " "
            << ( e->mask & IN_ACCESS        ?  "ACC "       : "" )
            << ( e->mask & IN_ATTRIB        ?  "ATTR "      : "" )
            << ( e->mask & IN_CLOSE_NOWRITE ?  "CLOSE "     : "" )
            << ( e->mask & IN_CLOSE_WRITE   ?  "CLOSE_W "   : "" )
            << ( e->mask & IN_CREATE        ?  "CREA "      : "" )
            << ( e->mask & IN_DELETE        ?  "DEL "       : "" )
            << ( e->mask & IN_DELETE_SELF   ?  "DELS "      : "" )
            << ( e->mask & IN_IGNORED       ?  "IGN "       : "" )
            << ( e->mask & IN_ISDIR         ?  "ISDIR "     : "" )
            << ( e->mask & IN_MODIFY        ?  "MOD "       : "" )
            << ( e->mask & IN_MOVE_SELF     ?  "MOV_S "     : "" )
            << ( e->mask & IN_MOVED_FROM    ?  "MOV_F "     : "" )
            << ( e->mask & IN_MOVED_TO      ?  "MOV_T "     : "" )
            << ( e->mask & IN_OPEN          ?  "OPN "       : "" )
            << ( e->mask & IN_Q_OVERFLOW    ?  "Q_OVR "     : "" )
            << ( e->mask & IN_UNMOUNT       ?  "UMOUNT "    : "" )
            << "\n" ;
    }
