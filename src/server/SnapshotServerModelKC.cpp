
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

/// Handle types:
/// 01- Client handle
/// 02- Snapshot-handle

#define CLIENT_HANDLE_PREFIX "01-"
#define SNAPSHOT_HANDLE_PREFIX "02-"
#define PATH_HANDLE_PREFIX "03-"
#define FILE_HANDLE_PREFIX "03-"

SnapshotServerModelKC::SnapshotServerModelKC()
    {  
    m_pDBClients    = NULL ;
    m_pDBSnapshots  = NULL ;
    m_pDBFiles      = NULL ;    
    }

SnapshotServerModelKC::SnapshotServerModelKC(const SnapshotServerModelKC& orig)
    {
    }

SnapshotServerModelKC::~SnapshotServerModelKC()
    {
    }

/// close databases, release memory. 
/// object can be re-used after provisioning again
 void SnapshotServerModelKC::Cleanup() 
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
 
/// Provision the model with the configuration data required.
/// The Model will not work without this info
/// @var pt --> "DBRoot" : Database root path
 void SnapshotServerModelKC::Provision(boost::property_tree::ptree &pt) 
    {
     
    // Call super method
    SnapshotServerModel::Provision(pt) ;
    
    m_sDBRoot = pt.get("DBRoot", ".") ;
    
    m_sDBClientFilename     = m_sDBRoot + "/clients.kch" ;

    m_pDBClients = new PolyDB();
    if (! (m_pDBClients && m_pDBClients -> open(m_sDBClientFilename, PolyDB::OWRITER | PolyDB::OCREATE)) )
        {
        throw SnapshotException("cannot_open", m_sDBClientFilename.c_str()) ;
        }
    
    
    m_sDBSnapshotFilename     = m_sDBRoot + "/snapshots.kch" ;

    m_pDBSnapshots = new PolyDB();
    if (! (m_pDBSnapshots && m_pDBSnapshots -> open(m_sDBSnapshotFilename, PolyDB::OWRITER | PolyDB::OCREATE)) )
        {
        throw SnapshotException("cannot_open", m_sDBSnapshotFilename.c_str()) ;
        }

    
    m_sDBFilesFilename     = m_sDBRoot + "/files.kch" ;

    m_pDBFiles = new PolyDB();
    if (! (m_pDBFiles && m_pDBFiles -> open(m_sDBFilesFilename, PolyDB::OWRITER | PolyDB::OCREATE)) )
        {
        throw SnapshotException("cannot_open", m_sDBFilesFilename.c_str()) ;
        }

     }

/// Get a handle for a client
/// pt contains the certificate subject, this is mapped to a unique handle
/// returned in the ptree
boost::property_tree::ptree SnapshotServerModelKC::GetClientHandle(boost::property_tree::ptree &pt)
    {
    boost::property_tree::ptree ret;
    
    if ( ! has_required_args(pt, "GetClientHandle") )
        return return_error_info(pt, "bad_arguments", "GetClientHandle");
    
    std::string sSubject = pt.get<std::string>("subject") ;

    std::string sHandle ;
    if ( ! m_pDBClients -> get (sSubject, &sHandle) )
        {
        return return_error_info(pt, "nonexisting_handle", "GetClientHandle");
        }
    
    ret.put("clienthandle", sHandle);
    return ret;
    }

