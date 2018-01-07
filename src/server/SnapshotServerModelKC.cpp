
/* 
 * File:   SnapshotServerModelKC.cpp
 * Author: klaus
 * 
 * Created on 29. Dezember 2017, 11:00
 */

#include "SnapshotServerModelKC.hpp"
#include "../common/SnapshotException.hpp"
#include "../common/StrUtil.hpp"

using namespace std ;
using namespace kyotocabinet ;

/// Handle types:
/// 01- Client handle
/// 02- Snapshot-handle

#define CLIENT_HANDLE_PREFIX "01-"
#define SNAPSHOT_HANDLE_PREFIX "02-"
#define PATH_HANDLE_PREFIX "03-"
#define FILE_HANDLE_PREFIX "04-"

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
    
    
    std::string sClienthandle = pt.get<std::string>("clienthandle") ;
    std::string sSnapshotClienthandle = change_handle(sClienthandle, CLIENT_HANDLE_PREFIX, SNAPSHOT_HANDLE_PREFIX);
    
    // Update snapshots for client
    std::string sJSON ;
    boost::property_tree::ptree ClientSnapshots;
    if ( ! m_pDBSnapshots -> get (sSnapshotClienthandle, &sJSON) )
        {
        return return_db_error_info(pt, m_pDBSnapshots, "GetSnapshots",
                                 std::string("cannot get ") + sSnapshotClienthandle );                       
        }
    
    ClientSnapshots = StrUtil::pt_from_json(sJSON);
    std::vector<string> sSnapShots ;
    StrUtil::get_vector(ClientSnapshots, "snapshots", sSnapShots) ;
    StrUtil::add_vector(ret, "snapshots", sSnapShots) ;
    
    return ret;
    
    }

/// Get a list of pathes for a snapshot
/// pt contains a snapshot handle, returned is an array of pathes
/// returned is a handle for this path
boost::property_tree::ptree SnapshotServerModelKC::GetSnapshotPathes(boost::property_tree::ptree &pt)
    {
    boost::property_tree::ptree ret, work;

    if ( ! has_required_args(pt, "GetSnapshotPathes") )
        return return_error_info(pt, "bad_arguments", "GetSnapshotPathes");

    std::string sSnapshothandle   = pt.get<std::string>("snapshothandle") ;
    std::string sPathhandle       = change_handle(sSnapshothandle.c_str(), SNAPSHOT_HANDLE_PREFIX, PATH_HANDLE_PREFIX);
     
    std::string sJSON ;
    
    std::vector<std::string> sPathArray ;
    std::vector<std::string> sHandleArray ;
    if(  ! m_pDBSnapshots -> get (sSnapshothandle, & sJSON))
        {
        return return_db_error_info(pt, m_pDBSnapshots, "GetSnapshotPathes",
                                 std::string("cannot get ") + sSnapshothandle );                       
        }
    work = pt_from_json(sJSON) ;
    std::string sTS = work.get("timestamp", "") ;
    if(  ! m_pDBSnapshots -> get (sPathhandle, & sJSON) )
        {
        return return_db_error_info(pt, m_pDBSnapshots, "GetSnapshotPathes",
                                 std::string("cannot get ") + sPathhandle );                       
        }
    ret = pt_from_json(sJSON) ;
    ret.add("timestamp", sTS) ;
    

    return ret;
    
    }

