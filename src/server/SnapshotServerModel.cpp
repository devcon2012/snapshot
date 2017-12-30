/* 
 * File:   SnapshotServerModel.cpp
 * Author: klaus
 * 
 * Created on 29. Dezember 2017, 11:00
 */

#include "SnapshotServerModel.hpp"
#include "SnapshotServerModelArgs.hpp"
#include "../common/SnapshotException.hpp"

using namespace std ;

SnapshotServerModel::SnapshotServerModel()
    {
    
    build_required_args() ;

    m_sDBRoot               = "." ;
    
    }

SnapshotServerModel::SnapshotServerModel(const SnapshotServerModel& orig)
    {
    }

SnapshotServerModel::~SnapshotServerModel()
    {
    }


/// Add a list of files in one path to a snapshot
/// pt contains a snapshot handle, a path handle and a filename
/// returned is a new file handle and maybe a digest for the same
/// file in a previous snapshot
boost::property_tree::ptree SnapshotServerModel::pt_from_json(std::string sJSON) 
    {
    std::istringstream sOut(sJSON);
    boost::property_tree::ptree xRet;
    
    boost::property_tree::read_json(sOut, xRet);
    return xRet ;
    
    }

boost::property_tree::ptree SnapshotServerModel::required_args(const std::string &sFunction) 
    {
    return m_xRequiredArgs.get<boost::property_tree::ptree>(sFunction) ;
    }

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

bool SnapshotServerModel::has_required_args(boost::property_tree::ptree &pt, 
                       boost::property_tree::ptree const & required)
    {
    for ( auto i=required.begin(); i!= required.end(); i++)
        {
        std::string sKey    = (*i).first.;
        std::string sType   = (*i).second;
        if( pt.find(sKey) == pt.not_found() )
            return false;
        }
    return true;
    }

void SnapshotServerModel::return_error_info(boost::property_tree::ptree &pt, 
                    std::string &sType,
                    std::string &sInfo)
    {
    boost::property_tree::ptree kid ;
    kid.put(sType, sInfo); 
    pt.add_child("ERROR", kid) ;
    }

void SnapshotServerModel::build_required_args()
    {
    m_xRequiredArgs = pt_from_json(sRequiredArgs) ;
    }

std::string SnapshotServerModel::create_handle()
    {
    std::stringstream sHandle ;
    sHandle << std::setfill('0') << std::setw(8) << std::hex << rand() << "-" << time(NULL) ;
    return sHandle.str() ;
    }
