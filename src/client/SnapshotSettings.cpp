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

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
    EVT_MENU(wxID_EXIT, SettingsDialog::OnExit)
wxEND_EVENT_TABLE()

KeyPasswdDialog::KeyPasswdDialog(wxWindow *parent) : myKeyPasswdDialog(parent) 
    {
    
    }

KeyPasswdDialog::~KeyPasswdDialog() 
    {
    
    }

std::string KeyPasswdDialog::GetPasswd() 
    {
    return "test" ;
    }

SettingsDialog::SettingsDialog(wxWindow* parent) : mySettingsDialog(parent)
    {
    SnapshotConfig *pConfig = SnapshotConfig::GetDefaultConfig() ;
    std::string sURL = pConfig -> GetString(CFG_SERVER_URL, "UNDEF") ;
    wxString sWxStr(sURL) ;
    m_sServerURL -> ChangeValue(sWxStr) ;
    m_sCAPath -> ChangeValue(wxString(pConfig -> GetString(CFG_SERVER_CA, "UNDEF"))) ;
    m_sCertificatePath -> ChangeValue(wxString(pConfig -> GetString(CFG_CLIENT_CERT, "UNDEF"))) ;
    m_sKeyPath -> ChangeValue(wxString(pConfig -> GetString(CFG_CLIENT_KEY, "UNDEF"))) ;
    std::vector<std::string> sEmpty ;
    std::vector<std::string> sDirs = pConfig -> GetStrings(CFG_SYNCED_DIRS, sEmpty);
    for( auto i = sDirs.begin(); i != sDirs.end(); i++ )
        {
        m_listBoxSyncedDirs -> Append(*i) ;
        }
    }

SettingsDialog::~SettingsDialog()
    {
    }

void SettingsDialog::OnExit(wxCommandEvent &e) 
    {
    }

    
void SettingsDialog::AddDirectory( wxCommandEvent& event ) 
    {
    wxFileName xDir = m_dirPicker1 ->GetDirName();
    m_listBoxSyncedDirs -> Append(xDir.GetFullPath()) ;
    }

void SettingsDialog::RemoveDirectory( wxCommandEvent& event ) 
    {
    int nSelected = m_listBoxSyncedDirs -> GetSelection() ;
    m_listBoxSyncedDirs -> Delete(nSelected) ;
    }

std::string SettingsDialog::toString( const wxTextCtrl & t) 
    {
    wxString sText = t.GetLineText(0);
    return std::string(sText.utf8_str()) ;
    }
    
void SettingsDialog::UpdateSettings( wxCommandEvent& event ) 
    {
    SnapshotConfig *pConfig = SnapshotConfig::GetDefaultConfig() ;
    pConfig -> Set(CFG_SERVER_URL, toString(*m_sServerURL)) ;
    std::vector<std::string> sDirs;
    for(unsigned int i=0; i<m_listBoxSyncedDirs->GetCount(); i++)
        {
        std::string sDir = m_listBoxSyncedDirs->GetString(i);
        sDirs.push_back(sDir) ;
        }
    pConfig -> Set(CFG_SYNCED_DIRS, sDirs) ;    
    pConfig -> Set(CFG_SERVER_CA, toString(*m_sCAPath)) ; 
    pConfig -> Set(CFG_CLIENT_CERT, toString(*m_sCertificatePath)) ; 
    pConfig -> Set(CFG_CLIENT_KEY, toString(*m_sKeyPath)) ; 

    /*m_sCAPath -> ChangeValue(wxString(pConfig -> GetString(CFG_SERVER_CA, "UNDEF"))) ;
    m_sCertificatePath -> ChangeValue(wxString(pConfig -> GetString(CFG_CLIENT_CERT, "UNDEF"))) ;
    m_sKeyPath -> ChangeValue(wxString(pConfig -> GetString(CFG_CLIENT_KEY, "UNDEF"))) ; */

    Close(true) ;
    }

void SettingsDialog::CancelSettings( wxCommandEvent& event ) 
    {
    Close(true) ;
    }

 void SettingsDialog::SelectCA( wxFileDirPickerEvent& event )
     {
     wxString sCAFile = m_xCAPicker -> GetFileName().GetFullPath() ;
     m_sCAPath -> SetValue(sCAFile) ;
     }
 
 void SettingsDialog::SelectCertificate( wxFileDirPickerEvent& event )
     {
     wxString sCertFile = m_xCertPicker -> GetFileName().GetFullPath() ;
     m_sCertificatePath -> SetValue(sCertFile) ;
     }
 
 void SettingsDialog::SelectKey( wxFileDirPickerEvent& event )
     {
     wxString sKeyFile = m_xKeyPicker -> GetFileName().GetFullPath( );
     m_sKeyPath -> SetValue(sKeyFile) ;
     
     }

 