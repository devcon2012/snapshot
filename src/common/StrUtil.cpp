/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StrUtil.cpp
 * Author: klaus
 * 
 * Created on 27. Dezember 2017, 11:28
 */

#include "StrUtil.hpp"

StrUtil::StrUtil()
    {
    }

StrUtil::StrUtil(const StrUtil& orig)
    {
    }

StrUtil::~StrUtil()
    {
    }

std::string StrUtil::StrSubst(const std::string &sIn, 
                     const std::string &sOld,
                     const std::string &sNew)
    {
    std::string sRet = sIn ;
    
    size_t i = sIn.find(sOld, 0) ;
    
    if( i != std::string::npos )
        {
        sRet.replace(i, sOld.length(), sNew);
        }

    return sRet ;
    }

std::string StrUtil::StrSubstAll(const std::string &sIn,
                        const std::string &sOld, 
                        const std::string &sNew)
    {
    std::string sRet =sIn;
    
    for(size_t i = 0; (i = sRet.find(sOld, i)) != std::string::npos;)
        {
        sRet.replace(i, sOld.length(), sNew);
        i += sNew.length();
        }

    return sRet ;    
    }
