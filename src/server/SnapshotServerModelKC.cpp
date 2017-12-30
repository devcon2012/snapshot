
/* 
 * File:   SnapshotServerModelKC.cpp
 * Author: klaus
 * 
 * Created on 29. Dezember 2017, 11:00
 */

#include "SnapshotServerModelKC.hpp"
#include "../common/SnapshotException.hpp"

using namespace std ;
using namespace kyotocabinet ;

SnapshotServerModelKC::SnapshotServerModelKC()
    {
        
    m_pDBSnapshots  = NULL ;
    m_pDBFiles      = NULL ;
    
    m_sDBClientFilename     = m_sDBRoot + "/clients.kch" ;
    
    m_pDBClients = new PolyDB();
    if (! (m_pDBClients && m_pDBClients -> open(m_sDBClientFilename, PolyDB::OWRITER | PolyDB::OCREATE)) )
        {
        throw SnapshotException("cannot_open", m_sDBClientFilename.c_str()) ;
        }
    
    }

SnapshotServerModelKC::SnapshotServerModelKC(const SnapshotServerModelKC& orig)
    {
    }

SnapshotServerModelKC::~SnapshotServerModelKC()
    {
    if(m_pDBClients)
        {
        m_pDBClients -> close();
        delete m_pDBClients ;
        m_pDBClients = NULL ;
        } 
    if(m_pDBSnapshots)
        {
        m_pDBSnapshots -> close();
        delete m_pDBSnapshots ;
        m_pDBSnapshots = NULL ;
        } 
    if(m_pDBFiles)
        {
        m_pDBFiles -> close();
        delete m_pDBFiles ;
        m_pDBFiles = NULL ;
        } 
    }



/// Get a handle for a client
/// pt contains the certificate subject, this is mapped to a unique handle
/// returned in the ptree
boost::property_tree::ptree SnapshotServerModelKC::GetClientHandle(boost::property_tree::ptree &pt)
    {
    boost::property_tree::ptree ret;
    return ret;
    
    }

/// Get a list of Snaphots we have
/// pt contains a client handle, returned is an array of dates with snapshots
/// mapping each date to a snapshot handle
boost::property_tree::ptree SnapshotServerModelKC::GetSnapshots(boost::property_tree::ptree &pt)
    {
    boost::property_tree::ptree ret;
    return ret;
    
    }

/// Get a list of pathes for a snapshot
/// pt contains a snapshot handle, returned is an array of pathes
/// returned is a handle for this path
boost::property_tree::ptree SnapshotServerModelKC::GetSnapshotPathes(boost::property_tree::ptree &pt)
    {
    boost::property_tree::ptree ret;
    return ret;
    
    }

/// Get a list of files for a snapshot
/// pt contains a snapshot handle, returned is an array of files
/// mapping each file to a pathhandle and filehandle
boost::property_tree::ptree SnapshotServerModelKC::GetSnapshotFiles(boost::property_tree::ptree &pt)
    {
    boost::property_tree::ptree ret;
    return ret;
    
    }


/// Setter

/// Set a handle for a client
/// pt contains the certificate subject, this is mapped to a unique handle
/// returned in the ptree
boost::property_tree::ptree SnapshotServerModelKC::SetClientHandle(boost::property_tree::ptree &pt)
    {
    boost::property_tree::ptree ret;
    
    if ( ! has_required_args(pt, required_args("SetClientHandle")) )
    return ret;
    }

/// Add a  Snaphots
/// pt contains a client handle and a timestamp. An existing snapshot handle
/// (if given) will copy the pathes for this old snapshot to the new one
/// returned is a newly created unique snapshot handle for this client
/// and timestamp
boost::property_tree::ptree SnapshotServerModelKC::AddSnapshot(boost::property_tree::ptree &pt)
    {
    boost::property_tree::ptree ret;
    return ret;
    
    }

/// Add a path to a snapshot
/// pt contains a path and an existing snapshot handle
/// returned is a new unique handle for this path
boost::property_tree::ptree SnapshotServerModelKC::AddSnapshotPath(boost::property_tree::ptree &pt)
    {
    boost::property_tree::ptree ret;
    return ret;
    
    }

/// Add a list of files in one path to a snapshot
/// pt contains a snapshot handle, a path handle and a filename
/// returned is a new file handle and maybe a digest for the same
/// file in a previous snapshot
boost::property_tree::ptree SnapshotServerModelKC::AddSnapshotFiles(boost::property_tree::ptree &pt)
    {
    boost::property_tree::ptree ret;
    return ret;
    
    }

  
void SnapshotServerModelKC::open_client_dbs(std::string const &sHandle)
    {
    
    m_sDBSnapshotFilename   = m_sDBRoot + "/" + sHandle + "-snap.kch" ;
    m_sDBFilesFilename      = m_sDBRoot + "/" + sHandle + "-files.kch" ;
    
    m_pDBClients = new PolyDB();
    if (! (m_pDBClients && m_pDBClients -> open(m_sDBClientFilename, PolyDB::OWRITER | PolyDB::OCREATE)) )
        {
        throw SnapshotException("cannot_open", m_sDBClientFilename.c_str()) ;
        }
    
    m_pDBSnapshots = new PolyDB();
    if (! (m_pDBSnapshots && m_pDBSnapshots -> open(m_sDBSnapshotFilename, PolyDB::OWRITER | PolyDB::OCREATE)) )
        {
        throw SnapshotException("cannot_open", m_sDBSnapshotFilename.c_str()) ;
        }

    m_pDBFiles = new PolyDB();
    if (! (m_pDBFiles && m_pDBFiles -> open(m_sDBFilesFilename, PolyDB::OWRITER | PolyDB::OCREATE)) )
        {
        throw SnapshotException("cannot_open", m_sDBFilesFilename.c_str()) ;
        }

    }

void SnapshotServerModelKC::close_client_dbs()
    {
    if (m_pDBClients)
        {
        m_pDBClients->close() ;
        delete m_pDBClients ;
        m_pDBClients = NULL ;
        }

    if (m_pDBSnapshots)
        {
        m_pDBSnapshots->close() ;
        delete m_pDBSnapshots ;
        m_pDBSnapshots = NULL ;
        }
  
    }

