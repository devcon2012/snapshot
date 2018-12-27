/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotSettings.cpp
 * Author: klaus
 * 
 * Created on 24. Februar 2018, 16:33
 */

#include "SnapshotSettings.hpp"
#include "../common/SnapshotConfig.hpp"

wxBEGIN_EVENT_TABLE(SnapshotSettings, wxDialog)
    EVT_MENU(wxID_EXIT,  SnapshotSettings::OnExit)
wxEND_EVENT_TABLE()


SnapshotSettings::SnapshotSettings(wxWindow* parent) : SettingsDialog(parent)
    {
    SnapshotConfig *pConfig = SnapshotConfig::GetDefaultConfig() ;
    std::string sURL = pConfig -> GetString("ServerURL", "UNDEF") ;
    wxString sWxStr(sURL) ;
    m_textCtrl1 -> ChangeValue(sWxStr) ;
    std::vector<std::string> sEmpty ;
    std::vector<std::string> sDirs = pConfig -> GetStrings("SyncedDirs", sEmpty);
    for( auto i = sDirs.begin(); i != sDirs.end(); i++ )
        {
        m_listBoxSyncedDirs -> Append(*i) ;
        }
    }

SnapshotSettings::~SnapshotSettings()
    {
    }

void SnapshotSettings::OnExit(wxCommandEvent &e) 
    {
    }

    
void SnapshotSettings::AddDirectory( wxCommandEvent& event ) 
    {
    wxFileName xDir = m_dirPicker1 ->GetDirName();
    m_listBoxSyncedDirs -> Append(xDir.GetFullPath()) ;
    }

void SnapshotSettings::RemoveDirectory( wxCommandEvent& event ) 
    {
    int nSelected = m_listBoxSyncedDirs -> GetSelection() ;
    m_listBoxSyncedDirs -> Delete(nSelected) ;
    }

void SnapshotSettings::UpdateSettings( wxCommandEvent& event ) 
    {
    wxString sServer = m_textCtrl1 -> GetLineText(0);
    SnapshotConfig *pConfig = SnapshotConfig::GetDefaultConfig() ;
    pConfig -> Set("ServerURL", std::string(sServer.utf8_str())) ;
    std::vector<std::string> sDirs;
    for(unsigned int i=0; i<m_listBoxSyncedDirs->GetCount(); i++)
        {
        std::string sDir = m_listBoxSyncedDirs->GetString(i);
        sDirs.push_back(sDir) ;
        }
    pConfig -> Set("SyncedDirs", sDirs) ;    
    Close(true) ;
    }

void SnapshotSettings::CancelSettings( wxCommandEvent& event ) 
    {
    Close(true) ;
    }
