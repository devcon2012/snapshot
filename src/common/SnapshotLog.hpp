/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotLog.hpp
 * Author: klaus
 *
 * Created on 4. März 2018, 11:48
 */

#ifndef SNAPSHOTLOG_HPP
#define SNAPSHOTLOG_HPP

#include <string>
#include <iostream>

#include "DefaultObject.hpp"

class SnapshotLog  : public DefaultObject<SnapshotLog> 
{
public:
    SnapshotLog();
    SnapshotLog(const SnapshotLog& orig);
    virtual ~SnapshotLog(); ;
    
    void Init() ;
    void log(int verbosity, const char *str) ;
    
private:
    int m_nVerbosity ; 
    
};

void log(int verbosity, const char *str) ;
void log(int verbosity, const std::string &str) ;

#endif /* SNAPSHOTLOG_HPP */

