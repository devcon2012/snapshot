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
    }

SnapshotClient::SnapshotClient(int argc, char** argv)
    {
    }

SnapshotClient::SnapshotClient(const SnapshotClient& orig)
    {
    }

SnapshotClient::~SnapshotClient()
    {
    }


int SnapshotClient::Run()
    {
    
    }

bool SnapshotClient::OnInit()
    {
    m_pView = new SnapshotView(0, NULL ) ; 
    m_pView -> Show(true);
    return true;
    }
