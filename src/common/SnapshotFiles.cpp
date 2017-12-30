/* 
 * File:   SnapshotFiles.cpp
 * Author: klaus
 * 
 * Created on 25. Dezember 2017, 21:07
 */

#include "SnapshotFiles.hpp"
#include "SnapshotException.hpp"

#include <boost/filesystem.hpp>
using namespace boost::filesystem ;

/// Create a SnapshotFiles Object containing file snapshot data
/// and file system state

#define PATH_SEPA std::string("/") 

SnapshotFiles::SnapshotFiles()
    {
    }

SnapshotFiles::SnapshotFiles(const SnapshotFiles& orig)
    {
    }

SnapshotFiles::~SnapshotFiles()
    {
    m_xPathes.clear();
    m_xFiles.clear();
    }

/// Release Snapshot data
void SnapshotFiles::CleanupFileSnapshot()
    {
    m_xFiles.clear();    
    }

/// Pathes monitored. We always monitor recursive.
/// Throw if problems (non exisiting, etc)
void SnapshotFiles::AddPathRecursive(const char * sPath)
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
void SnapshotFiles::AddPath(const char * sPath)
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
std::string SnapshotFiles::GetPath(int n)
    {
    return m_xPathes[n] ;
    }

size_t SnapshotFiles::GetPathCount()
    {
    return m_xPathes.size() ;
    }


void SnapshotFiles::CollectFileSnapshot() 
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

size_t SnapshotFiles::GetSnapshotCount()
    {
    return m_xFiles.size();
    }

SnapshotFiles::tFileSnapshot SnapshotFiles::GetSnapshot(int n)
    {
    return m_xFiles[n];    
    }

boost::filesystem::path SnapshotFiles::GetSnapshotPath(int n)
    {
    FileSnapshot &s = m_xFiles[n];
    
    std::string sPath = m_xPathes[s.nFilePathNo] ;
         
     boost::filesystem::path p (sPath) ;
     p += PATH_SEPA + s.sFileName;
     return p;
    }

boost::filesystem::path SnapshotFiles::GetSnapshotPath(SnapshotFiles::tFileSnapshot &s)
    {
    std::string sPath = m_xPathes[s.nFilePathNo] ;

    boost::filesystem::path p (sPath) ;
    p += PATH_SEPA + s.sFileName;
    return p;
    }

SnapshotFiles::FileSnapshot::FileSnapshot(boost::filesystem::path p, int n) 
    {
    nFileMtime = last_write_time(p);
    nFileSize = file_size(p) ;
    sFileName = p.filename().generic_string();
    nFilePathNo = n ;
    }