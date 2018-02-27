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

class SnapshotSettings : public SettingsDialog 
{
public:
    SnapshotSettings(wxWindow* parent) ; 

    virtual ~SnapshotSettings();

private:
    virtual void OnExit(wxCommandEvent &e) ;    
    
    virtual void AddDirectory( wxCommandEvent& event ) ;
    virtual void RemoveDirectory( wxCommandEvent& event ) ;
    virtual void UpdateSettings( wxCommandEvent& event ) ;
    virtual void CancelSettings( wxCommandEvent& event ) ;

    wxDECLARE_EVENT_TABLE();

};



#endif /* SNAPSHOTSETTINGS_HPP */

