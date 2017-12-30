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

#include "SnapshotView.hpp"
#include <wx/wx.h>

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

bool SnapshotView::OnInit()
    {
    this->Show(true);
    }

void SnapshotView::OnExit(wxCommandEvent &e) 
    {
    exit(0);
    }
