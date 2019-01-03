/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   I18N.hpp
 * Author: klaus
 *
 * Created on 25. Dezember 2017, 23:13
 */

#ifndef I18N_HPP
#define I18N_HPP

#include <map>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "DefaultObject.hpp"
#include "GenericException.hpp"

/** I18N collects I18N strings for one language
 */
class I18NCollector ;
class I18N : public DefaultObject<I18N>
    {
    friend class I18NCollector ;
public:
    using Callback = void (*)(const std::string &stag, const std::string &sLang) ;

    I18N(const char * sLang, Callback c = NULL) ;
    I18N(const I18N &orig) ;
    virtual ~I18N() ;

    /// Interpolate I18N string tagged sType with args and return
    std::string interpolate(const char *sType, const char *sArg1=NULL, const char *sArg2=NULL) ;

    /// Get the lang of this objects
    std::string GetLang() const { return m_sLang ; }

    /// Get the file used for loading
    std::string GetFile() const { return m_sFile ; }
    void SetFile(const std::string &sFile) { m_sFile = sFile; }
    
    /// add a tag / I18N to this lang
    void addTag(const std::string &sTag, const std::string &sText) ;
    
    /// load I18N as jsonfcrom the file specified    
    void load(const std::string &sFile) ;

    /// save I18N as json to the file used for reading previousely
    void save() const ;
    
    /// MissingCallback is called when a tag is not found
    /// default is to throw an exception
    void SetMissingI18NCallback( I18N::Callback c ) { m_xCallback = c; } ;
    
    void SetAsDefault() { SetDefault(this) ; }
    
    /// Get default I18N Object 
    static I18N * GetDefaultI18N() ;

    /// Interpolate I18N string in default lang tagged sType with args and return
    static std::string I18N_interpolate(const char *sType, const char *sArg1=NULL, const char *sArg2=NULL) ;
    
private:
    std::string get_raw(const std::string &sTag) const ;
    
    boost::property_tree::ptree         m_xMapping ;
    std::string                         m_sLang ;
    std::string                         m_sFile ;
    Callback                            m_xCallback ;
    
    } ;

/** I18NCollector collects available I18N objects.
 *  
 */
class I18NCollector : public DefaultObject<I18NCollector> 
    {
public:
    I18NCollector(const std::string & sRoot) ;
    I18NCollector(const I18N &orig) ;
    virtual ~I18NCollector() ;
    void Init() ;
    
    static I18NCollector * GetI18NCollector(const std::string & sRoot = std::string("")) ;
    I18N * GetI18N(const std::string &sLang) ;
    
    void newI18N(const std::string &sLang) ;
    
    void SetMissingI18NCallback( I18N::Callback c ) ;
protected :
    std::map<std::string, I18N *>   m_xMapping ;
    std::string                     m_sRootDir ;
    I18N::Callback                  m_xCallback ;
    } ;
#endif /* I18N_HPP */

