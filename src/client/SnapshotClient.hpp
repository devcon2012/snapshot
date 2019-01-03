/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotClient.hpp
 * Author: klaus
 *
 * Created on 25. Dezember 2017, 21:01
 */

#ifndef SNAPSHOTCLIENT_HPP
#define SNAPSHOTCLIENT_HPP

#include <wx/wx.h>

#include "SnapshotView.hpp"
#include "SnapshotData.hpp"
#include "SnapshotSettings.hpp"
#include "../common/SnapshotConfig.hpp"
#include "SnapshotConnector.hpp"

wxDECLARE_EVENT(wxEVT_DO_EVENT, wxCommandEvent);

#define EVT_DO_EVENT(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( \
        wxEVT_DO_EVENT, id, wxID_ANY, \
        wxCommandEventHandler(fn), \
        (wxObject *) NULL \
    ),

wxDECLARE_EVENT(wxEVT_ERR_EVENT, wxCommandEvent);

#define EVT_ERR_EVENT(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( \
        wxEVT_ERR_EVENT, id, wxID_ANY, \
        wxCommandEventHandler(fn), \
        (wxObject *) NULL \
    ),

wxDECLARE_EVENT(wxEVT_STATE_UPDATE_EVENT, wxCommandEvent);

#define EVT_STATE_UPDATE_EVENT(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( \
        wxEVT_STATE_UPDATE_EVENT, id, wxID_ANY, \
        wxCommandEventHandler(fn), \
        (wxObject *) NULL \
    ),

class SnapshotClient : public wxApp
    {
public:
    SnapshotClient() ;
    SnapshotClient(int argc, char** argv ) ;
    SnapshotClient(const SnapshotClient& orig) ;
    virtual ~SnapshotClient() ;
    int Run() ;
    SnapshotView * View() {return m_pView ;}
    virtual bool OnInit();
    virtual int OnExit();

    void OnError(wxCommandEvent& event) ;

    static SnapshotClient * GetDefault() { return m_pDefault; }
    static void PostError(const std::exception &e, const std::string & sMore = std::string()) ;
    static void PostUpdateServerState(const char *state) ;
    
    /// These event named DoXXX - they are triggered by the View, not the user
    void DoConnect(wxCommandEvent& event) ;
    void DoSync(wxCommandEvent& event) ;
    
private:
    void                    Init() ;
    void                    Cleanup() ;

    std::string             m_sConfigFilename ;
    std::string             m_sCertFilename ;
    std::string             m_sKeyFilename ;
    std::string             m_sPasswd ;
    SnapshotView          * m_pView ;
    SnapshotConfig        * m_pConfig ;
    KeyPasswdDialog       * m_pPasswd ;
    SnapshotConnector     * m_pConnector ;
    static SnapshotClient        * m_pDefault ;
    
    wxDECLARE_EVENT_TABLE();
 
    };
        
extern class SnapshotClient *pApp ;

#endif /* SNAPSHOTCLIENT_HPP */

