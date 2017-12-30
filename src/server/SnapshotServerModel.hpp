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
    
    virtual std::string create_handle() ;
    
    virtual boost::property_tree::ptree pt_from_json(std::string sJSON) ;

    
  protected:

    virtual void build_required_args();
    virtual boost::property_tree::ptree required_args(const std::string &sFunction);

    virtual bool has_required_args(boost::property_tree::ptree &pt, 
                           boost::property_tree::ptree const & required);

    virtual void return_error_info(boost::property_tree::ptree &pt, 
                        std::string &sType,
                        std::string &sInfo);

    virtual void add_vector(boost::property_tree::ptree &pt,
                        std::string &sArrayName,
                        std::vector<std::string> &sArray);
    
    
    boost::property_tree::ptree m_xRequiredArgs ;

        /// Root path containing Database files
    std::string               m_sDBRoot ;

        /// Root path containing Snapshotted files
    std::string               m_sSnaphotFilesRoot ;
    
};

#endif /* SNAPSHOTSERVERMODEL_HPP */

