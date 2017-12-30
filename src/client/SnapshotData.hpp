/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotData.hpp
 * Author: klaus
 *
 * Snapshot model 
 *  *
 * Created on 25. Dezember 2017, 21:07
 */

#ifndef SNAPSHOTDATA_HPP
#define SNAPSHOTDATA_HPP

#include <map>
#include <vector>
#include <string>

#include "../common/SnapshotFiles.hpp"

class SnapshotData : public SnapshotFiles
{
public:
    
    SnapshotData();
    SnapshotData(const SnapshotData& orig);
    virtual ~SnapshotData();
    
    /// getter/setter
    /// Servers
    void AddServer(const char * server);
    std::string GetServer(int n = 0);
    size_t GetServerCount();
        
private:
       
    /// Vector containing servers we can connect to
    std::vector<std::string>     m_xServers ;
        
};
#endif /* SNAPSHOTDATA_HPP */

