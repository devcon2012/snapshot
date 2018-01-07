/* 
 * File:   SnapshotServerModel.cpp
 * Author: klaus
 * 
 * Created on 29. Dezember 2017, 11:00
 */

#include <iostream>

#include "SnapshotServerModel.hpp"
#include "SnapshotServerModelArgs.hpp"
#include "../common/SnapshotException.hpp"
#include "../common/StrUtil.hpp"

using namespace std ;

/* ************************************************************************** */
// Livecycle
SnapshotServerModel::SnapshotServerModel()
    {
    srand(time(NULL)) ;
    build_required_args() ;
    }

SnapshotServerModel::SnapshotServerModel(const SnapshotServerModel& orig)
    {
    }

SnapshotServerModel::~SnapshotServerModel()
    {
    }

/* ************************************************************************** */
// Helpers

/// Add a list of files in one path to a snapshot
/// pt contains a snapshot handle, a path handle and a filename
/// returned is a new file handle and maybe a digest for the same
/// file in a previous snapshot
/// @var sJSON JSON String to be parsed
/// @ret parsed JSOn ptree
boost::property_tree::ptree SnapshotServerModel::pt_from_json(std::string const &sJSON) 
    {
    return StrUtil::pt_from_json(sJSON) ;
    }

/// Add a list of files in one path to a snapshot
/// pt contains a snapshot handle, a path handle and a filename
/// returned is a new file handle and maybe a digest for the same
/// file in a previous snapshot
/// @var sJSON JSON String to be parsed
/// @ret parsed JSOn ptree
std::string SnapshotServerModel::json_from_pt(boost::property_tree::ptree const &pt) 
    {
    return StrUtil::json_from_pt(pt) ;
    }

/// construct a simple json key->value list
/// @var str a la "key1;value1;key2;value..."
/// @ret sJSON a la "{key1:value1, key2: ..."
std::string SnapshotServerModel::str2json(const char ** str, int n) 
    {
    return StrUtil::str2json(str, n) ;
    }



/// Check a functions arguments for required args
/// @var args_in Argument pt to be checked
/// @var sFunction - function name 
/// @ret true if args ok, false otherwise
bool SnapshotServerModel::has_required_args(boost::property_tree::ptree &args_in, 
                           const std::string &sFunction)
    {
    auto required = m_xRequiredArgs.get_child(sFunction);
    std::string key ;
    try {
        for ( auto i=required.begin(); i!= required.end(); i++)
            {
            key = i->first ;
            auto val = i->second.data() ;
            auto has = args_in.get<std::string>(key) ;
            if (val == "handle" && (has.length() <9) )
                throw std::string("bad handle ") + has + " for " + key;   
            
            }
        }
    catch (std::string e)
        {
        args_in.add("ERROR", e);
        return false ;
        }
    catch (...)
        {
        args_in.add("ERROR", std::string("missing ") + key);
        return false ;
        }
    
    return true;
    }

/// construct an error info ptree to be returned
/// @var sType type of error, used for I18N
/// @var sLocation  function causing the error
/// @var sInfo (="") additional info 
/// @ret error info ptree
boost::property_tree::ptree SnapshotServerModel::return_error_info(boost::property_tree::ptree &pt, 
                    const std::string &sType,
                    const std::string &sLocation,
                    const std::string &sInfo)
    {
    boost::property_tree::ptree kid ;
    boost::property_tree::ptree ret ;
    kid.put(sType, sLocation);
    if(sInfo.length()>0)
        kid.add(sType, sInfo); 
    std::string sReason = pt.get("ERROR", "") ;
    if( sReason.length()>0)
        kid.add(sType, sReason); 
    ret.add_child("ERROR", kid) ;
    
    std::cerr << "ERROR: " << sType << " - " << sLocation << " - " << sInfo 
            << " - " << sReason << "\n" ;
    return ret ;
    }

/// populate the m_xRequiredArgs ptree 
void SnapshotServerModel::build_required_args()
    {
    m_xRequiredArgs = pt_from_json(sRequiredArgs) ;
    }

/// create a new unique handle
/// @var prefix optional handle prefix
/// @ret new unique handle
std::string SnapshotServerModel::create_handle(const char * prefix)
    {
    std::stringstream sHandle ;
    sHandle << (prefix ? prefix : "" ) << std::setfill('0') << std::setw(8) << std::hex << rand() << "-" << time(NULL) ;
    return sHandle.str() ;
    }

/// create a new unique handle
/// @var prefix optional handle prefix
/// @ret new unique handle
std::string SnapshotServerModel::change_handle(const char *handle, const char * old_prefix, const char * new_prefix)
    {
    std::string sHandle(handle) ;
    
    return StrUtil::StrSubst(sHandle, old_prefix, new_prefix);

    }

