/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotServer.hpp
 * Author: klaus
 *
 * Created on 26. Dezember 2017, 12:44
 */

#ifndef SNAPSHOTSERVER_HPP
#define SNAPSHOTSERVER_HPP

class SnapshotServer {
public:
    SnapshotServer(int argc, char** argv);
    SnapshotServer(const SnapshotServer& orig);
    virtual ~SnapshotServer();
    int Run();
private:

};

#endif /* SNAPSHOTSERVER_HPP */

