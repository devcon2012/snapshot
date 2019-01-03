/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotView.cpp
 * Author: klaus
 * 
 * Created on 25. Dezember 2017, 21:07
 */

#include <wx/wx.h>
#include "SnapshotClient.hpp"
#include "SnapshotView.hpp"
#include "SnapshotSettings.hpp"

wxBEGIN_EVENT_TABLE(SnapshotView, wxFrame)
    EVT_MENU(wxID_EXIT,  SnapshotView::OnExit)
    EVT_STATE_UPDATE_EVENT(wxID_ANY, SnapshotView::OnUpdateServerState)
wxEND_EVENT_TABLE()

SnapshotView::SnapshotView(wxWindow* parent, int argc, char** argv ) : myMainFrame(parent)
    {
    
    }

SnapshotView::SnapshotView(const SnapshotView& orig) : myMainFrame(NULL)
    {
    }

SnapshotView::~SnapshotView()
    {
    }

void SnapshotView::UpdateStatus(const char * sStatus) 
    {
    UpdateStatus(wxString(sStatus)) ;
    }

void SnapshotView::UpdateStatus(const wxString & sStatus) 
    {
    m_statusBar1 ->SetStatusText(sStatus) ;
    }

bool SnapshotView::OnInit()
    {
    this->Show(true);
    return true;
    }

void SnapshotView::OnExit(wxCommandEvent &e) 
    {
    wxTheApp->OnExit();
    }

void SnapshotView::OnMenuSettings( wxCommandEvent& event ) 
    {
    SettingsDialog * pSettings = new SettingsDialog(this);
    pSettings -> ShowModal() ;
    }

void SnapshotView::OnMenuQuit( wxCommandEvent& event ) 
    {
    OnExit(event) ;
    }

void SnapshotView::OnUpdateServerState( wxCommandEvent& event ) 
    {
    wxStringClientData * clientObject = dynamic_cast<wxStringClientData *>(event.GetClientObject()) ;
    if (clientObject)
        {
        UpdateStatus(clientObject -> GetData()) ;  
        delete clientObject ;
        }
    }


void SnapshotView::OnConnectServer( wxCommandEvent& event ) 
    {
    UpdateStatus("Connecting...") ;

    wxCommandEvent eventDo(wxEVT_DO_EVENT);

    wxPostEvent(SnapshotClient::GetDefault(), eventDo);
    }
