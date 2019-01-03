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
#include <wx/msgdlg.h>
#include "../common/GenericException.hpp"

#define ClientError(x)  GenericException(x, __FUNCTION__,  __FILE__, __LINE__ )


wxDEFINE_EVENT(wxEVT_DO_EVENT, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_ERR_EVENT, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_STATE_UPDATE_EVENT, wxCommandEvent);

        
wxBEGIN_EVENT_TABLE(SnapshotClient, wxApp)
        EVT_DO_EVENT(wxID_ANY, SnapshotClient::DoConnect)
        EVT_ERR_EVENT(wxID_ANY, SnapshotClient::OnError)
        //EVT_DO_EVENT(wxID_ANY, SnapshotClient::DoSync)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(SnapshotClient);


SnapshotClient * SnapshotClient::m_pDefault = NULL ;

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
    m_sConfigFilename = std::string(base) + "/.snapshot/client" ;
    m_pConnector = new SnapshotConnector() ;
    if ( ! m_pDefault )
        m_pDefault   = this ;
    }

/// Cleanup - delete all pointers etc.
void SnapshotClient::Cleanup()
    {
    if ( m_pView )
        {
        delete m_pView ;
        m_pView = NULL ;
        }
    if ( m_pConnector )
        {
        delete m_pConnector ;
        m_pConnector = NULL ;
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
    
    m_pView = new SnapshotView(NULL, 0, NULL ) ; 
    m_pView -> UpdateStatus("Not connected") ;
    m_pView -> Show(true) ;
    
    m_pView -> SetTitle("SnapshotClient") ;
            
    m_pConfig = new SnapshotConfig() ;
    m_pConfig -> InitClientDefaults() ;
    try {
        m_pConfig -> Load(m_sConfigFilename) ;
        }
    catch(std::exception e)
        {
        PostError(e, std::string("config read fail")) ;
        }
    
    return true ;
    }


void SnapshotClient::DoConnect(wxCommandEvent& event) 
    {
    int res = m_pConnector->Connect(m_pConfig->GetString(CFG_SERVER_URL), 
                          0, //m_pConfig->GetInt("port", 0),
                          m_pConfig->GetString(CFG_SERVER_CA),
                          m_pConfig->GetString(CFG_CLIENT_CERT),
                          m_pConfig->GetString(CFG_CLIENT_KEY),
                          ""
                            );
    if (res == 200 )
        {
        PostUpdateServerState("connected") ;
        }
    
    event.Skip(true) ;
    }

void SnapshotClient::DoSync(wxCommandEvent& event) 
    {
    event.Skip(true) ;    
    }

void SnapshotClient::OnError(wxCommandEvent& event) 
    {
    wxStringClientData * clientObject = dynamic_cast<wxStringClientData *>(event.GetClientObject()) ;
    if(clientObject)
        {
        wxMessageDialog *errDlg = new wxMessageDialog(NULL, clientObject->GetData(), wxString("Exception"));
        errDlg->ShowModal() ;
        delete errDlg;
        delete clientObject ;
        event.Skip() ;  
        }
    }

void SnapshotClient::PostError(const std::exception &e, const std::string & sMore /* = "" */) 
    {
    wxCommandEvent eventErr(wxEVT_ERR_EVENT);
    wxStringClientData *pData = new wxStringClientData(wxString(e.what()) + "\n(" + sMore + ")")  ;
    eventErr.SetClientObject(pData) ;
    wxPostEvent(SnapshotClient::GetDefault(), eventErr);
    }

void SnapshotClient::PostUpdateServerState(const char *state) 
    {
    wxCommandEvent eventState(wxEVT_STATE_UPDATE_EVENT);
    wxStringClientData *pData = new wxStringClientData(wxString(state)) ;
    eventState.SetClientObject(pData) ;
    wxPostEvent(SnapshotClient::GetDefault()->View(), eventState);
    }
   