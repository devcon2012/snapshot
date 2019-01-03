/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotCmdResponse.cpp
 * Author: klaus
 * 
 * Created on 1. März 2018, 21:42
 */

#include "SnapshotCmdResponse.hpp"
#include "SnapshotCmds.hpp"
#include "../common/StrUtil.hpp"

SnapshotCmdResponse::SnapshotCmdResponse()
    {
    }

SnapshotCmdResponse::SnapshotCmdResponse(const std::string &sJson)
    {
    SetResponse(sJson) ;
    }

SnapshotCmdResponse::SnapshotCmdResponse(const SnapshotCmdResponse& orig)
    {
    SetResponse(orig.GetResponse());
    }

SnapshotCmdResponse::~SnapshotCmdResponse()
    {
    }

std::string SnapshotCmdResponse::GetClienthandle(const std::string &sJsonResponse) 
    {
    SetResponse(sJsonResponse) ;
    return m_xPTree.get<std::string>("clienthandle") ;
    }

bool SnapshotCmdResponse::IsError(const std::string &sJsonResponse)
    {
    SetResponse(sJsonResponse) ;
    try
        {
        m_xPTree.get_child("Error");
        return true ;
        }
    catch (...)
        {
        return false ;
        }
    }

void SnapshotCmdResponse::SetResponse(const std::string &sJsonResponse) 
    {
    if(sJsonResponse.length()>0)
        m_xPTree = StrUtil::pt_from_json(sJsonResponse) ;
    }


std::string SnapshotCmdResponse::ErrorMessage(const std::string &sJsonResponse) 
    {
    SetResponse(sJsonResponse) ;
    return SnapshotCmds::ErrorMessage(m_xPTree) ;
    }

