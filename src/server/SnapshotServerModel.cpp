/* 
 * File:   SnapshotServerModel.cpp
 * Author: klaus
 * 
 * Created on 29. Dezember 2017, 11:00
 */

#include "SnapshotServerModel.hpp"
#include "SnapshotServerModelArgs.hpp"
#include "../common/SnapshotException.hpp"
#include "../common/StrUtil.hpp"

using namespace std ;

/* ************************************************************************** */
// Livecycle
SnapshotServerModel::SnapshotServerModel()
    {
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
    std::istringstream sOut(sJSON);
    boost::property_tree::ptree xRet;
    
    boost::property_tree::read_json(sOut, xRet);
    return xRet ;
    
    }

/// Add a list of files in one path to a snapshot
/// pt contains a snapshot handle, a path handle and a filename
/// returned is a new file handle and maybe a digest for the same
/// file in a previous snapshot
/// @var sJSON JSON String to be parsed
/// @ret parsed JSOn ptree
std::string SnapshotServerModel::json_from_pt(boost::property_tree::ptree const &pt) 
    {
    std::ostringstream sOut;
    
    boost::property_tree::write_json(sOut, pt);
    return sOut.str() ;
    
    }

/// construct a simple json key->value list
/// @var str a la "key1;value1;key2;value..."
/// @ret sJSON a la "{key1:value1, key2: ..."
std::string SnapshotServerModel::str2json(const char * str) 
    {
    std::stringstream sJSON ;
    std::string  sIn(str);
    
    sJSON << "{" ;
    while(true)
        {
        }
    sJSON << "}";
    return sJSON.str();
    }

/// Add a string vector to a pt so it is later rendered as a JSON array
void SnapshotServerModel::add_vector(boost::property_tree::ptree &pt,
                    std::string &sArrayName,
                    std::vector<std::string> &sArray)
    {
    boost::property_tree::ptree array;
    
    for ( auto i = sArray.begin(); i != sArray.end(); i++)
        {
        boost::property_tree::ptree kid ;
        kid.put("", *i);
        array.push_back(std::make_pair("", kid));
        }

    pt.add_child(sArrayName, array) ;
    }

/// Add a string vector to a pt so it is later rendered as a JSON array
void SnapshotServerModel::get_vector(boost::property_tree::ptree &pt,
                    std::string &sArrayName,
                    std::vector<std::string> &sArray)
    {
    boost::property_tree::ptree &array = pt.get_child(sArrayName) ;

    for ( auto i = array.begin(); i != array.end(); i++)
        {
        sArray.push_back(i->second.get_value<std::string>());
        }

    pt.add_child(sArrayName, array) ;
    }

/// Check a functions arguments for required args
/// @var args_in Argument pt to be checked
/// @var sFunction - function name 
/// @ret true if args ok, false otherwise
bool SnapshotServerModel::has_required_args(boost::property_tree::ptree &args_in, 
                           const std::string &sFunction)
    {
    auto required = m_xRequiredArgs.get_child(sFunction);
    try {
        for ( auto i=required.begin(); i!= required.end(); i++)
            {
            auto key = i->first ;
            auto val = i->second ;
            auto has = args_in.get<std::string>(key) ;
            if (val == "handle" && (val.length() <9) )
                throw 1;
            }
        }
    catch (...)
        {
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
        kid.add(sType, sInfo); 
    ret.add_child("ERROR", kid) ;
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

