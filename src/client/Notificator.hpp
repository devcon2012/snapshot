/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notificator.hpp
 * Author: klaus
 *
 * Created on 2. Dezember 2018, 12:35
 */

#ifndef NOTIFICATOR_HPP
#define NOTIFICATOR_HPP

#include <sys/inotify.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <boost/filesystem.hpp>
#include <thread>
#include <map>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

typedef struct inotify_event inotify_event_t ;
typedef boost::filesystem::path path_t ;

class NotifyEventReader ;

class Notificator 
    {
    friend class NotifyEventReader ;
    public:
        Notificator();
        Notificator(const char *path);
        Notificator(const path_t &path);
        Notificator(const Notificator& orig);
        virtual ~Notificator();

        void AddPath(const char * path) ;
        void AddPath(const path_t &path) ;
        void RemovePath(const char * path) ;
        void RemovePath(const path_t &path) ;
        
        inotify_event_t * NextEvent() ;
        
        const path_t * GetCookiePath(uint32_t cookie) ;
        void SetCookiePath(uint32_t cookie, const path_t *) ;
        std::string GetPath(int wd) {return wdmap[wd]; }
    private:
        int notifyfd ;
        void _init() ;
        char buf[BUF_LEN] , *cursor ;
        int fill ;
        std::map<int, std::string> wdmap;
        std::map<uint32_t, const path_t> cookiemap;
    } ;

class NotifyEventReader 
    {    
    public:
        NotifyEventReader() ;
        virtual ~NotifyEventReader() ;

        void ReadEvents(Notificator &n) ;

        virtual void OnClose(int wd, const path_t &p) ;
        virtual void OnCreate(int wd, const path_t &p) ;
        virtual void OnDelete(int wd, const path_t &p) ;
        virtual void OnMove(int wd, const path_t &from, const path_t &to) ;
    
        void Stop() ;
        static void DumpEvent( inotify_event_t *e ) ;
    protected:
        typedef struct 
            {
            NotifyEventReader *self ;
            Notificator *n ;
            } Context ;
        bool run ;
        std::thread *t;
        static void Runner(Context *c) ;
    } ;

#endif /* NOTIFICATOR_HPP */
