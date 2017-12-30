/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotClient.hpp
 * Author: klaus
 *
 * Created on 25. Dezember 2017, 21:01
 */

#ifndef SNAPSHOTCLIENT_HPP
#define SNAPSHOTCLIENT_HPP

#include <wx/wx.h>

#include "SnapshotView.hpp"
#include "SnapshotData.hpp"


class SnapshotClient : public wxApp
    {
public:
    SnapshotClient() ;
    SnapshotClient(int argc, char** argv ) ;
    SnapshotClient(const SnapshotClient& orig) ;
    virtual ~SnapshotClient() ;
    int Run() ;
    virtual bool OnInit();
    
private:
     
    SnapshotView * m_pView ;
    };

#endif /* SNAPSHOTCLIENT_HPP */

