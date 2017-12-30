/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotView.hpp
 * Author: klaus
 *
 * Created on 25. Dezember 2017, 21:07
 */

#ifndef SNAPSHOTVIEW_HPP
#define SNAPSHOTVIEW_HPP

#include "wxClient.h"

class SnapshotView : public myMainFrame
{
public:
    SnapshotView(int argc, char** argv);
    SnapshotView(const SnapshotView& orig);
    virtual ~SnapshotView();
    

private:
    virtual void ExitButton( wxCommandEvent& event ) { OnExit(event); }
    virtual bool OnInit() ;
    virtual void OnExit(wxCommandEvent &e) ;
    wxDECLARE_EVENT_TABLE();

};

#endif /* SNAPSHOTVIEW_HPP */

