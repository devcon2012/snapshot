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

#include <boost/filesystem.hpp>

class SnapshotData {
public:
    
    /// Type collecting file state info: Name
    typedef struct FileSnapshot
        {
        std::string sFileName ;     /// Name without path
        time_t      nFileMtime ;    /// File Mtime
        size_t      nFileSize ;     /// File Size   
        ssize_t      nFilePathNo ;   /// Index into path vector
        
        FileSnapshot(boost::filesystem::path p, int n=-1) ;
        } tFileSnapshot ;
    SnapshotData();
    SnapshotData(const SnapshotData& orig);
    virtual ~SnapshotData();
    
    /// getter/setter
    /// Servers
    void AddServer(const char * server);
    std::string GetServer(int n = 0);
    size_t GetServerCount();
    
    /// Pathes monitored. We always monitor recursive.
    void AddPathRecursive(const char * path);
    void AddPath(const char * path);
    std::string GetPath(int n);
    size_t GetPathCount();

    /// Snapshotdata
    size_t GetSnapshotCount();
    tFileSnapshot GetSnapshot(int n);
    boost::filesystem::path GetSnapshotPath(int n);
    boost::filesystem::path GetSnapshotPath(tFileSnapshot &s);
    
    /// Data operations
    
    /// Collect snapshot data
    void CollectFileSnapshot() ;
    
    
    
private:
   
    void CleanupFileSnapshot();
    
    /// Vector containing servers we can connect to
    std::vector<std::string>     m_xServers ;
    
    /// Vector containing pathes we monitor
    std::vector<std::string>     m_xPathes ;

    /// Vector containing files we monitor
    std::vector<tFileSnapshot>   m_xFiles ;
    
    
};
#endif /* SNAPSHOTDATA_HPP */

