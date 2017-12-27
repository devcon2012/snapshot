/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotData.cpp
 * Author: klaus
 * 
 * Created on 25. Dezember 2017, 21:07
 */

#include "SnapshotData.hpp"
#include "../common/SnapshotException.hpp"

#include <boost/filesystem.hpp>
using namespace boost::filesystem ;

/// Create a SnapshotData Object containing configuration data
/// and file system state

#define PATH_SEPA std::string("/") 

SnapshotData::SnapshotData()
    {
    }

SnapshotData::SnapshotData(const SnapshotData& orig)
    {
    }

SnapshotData::~SnapshotData()
    {
    m_xServers.clear();
    m_xPathes.clear();
    m_xFiles.clear();
    }

/// Release Snapshot data
void SnapshotData::CleanupFileSnapshot()
    {
    m_xFiles.clear();    
    }

/// Add a server we can connect to
void SnapshotData::AddServer(const char * server)
    {
    m_xServers.push_back(server);
    }

/// Get server numbered n (default 0)
std::string SnapshotData::GetServer(int n /* = 0 */)
    {
    if ( ( n>=0 ) && (n<m_xServers.size()) )
        return m_xServers[n];
    
    }

/// How many servers?    
size_t SnapshotData::GetServerCount()
    {
    return m_xServers.size() ;
    }

/// Pathes monitored. We always monitor recursive.
/// Throw if problems (non exisiting, etc)
void SnapshotData::AddPathRecursive(const char * sPath)
    {
    
    AddPath(sPath) ;
    boost::filesystem::path p (sPath) ;

    try
        {
        for (const directory_entry& x : directory_iterator(p))
            {
            if ( exists(x.path()) && is_directory(x.path()) )
                {
                AddPathRecursive(x.path().generic_string().c_str());
                }
            }
        }
    catch (const filesystem_error& ex)
        {
        throw SnapshotException("directory_read", ex.what(), sPath );      
        }
    }

/// Add a single path
/// Throw if problems (non exisiting, etc)
void SnapshotData::AddPath(const char * sPath)
    {
    path p (sPath) ;

    try
        {
        if (exists(p) && is_directory(p) )
            {
            m_xPathes.push_back(sPath);
            }
        else
            throw SnapshotException("directory_read", "", sPath );      
        
        }
    catch (const filesystem_error& ex)
        {
        throw SnapshotException("directory_read", ex.what(), sPath );      
        }
        
    }

/// Get path n 
std::string SnapshotData::GetPath(int n)
    {
    return m_xPathes[n] ;
    }

size_t SnapshotData::GetPathCount()
    {
    return m_xPathes.size() ;
    }


void SnapshotData::CollectFileSnapshot() 
    {

    for( int i = 0; i <m_xPathes.size(); i++ )
        {
        try
            {
            boost::filesystem::path p (m_xPathes[i]) ;

            for (const directory_entry& x : directory_iterator(p))
                {
                if ( exists(x.path()) && ! is_directory(x.path()) )
                    {
                    tFileSnapshot xSnapshot(x.path(), i) ;
                    m_xFiles.push_back(xSnapshot) ;
                    }
                }
            }
        catch (const filesystem_error& ex)
            {
            throw SnapshotException("directory_read", ex.what(), m_xPathes[i].c_str() );      
            }
        }
    }

size_t SnapshotData::GetSnapshotCount()
    {
    return m_xFiles.size();
    }

SnapshotData::tFileSnapshot SnapshotData::GetSnapshot(int n)
    {
    return m_xFiles[n];    
    }

boost::filesystem::path SnapshotData::GetSnapshotPath(int n)
    {
    FileSnapshot &s = m_xFiles[n];
    
    std::string sPath = m_xPathes[s.nFilePathNo] ;
         
     boost::filesystem::path p (sPath) ;
     p += PATH_SEPA + s.sFileName;
     return p;
    }

boost::filesystem::path SnapshotData::GetSnapshotPath(SnapshotData::tFileSnapshot &s)
    {
    std::string sPath = m_xPathes[s.nFilePathNo] ;

    boost::filesystem::path p (sPath) ;
    p += PATH_SEPA + s.sFileName;
    return p;
    }

SnapshotData::FileSnapshot::FileSnapshot(boost::filesystem::path p, int n) 
    {
    nFileMtime = last_write_time(p);
    nFileSize = file_size(p) ;
    sFileName = p.filename().generic_string();
    nFilePathNo = n ;
    }