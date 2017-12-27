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

class SnapshotClient 
    {
public:
    SnapshotClient(int argc, char** argv ) ;
    SnapshotClient(const SnapshotClient& orig) ;
    virtual ~SnapshotClient() ;
    int Run() ;
    
private:

    };

#endif /* SNAPSHOTCLIENT_HPP */

