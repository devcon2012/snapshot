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
#include "SnapshotView.hpp"
#include "SnapshotSettings.hpp"

wxBEGIN_EVENT_TABLE(SnapshotView, wxFrame)
    EVT_MENU(wxID_EXIT,  SnapshotView::OnExit)
wxEND_EVENT_TABLE()

SnapshotView::SnapshotView(int argc, char** argv ) : myMainFrame(NULL)
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
    m_statusBar1 ->SetStatusText(wxString(sStatus)) ;
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
    SnapshotSettings * pSettings = new SnapshotSettings(this);
    pSettings -> ShowModal() ;
    }

void SnapshotView::OnMenuQuit( wxCommandEvent& event ) 
    {
    OnExit(event) ;
    }

void SnapshotView::OnConnectServer( wxCommandEvent& event ) 
    {
    UpdateStatus("Connecting...") ;
    }