/// Get a list of Snaphots we have
/// pt contains a client handle, returned is an array of dates with snapshots
/// mapping each date to a snapshot handle
boost::property_tree::ptree SnapshotServerModelKC::GetSnapshots(boost::property_tree::ptree &pt)
    {
    boost::property_tree::ptree ret;

    if ( ! has_required_args(pt, "GetSnapshots") )
        return return_error_info(pt, "bad_arguments", "GetSnapshots");
    
    std::string sSubject = pt.get<std::string>("clienthandle") ;
    
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
/// @var pt requires subject
/// @ret ret pt containing handle 

boost::property_tree::ptree SnapshotServerModelKC::SetClientHandle(boost::property_tree::ptree &pt)
    {
    boost::property_tree::ptree ret;
    
    if ( ! has_required_args(pt, "SetClientHandle") )
        return return_error_info(pt, "bad_arguments", "SetClientHandle");
    
    std::string sSubject = pt.get<std::string>("subject") ;

    std::string sHandle ;
    if ( ! m_pDBClients -> get (sSubject, &sHandle) )
        {
        sHandle = create_handle(CLIENT_HANDLE_PREFIX) ;
        m_pDBClients -> set (sSubject, sHandle) ;
        //return return_error_info(pt, "database_fail", "SetClientHandle");
        }
    
    ret.put("clienthandle", sHandle);
    return ret;
    }

/// Add a  Snaphots
/// pt contains a client handle and a timestamp. An existing snapshot handle
/// (if given) will copy the pathes for this old snapshot to the new one
/// returned is a newly created unique snapshot handle for this client
/// and timestamp
/// @var pt argument ptree containing clienthandle and timestamp
/// @ret 
boost::property_tree::ptree SnapshotServerModelKC::AddSnapshot(boost::property_tree::ptree &pt)
    {

    if ( ! has_required_args(pt, "AddSnapshot") )
        return return_error_info(pt, "bad_arguments", "AddSnapshot");

    std::string sClienthandle = pt.get<std::string>("clienthandle") ;
    std::string sTimestamp = pt.get<std::string>("timestamp") ;
    std::string sSnapshothandle = create_handle(SNAPSHOT_HANDLE_PREFIX);
    
    boost::property_tree::ptree snapshot;
    snapshot.add("timestamp", sTimestamp);
    snapshot.add("snapshothandle", sSnapshothandle);
    
    std::string sJSON = json_from_pt(snapshot) ;

    m_pDBSnapshots -> set (sClienthandle, sJSON) ;

    return snapshot;
    
    }

/// Add a path to a snapshot
/// pt contains a path and an existing snapshot handle
/// returned is a new unique handle for this path
boost::property_tree::ptree SnapshotServerModelKC::AddSnapshotPath(boost::property_tree::ptree &pt)
    {
    if ( ! has_required_args(pt, "AddSnapshotPath") )
        return return_error_info(pt, "bad_arguments", "AddSnapshotPath");

    std::string sSnapshothandle   = pt.get<std::string>("snapshothandle") ;
    std::string sSnapshotPath     = pt.get<std::string>("path") ;
    std::string sPathhandle       = change_handle(sSnapshothandle.c_str(), SNAPSHOT_HANDLE_PREFIX, PATH_HANDLE_PREFIX);
    
    std::string sJSON ;
    boost::property_tree::ptree snapshot;
    
    if( m_pDBSnapshots -> get (sPathhandle, & sJSON))
        {
        snapshot = pt_from_json(sJSON) ;
        }

    snapshot.put("snapshothandle", sSnapshothandle);
    
    sJSON = json_from_pt(snapshot) ;
    
    if( m_pDBSnapshots -> set (sPathhandle, sJSON))
        {
        return return_error_info(pt, "database_error", "AddSnapshotPath",
                                 m_pDBSnapshots ->error().name() );
        }

    return snapshot;
    }

/// Add a list of files in one path to a snapshot
/// pt contains a snapshot handle, a path handle and a filename
/// returned is a new file handle and maybe a digest for the same
/// file in a previous snapshot
boost::property_tree::ptree SnapshotServerModelKC::AddSnapshotFiles(boost::property_tree::ptree &pt)
    {
    if ( ! has_required_args(pt, "AddSnapshotPath") )
        return return_error_info(pt, "bad_arguments", "AddSnapshotPath");

    std::string sSnapshothandle   = pt.get<std::string>("snapshothandle") ;
    std::string sSnapshotPath     = pt.get<std::string>("path") ;
    std::string sPathhandle       = change_handle(sSnapshothandle.c_str(), SNAPSHOT_HANDLE_PREFIX, PATH_HANDLE_PREFIX);
    
    std::string sJSON ;
    boost::property_tree::ptree snapshot;
    
    if( m_pDBSnapshots -> get (sPathhandle, & sJSON))
        {
        snapshot = pt_from_json(sJSON) ;
        }

    snapshot.put("snapshothandle", sSnapshothandle);
    
    sJSON = json_from_pt(snapshot) ;
    
    if( m_pDBSnapshots -> set (sPathhandle, sJSON))
        {
        return return_error_info(pt, "database_error", "AddSnapshotPath",
                                 m_pDBSnapshots ->error().name() );
        }    
    return snapshot ;
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

