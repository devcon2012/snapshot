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

#ifndef SNAPSHOTSERVERMODEL_HPP
#define SNAPSHOTSERVERMODEL_HPP

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>


class SnapshotServerModel  {
public:
    SnapshotServerModel();
    SnapshotServerModel(const SnapshotServerModel& orig);
    virtual ~SnapshotServerModel();
    
    /// The Model must be provisioned before being used
    virtual void Provision(boost::property_tree::ptree &pt) {}
    
    /// Release resources etc.
    virtual void Cleanup() {}
    
    // Getter
    // Get a handle for a client
    virtual boost::property_tree::ptree GetClientHandle(boost::property_tree::ptree &pt) = 0;
    
    // Get a list of Snaphots we have
    virtual boost::property_tree::ptree GetSnapshots(boost::property_tree::ptree &pt) = 0;

    // Get a list of pathes for a snapshot
    virtual boost::property_tree::ptree GetSnapshotPathes(boost::property_tree::ptree &pt) = 0;
    
    // Get a list of files for a snapshot
    virtual boost::property_tree::ptree GetSnapshotFiles(boost::property_tree::ptree &pt) = 0;

    
    // Setter    
    // Set a handle for a client
    virtual boost::property_tree::ptree SetClientHandle(boost::property_tree::ptree &pt) = 0;
    
    // Add a  Snaphots
    virtual boost::property_tree::ptree AddSnapshot(boost::property_tree::ptree &pt) = 0;

    // Add a path to a snapshot
    virtual boost::property_tree::ptree AddSnapshotPath(boost::property_tree::ptree &pt) = 0;
    
    // Add a list of files in one path to a snapshot
    virtual boost::property_tree::ptree AddSnapshotFiles(boost::property_tree::ptree &pt) = 0;
    
    virtual std::string create_handle(const char * prefix=NULL) ;
    virtual std::string change_handle(const char *handle, const char * old_prefix, const char * new_prefix) ;
    virtual std::string change_handle(const std::string &sHandle, const char * old_prefix, const char * new_prefix) 
            { return change_handle(sHandle.c_str(), old_prefix, new_prefix); } 
    
    virtual std::string str2json(const char ** str, int n=0) ;
    virtual boost::property_tree::ptree pt_from_json(std::string const &sJSON) ;
    virtual std::string json_from_pt(boost::property_tree::ptree const &pt)  ;
 
    
  protected:

    virtual void build_required_args();

    virtual bool has_required_args(boost::property_tree::ptree &args_in, 
                           const std::string &sFunction);

    virtual boost::property_tree::ptree return_error_info(boost::property_tree::ptree &pt, 
                        const std::string &sType,
                        const std::string &sLocation,
                        const std::string &sInfo=""
                        );    
    
    boost::property_tree::ptree m_xRequiredArgs ;

        /// Root path containing Database files
    std::string               m_sDBRoot ;

        /// Root path containing Snapshotted files
    std::string               m_sSnaphotFilesRoot ;
    
};

#endif /* SNAPSHOTSERVERMODEL_HPP */

