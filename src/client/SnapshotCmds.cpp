/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotCmds.cpp
 * Author: klaus
 * 
 * Created on 1. März 2018, 21:42
 */

#include "SnapshotCmds.hpp"

SnapshotCmds::SnapshotCmds()
    {
    }

SnapshotCmds::SnapshotCmds(const SnapshotCmds& orig)
    {
    }

SnapshotCmds::~SnapshotCmds()
    {
    }

// "{\"action\":\"get\",\"arg\":\"clienthandle\",\"subject\":\"cn=test\"}" ;
std::string SnapshotCmds::GetClienthandle(const std::string &sSubject) 
    {
    std::stringstream sCmd ;
    sCmd << "{\"action\":\"get\",\"arg\":\"clienthandle\",\"subject\":\"" << sSubject << "\"}" ;
    return sCmd.str() ;
    }
