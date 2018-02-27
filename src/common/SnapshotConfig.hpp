/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotConfig.hpp
 * Author: klaus
 *
 * Created on 25. Februar 2018, 11:10
 */

#ifndef SNAPSHOTCONFIG_HPP
#define SNAPSHOTCONFIG_HPP

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "DefaultObject.hpp"

class SnapshotConfig : public DefaultObject<SnapshotConfig> 
{
public:
    SnapshotConfig() ;
    SnapshotConfig(const SnapshotConfig& orig) ;
    virtual ~SnapshotConfig() ;
    
    static SnapshotConfig * GetDefaultConfig() ;

    virtual void InitClientDefaults() ;
    virtual void InitServerDefaults() ;
    
    virtual void Load(const std::string & sFilename ) ;
    virtual void Save(const std::string & sFilename ) ;

    virtual std::string GetString(const std::string &sProp) ;
    virtual int GetInt(const std::string &sProp) ;
    virtual std::vector<std::string> GetStrings(const std::string &sProp) ;
    
    virtual std::string GetString(const std::string &sProp, 
            const std::string &sDefault) ;
    virtual int GetInt(const std::string &sProp, int nDefault) ;
    virtual std::vector<std::string> GetStrings(const std::string &sProp,
            const std::vector<std::string> & sItems) ;
    
    virtual void Set(const std::string &sProp, const std::string &sVal) ;
    virtual void Set(const std::string &sProp, const int nVal) ;
    virtual void Set(const std::string &sProp, 
             std::vector<std::string> & sItems) ;
    
private:

    boost::property_tree::ptree m_xSettings ;
    
};

#endif /* SNAPSHOTCONFIG_HPP */

