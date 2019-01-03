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

I18N::I18N(const char * sLangp, Callback c /* = NULL */ )
    {
    m_sLang = std::string(sLangp) ;
    m_xCallback = c ;
    }

I18N::I18N(const I18N& orig)
    {
    m_sLang = orig.m_sLang ;
    m_xCallback = orig.m_xCallback ;
    }

I18N::~I18N()
    {
    } 

std::string I18N::get_raw(const std::string &sTag) const 
    {
    std::string sRaw = m_xMapping.get<std::string>(sTag, "") ;
    
    if (sRaw.length() == 0)
        {
        sRaw = std::string(sTag) + " (I18N MISSING): %1 %2" ;
        if ( m_xCallback )
            m_xCallback(sTag, m_sLang) ;
        }
    return sRaw ;
    }

void I18N::addTag(const std::string &sTag, const std::string &sText) 
    {
    if ( ! m_xMapping.get_child_optional(sTag)  )
        {
        m_xMapping.add<std::string>(sTag, sText) ;
        }
    else
        {
        m_xMapping.put<std::string>(sTag, sText) ;
        }
    
    save();
  
    }

void I18N::load(const std::string &sFile) 
    {
    m_sFile = sFile ;
    m_xMapping = StrUtil::pt_from_json_file(sFile) ;
    }

/// save I18N as json to the file used for reading previousely
void I18N::save() const 
    {
    if ( m_sFile.length() > 0 )
        {
        std::fstream out ;
        out.open(m_sFile, std::ios_base::out) ;
        StrUtil::dump_pt(out, m_xMapping) ;
        out.close() ;
        }
    }
    
std::string I18N::interpolate(const char *sType, 
                              const char *sArg1p /* =NULL */,
                              const char *sArg2p /* =NULL */ ) 
    {
    std::string sRet, sArg1(sArg1p?sArg1p:""), sArg2(sArg2p?sArg2p:"");
    
    sRet = get_raw(sType) ;
    
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
template<> I18NCollector * DefaultObject<I18NCollector>::ms_DefaultObject = NULL ;

 I18NCollector * I18NCollector::GetI18NCollector(const std::string & sRoot /* = std::string("") */ ) 
    {
    return GetDefault() ? GetDefault() : new I18NCollector(sRoot) ;
    }

I18NCollector::I18NCollector(const std::string &sRoot) 
    {
    m_sRootDir = sRoot ;
    
    I18N * i18n_de = new I18N("de") ;
    m_xMapping["de"] = i18n_de ;
    std::string sFile = sRoot + "/i18n.de" ;
    i18n_de->load(sFile) ;
    
    I18N * i18n_en = new I18N("en") ;
    m_xMapping["en"] = i18n_en ;
    sFile = sRoot + "/i18n.en" ;
    i18n_en->load(sFile) ;
    
    SetDefault(this) ;
    i18n_de->SetAsDefault();
    }

I18NCollector::I18NCollector(const I18N &orig) 
    {
    
    }

I18NCollector::~I18NCollector() 
    {
    
    }

void I18NCollector::Init()
    {
    
    }
    
I18N * I18NCollector::GetI18N(const std::string &sLang)
    {
    return m_xMapping[sLang] ;
    }

void I18NCollector::newI18N(const std::string &sLang)
    {
    I18N * i18n = new I18N(sLang.c_str()) ;
    m_xMapping[sLang] = i18n ;
    std::string sFile = m_sRootDir + "/i18n." + sLang ;
    i18n->SetFile(sFile) ;
    }
    
void I18NCollector::SetMissingI18NCallback( I18N::Callback c ) 
    {
    m_xCallback = c ;
    
    for ( auto i=m_xMapping.begin(); i!=m_xMapping.end() ; i++ )
        {
        i->second->SetMissingI18NCallback(c);
        }
    }
    