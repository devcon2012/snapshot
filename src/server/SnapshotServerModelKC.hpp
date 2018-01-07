/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotServerModel.hpp
 * Author: klaus
 *
 * Created on 29. Dezember 2017, 11:00
 */

#ifndef SNAPSHOTSERVERMODELKC_HPP
#define SNAPSHOTSERVERMODELKC_HPP

#include <vector>
#include <kcpolydb.h>

#include "SnapshotServerModel.hpp"

class SnapshotServerModelKC : public SnapshotServerModel {
public:
    SnapshotServerModelKC();
    SnapshotServerModelKC(const SnapshotServerModelKC& orig);
    virtual ~SnapshotServerModelKC();
    
    virtual void Provision(boost::property_tree::ptree &pt) ;
    virtual void Cleanup() ;
    
    // Getter
    // Get a handle for a client
    virtual boost::property_tree::ptree GetClientHandle(boost::property_tree::ptree &pt);
    
    // Get a list of Snaphots we have
    virtual boost::property_tree::ptree GetSnapshots(boost::property_tree::ptree &pt);

    // Get a list of pathes for a snapshot
    virtual boost::property_tree::ptree GetSnapshotPathes(boost::property_tree::ptree &pt);
    
    // Get a list of files for a snapshot
    virtual boost::property_tree::ptree GetSnapshotFiles(boost::property_tree::ptree &pt);

    
    // Setter    
    // Set a handle for a client
    virtual boost::property_tree::ptree SetClientHandle(boost::property_tree::ptree &pt);
    
    // Add a  Snaphots
    virtual boost::property_tree::ptree AddSnapshot(boost::property_tree::ptree &pt);

    // Add a path to a snapshot
    virtual boost::property_tree::ptree AddSnapshotPath(boost::property_tree::ptree &pt);
    
    // Add a list of files in one path to a snapshot
    virtual boost::property_tree::ptree AddSnapshotFiles(boost::property_tree::ptree &pt);
        
protected:
 
    virtual void open_client_dbs(std::string const &sHandle) ;
    virtual void close_client_dbs() ;
    virtual boost::property_tree::ptree return_db_error_info(boost::property_tree::ptree &pt, 
                          kyotocabinet::PolyDB    * pDB ,
                    const std::string &sLocation,
                    const std::string &sInfo);

    /// Database file containing clients. Global file.
    std::string               m_sDBClientFilename ;

    /// Database file containing Snapshots. One file per client.
    std::string               m_sDBSnapshotFilename ;

    /// Database file containing Files. One file per client.
    std::string               m_sDBFilesFilename ;
    
    /// Database of clients we know & like
    kyotocabinet::PolyDB    * m_pDBClients ;
        
    /// Database of Snapshots (and pathes monitored) we maintain
    kyotocabinet::PolyDB    * m_pDBSnapshots ;
    
    /// Database of Files we have snapshots
    kyotocabinet::PolyDB    * m_pDBFiles ;
};

#endif /* SNAPSHOTSERVERMODELKC_HPP */

