/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotClient.cpp
 * Author: klaus
 * Snapshot Controler -Connect Model and View
 * 
 * Created on 25. Dezember 2017, 21:01
 */

#include "SnapshotClient.hpp"
#include <wx/wx.h>

wxIMPLEMENT_APP(SnapshotClient);

SnapshotClient::SnapshotClient()
    {
    Init();
    }

SnapshotClient::SnapshotClient(int argc, char** argv)
    {
    Init();
    }

SnapshotClient::SnapshotClient(const SnapshotClient& orig)
    {
    Init();
    }

SnapshotClient::~SnapshotClient()
    {
    Cleanup();
    }

/// Init - NULL all pointers etc.
void SnapshotClient::Init()
    {
    m_pView     = NULL ;
    m_pConfig   = NULL ;
    const char * base = ( getenv("HOME") ? getenv("HOME") : "" ) ;
    m_sConfigFilename = std::string(base) + "/.snapshotclient" ;
    }

/// Cleanup - delete all pointers etc.
void SnapshotClient::Cleanup()
    {
    if ( m_pView )
        {
        delete m_pView ;
        m_pView = NULL ;
        }
    if ( m_pConfig )
        {
        m_pConfig -> Save(m_sConfigFilename) ;
        delete m_pConfig ;
        m_pConfig = NULL ;
        } 
    }

int SnapshotClient::OnExit()
    {
    Cleanup() ;
    exit(0) ;
    }

int SnapshotClient::Run()
    {
    return 0;
    }

bool SnapshotClient::OnInit()
    {
    wxImage::AddHandler(new wxPNGHandler()) ;
    
    m_pView = new SnapshotView(0, NULL ) ; 
    m_pView -> UpdateStatus("Not connected") ;
    m_pView -> Show(true) ;
    
    m_pConfig = new SnapshotConfig() ;
    m_pConfig -> InitClientDefaults() ;
    try {
        m_pConfig -> Load(m_sConfigFilename) ;
        }
    catch(...)
        {
        // cannot read config, maybe nonexistent?
        }
    
    return true ;
    }
