/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotConfig.cpp
 * Author: klaus
 * 
 * Created on 25. Februar 2018, 11:10
 */

#include <fstream>
#include "SnapshotConfig.hpp"
#include "SnapshotException.hpp"
#include "StrUtil.hpp"

SnapshotConfig::SnapshotConfig()
    {
    if ( ! GetDefault() )
        SetDefault(this) ;
    }

SnapshotConfig::SnapshotConfig(const SnapshotConfig& orig)
    {
    }

SnapshotConfig::~SnapshotConfig()
    {
    }

SnapshotConfig * SnapshotConfig::GetDefaultConfig() 
    {
    return ( GetDefault() ? GetDefault() : new SnapshotConfig() ) ;    
    }

void SnapshotConfig::Load(const std::string & sFilename ) 
    {
    std::fstream xIn;
    
    xIn.open(sFilename.c_str(), std::fstream::in);
    
    if(xIn)
        boost::property_tree::read_json(xIn, m_xSettings);
    else
        throw SnapshotException("file_open", sFilename.c_str()) ;

    xIn.close() ;
    
    }

void SnapshotConfig::Save(const std::string & sFilename ) 
    {
    std::fstream xOut;
    
    xOut.open(sFilename.c_str(), std::fstream::out | std::fstream::trunc);
    
    if(xOut)
        boost::property_tree::write_json(xOut, m_xSettings);
    else
        throw SnapshotException("file_open", sFilename.c_str()) ;

    xOut.close() ;
    
    }

std::string SnapshotConfig::GetString(const std::string &sProp) 
    {            
    return m_xSettings.get<std::string>(sProp);
    }
std::vector<std::string> SnapshotConfig::GetStrings(const std::string &sProp) 
    {
    std::vector<std::string> xRet;
    StrUtil::get_vector(m_xSettings, sProp, xRet);
    return xRet ;
    }

int SnapshotConfig::GetInt(const std::string &sProp) 
    {
    return m_xSettings.get<int>(sProp);
    }

std::string SnapshotConfig::GetString(const std::string &sProp, const std::string &sDefault) 
    {            
    return m_xSettings.get<std::string>(sProp, sDefault);
    }

int SnapshotConfig::GetInt(const std::string &sProp, int nDefault) 
    {
    return m_xSettings.get<int>(sProp, nDefault);
    }

std::vector<std::string> SnapshotConfig::GetStrings(const std::string &sProp, 
                                                    const std::vector<std::string> &sItems) 
    {            
    std::vector<std::string> xRet;
    StrUtil::get_vector(m_xSettings, sProp, xRet);
    return xRet ;
    }

void SnapshotConfig::Set(const std::string &sProp, const std::string &sVal) 
    {
    m_xSettings.put(sProp, sVal) ;
    }

void SnapshotConfig::Set(const std::string &sProp, const int nVal) 
    {
    m_xSettings.put(sProp, nVal) ;    
    }

void SnapshotConfig::Set(const std::string & sProp, 
             std::vector<std::string> & sItems) 
    {
    StrUtil::set_vector(m_xSettings, sProp, sItems);
    }

void SnapshotConfig::InitClientDefaults() 
    {
    Set("ServerURL", "http://127.0.0.1:8088") ;
    }

void SnapshotConfig::InitServerDefaults() 
    {
    Set("Timeout", 10) ;    
    }


template<> SnapshotConfig * DefaultObject<SnapshotConfig>::ms_DefaultObject = NULL ;