/// Get a list of files for a snapshot
/// pt contains a snapshot handle, returned is an array of files
/// mapping each file to a pathhandle and filehandle
boost::property_tree::ptree SnapshotServerModelKC::GetSnapshotFiles(boost::property_tree::ptree &pt)
    {
    boost::property_tree::ptree ret, work;

    if ( ! has_required_args(pt, "GetSnapshotFiles") )
        return return_error_info(pt, "bad_arguments", "GetSnapshotFiles");

    std::string sPathhandle       = pt.get<std::string>("pathhandle") ;
     
    std::string sJSON ;
    
    if(  ! m_pDBFiles -> get (sPathhandle, & sJSON))
        {
        return return_db_error_info(pt, m_pDBFiles, "GetSnapshotFiles",
                                 std::string("cannot get ") + sPathhandle );                       
        }
    ret = pt_from_json(sJSON) ;
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
        if ( ! m_pDBClients -> add (sSubject, sHandle) )
            {
            return return_error_info(pt, "database_fail", "SetClientHandle");
            }
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
    std::string sSnapshotClienthandle = change_handle(sClienthandle, CLIENT_HANDLE_PREFIX, SNAPSHOT_HANDLE_PREFIX);
    
    // Update snapshots for client
    std::string sJSON ;
    boost::property_tree::ptree ClientSnapshots;
    if(m_pDBSnapshots -> check (sSnapshotClienthandle)>0)
        {
        if ( ! m_pDBSnapshots -> get (sSnapshotClienthandle, &sJSON) )
            {
            return return_db_error_info(pt, m_pDBSnapshots, "AddSnapshot",
                                     std::string("cannot get ") + sSnapshotClienthandle );                       
            }
        ClientSnapshots = pt_from_json(sJSON);
        auto &x = ClientSnapshots.get_child("snapshots");
        boost::property_tree::ptree kid ;
        kid.put("",sSnapshothandle);
        x.push_back(std::make_pair("",kid));
        }
    else
        {
        boost::property_tree::ptree kid, array ;
        kid.put("", sSnapshothandle);
        array.push_back(std::make_pair("", kid)) ;
        ClientSnapshots.add_child("snapshots", array);
        ClientSnapshots.add("clienthandle",sClienthandle);
        }
    
    sJSON = StrUtil::json_from_pt(ClientSnapshots);
    
    if ( ! m_pDBSnapshots -> set (sSnapshotClienthandle, sJSON) )
        {
        return return_db_error_info(pt, m_pDBSnapshots, "AddSnapshot",
                                 std::string("cannot set ") + sSnapshotClienthandle );           
        } ;
    
    boost::property_tree::ptree snapshot;
    snapshot.add("timestamp", sTimestamp);
    snapshot.add("clienthandle", sClienthandle);
    
    sJSON = json_from_pt(snapshot) ;

    if ( ! m_pDBSnapshots -> add (sSnapshothandle, sJSON) )
        {
        return return_db_error_info(pt, m_pDBSnapshots, "AddSnapshot",
                                 std::string("cannot add ") + sClienthandle );   
        }

    snapshot.add("snapshothandle", sSnapshothandle);

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
    std::string sNewPathhandle    = create_handle(PATH_HANDLE_PREFIX) ;
     
    std::string sJSON ;
    boost::property_tree::ptree snapshot;
    
    std::vector<std::string> sPathArray ;
    std::vector<std::string> sHandleArray ;
    if(  m_pDBSnapshots -> get (sPathhandle, & sJSON))
        {
        snapshot = pt_from_json(sJSON) ;
        }
    else
        {
        snapshot.put("snapshothandle", sSnapshothandle);
        StrUtil::StrUtil::add_vector(snapshot, "patharray", sPathArray);
        StrUtil::StrUtil::add_vector(snapshot, "handlearray", sHandleArray);
        }

    StrUtil::get_vector(snapshot, "patharray", sPathArray);
    sPathArray.push_back(sSnapshotPath);

    StrUtil::get_vector(snapshot, "handlearray", sHandleArray);
    sHandleArray.push_back(sNewPathhandle) ;

    snapshot.clear() ;
    snapshot.put("snapshothandle", sSnapshothandle);
    StrUtil::StrUtil::add_vector(snapshot, "patharray", sPathArray);
    StrUtil::StrUtil::add_vector(snapshot, "handlearray", sHandleArray);
    
    sJSON = json_from_pt(snapshot) ;
    if( ! m_pDBSnapshots -> set (sPathhandle, sJSON) )
        {
        return return_error_info(pt, "database_error", "AddSnapshotPath",
                                 m_pDBSnapshots ->error().name() );
        }

    snapshot.put("pathhandle", sNewPathhandle);

    return snapshot;
    }

/// Add a list of files in one path to a snapshot
/// pt contains a snapshot handle, a path handle and a filename
/// returned is a new file handle and maybe a digest for the same
/// file in a previous snapshot
boost::property_tree::ptree SnapshotServerModelKC::AddSnapshotFiles(boost::property_tree::ptree &pt)
    {
    if ( ! has_required_args(pt, "AddSnapshotFiles") )
        return return_error_info(pt, "bad_arguments", "AddSnapshotFiles");

    std::string sSnapshothandle   = pt.get<std::string>("snapshothandle") ;
    std::string sPathhandle       = pt.get<std::string>("pathhandle") ;

    std::vector<std::string> sFileArray ; 
    StrUtil::get_vector(pt, "filenames", sFileArray);

    std::vector<std::string> sFileMetaArray ; 
    StrUtil::get_vector(pt, "filemetainfos", sFileMetaArray);
    
    std::vector<std::string> sFilehandleArray ; 
    for (auto i= sFileArray.begin(); i!= sFileArray.end(); i++)
        {
        sFilehandleArray.push_back(create_handle(FILE_HANDLE_PREFIX)) ;
        }
    size_t nIn = sFileMetaArray.size();
    std::string sJSON ;

    if(  m_pDBFiles -> get (sPathhandle, & sJSON))
        {
        boost::property_tree::ptree Oldsnapshot = pt_from_json(sJSON) ;
        StrUtil::get_vector(Oldsnapshot, "filenames", sFileArray);
        StrUtil::get_vector(Oldsnapshot, "filehandles", sFilehandleArray);
        StrUtil::get_vector(Oldsnapshot, "filemetainfos", sFileMetaArray);
        }

    boost::property_tree::ptree snapshot;

    snapshot.put("snapshothandle", sSnapshothandle);
    snapshot.put("pathhandle", sPathhandle);        

    StrUtil::StrUtil::add_vector(snapshot, "filenames", sFileArray);
    StrUtil::StrUtil::add_vector(snapshot, "filehandles", sFilehandleArray);
    StrUtil::StrUtil::add_vector(snapshot, "filemetainfos", sFileMetaArray);

    
    sJSON = json_from_pt(snapshot) ;
    if( ! m_pDBFiles -> set (sPathhandle, sJSON) )
        {
        return return_db_error_info(pt, m_pDBFiles, "AddSnapshotFiles",
                                 m_pDBSnapshots ->error().name() );
        }

    sFilehandleArray.resize(nIn);
    boost::property_tree::ptree ret;
    StrUtil::add_vector(ret, "filehandles", sFilehandleArray);
    return snapshot;
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

/// construct an error info ptree to be returned onbase error data
/// @var pDB database

/// @var sType database_error
/// @var sLocation  function causing the error
/// @var sInfo (="") additional info 
/// @ret error info ptree
boost::property_tree::ptree SnapshotServerModelKC::return_db_error_info(boost::property_tree::ptree &pt, 
                          kyotocabinet::PolyDB    * pDB ,
                    const std::string &sLocation,
                    const std::string &sInfo)
    {
    std::stringstream sFullInfo;
    sFullInfo << pDB -> path() << ":" << pDB -> error() << "(" << sInfo << ")";
    return return_error_info(pt, "database_error", sLocation, sFullInfo.str()) ;
    }
