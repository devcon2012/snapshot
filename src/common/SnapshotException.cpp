/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotException.cpp
 * Author: klaus
 * 
 * Created on 25. Dezember 2017, 23:05
 */

#include "SnapshotException.hpp"
#include "I18N.hpp"

SnapshotException::SnapshotException(const std::string &sArg) noexcept
    {
    m_sMessage = sArg ;
    }

SnapshotException::SnapshotException(const char * sType, const char * sArg1, const char * sArg2) noexcept
    {
    m_sMessage = I18N::I18N_interpolate(sType, sArg1, sArg2) ;
    }


SnapshotException::SnapshotException(const SnapshotException& orig) noexcept
    {
    }

SnapshotException::~SnapshotException() noexcept
    {
    }

