/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotLog.cpp
 * Author: klaus
 * 
 * Created on 4. März 2018, 11:48
 */

#include "SnapshotLog.hpp"
#include "SnapshotConfig.hpp"

SnapshotLog::SnapshotLog()
    {
    if ( ! GetDefault() )
        SetDefault(this) ;
    Init();
    }

SnapshotLog::SnapshotLog(const SnapshotLog& orig)
    {
    }

SnapshotLog::~SnapshotLog()
    {
    }

void SnapshotLog::Init() 
    {
    SnapshotConfig *pConfig = SnapshotConfig::GetDefaultConfig() ;
    m_nVerbosity = pConfig -> GetInt("Verbosity", 1) ;
    }

void SnapshotLog::log(int verbosity, const char *str) 
    {
    if ( verbosity <= m_nVerbosity)
        std::cerr << str << "\n" ;
    }

void log(int verbosity, const char *str) 
    {
    SnapshotLog *pLog = 
            SnapshotLog::GetDefault() ;
    if (pLog) 
        pLog -> log(verbosity, str);
    }
void log(int verbosity, const std::string &str) 
    {
    SnapshotLog *pLog = 
            SnapshotLog::GetDefault() ;
    if (pLog) 
        pLog -> log(verbosity, str.c_str());
    }

template<> SnapshotLog * DefaultObject<SnapshotLog>::ms_DefaultObject = NULL ;
