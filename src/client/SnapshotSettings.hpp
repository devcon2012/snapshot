/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotSettings.hpp
 * Author: klaus
 *
 * Created on 24. Februar 2018, 16:33
 */

#ifndef SNAPSHOTSETTINGS_HPP
#define SNAPSHOTSETTINGS_HPP

#include "wxClient.h"

/// defined config settings keys

#define CFG_SERVER_URL      "ServerURL"
#define CFG_SERVER_CA       "ServerCA"
#define CFG_CLIENT_CERT     "ClientCertificate"
#define CFG_CLIENT_KEY      "ClientKey"
#define CFG_SYNCED_DIRS     "SyncedDirs"
    
class SettingsDialog : public mySettingsDialog 
{
public:
    SettingsDialog(wxWindow* parent) ; 

    virtual ~SettingsDialog();

private:
    virtual void OnExit(wxCommandEvent &e) ;    
    
    virtual void AddDirectory( wxCommandEvent& event ) ;
    virtual void RemoveDirectory( wxCommandEvent& event ) ;
    virtual void UpdateSettings( wxCommandEvent& event ) ;
    virtual void CancelSettings( wxCommandEvent& event ) ;

    virtual void SelectCA( wxFileDirPickerEvent& event ) ;
    virtual void SelectCertificate( wxFileDirPickerEvent& event ) ;
    virtual void SelectKey( wxFileDirPickerEvent& event ) ;

    std::string toString( const wxTextCtrl & t) ;
    wxDECLARE_EVENT_TABLE();

};

class KeyPasswdDialog : public myKeyPasswdDialog
    {
    public:
        KeyPasswdDialog( wxWindow* parent ) ;
        ~KeyPasswdDialog();
        std::string GetPasswd() ;
    } ;


#endif /* SNAPSHOTSETTINGS_HPP */

