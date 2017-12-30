/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   I18N.cpp
 * Author: klaus
 * 
 * Created on 25. Dezember 2017, 23:13
 */

#include "I18N.hpp"
#include "StrUtil.hpp"
#include "SnapshotException.hpp"

I18N::I18N(const char * sLangp)
    {
    std::string sLang(sLangp) ;
    if ( sLang == "de" )
        {
        m_xMapping["test_i18n"] = "I18N TEST: %1 %2" ;
        m_xMapping["directory_read"] = "Fehler beim lesen von %2: %1" ;
        }
    else
        {
        std::string sMsg("Invalid language: ");
        throw SnapshotException(sMsg + std::string(sLangp));
        }
    }

I18N::I18N(const I18N& orig)
    {
    }

I18N::~I18N()
    {
    } 

std::string I18N::interpolate(const char *sType, 
                              const char *sArg1p /* =NULL */,
                              const char *sArg2p /* =NULL */ ) 
    {
    std::string sRet, sArg1(sArg1p?sArg1p:""), sArg2(sArg2p?sArg2p:"");
    
    sRet = m_xMapping[sType] ;
    if (sRet.length() == 0)
        sRet = std::string(sType) + " (I18N MISSING): %1 %2" ;
    
    sRet = StrUtil::StrSubst(sRet, "%1", sArg1);
    sRet = StrUtil::StrSubst(sRet, "%2", sArg2);
    
    return sRet;
    }

std::string I18N::I18N_interpolate(const char *sType, 
                                   const char *sArg1p /* =NULL */,
                                   const char *sArg2p /* =NULL */ ) 
    {
    I18N * pDefault = GetDefaultI18N() ;

    return pDefault -> interpolate(sType, sArg1p, sArg2p);    
    }

 I18N * I18N::GetDefaultI18N() 
    {
    return ( GetDefault() ? GetDefault() : new I18N("de")) ;
    }

template<> I18N * DefaultObject<I18N>::ms_DefaultObject = NULL ;