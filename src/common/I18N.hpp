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

#include "DefaultObject.hpp"

class I18N : public DefaultObject
    {
public:
    I18N(const char * sLang) ;
    I18N(const I18N& orig) ;
    virtual ~I18N() ;
    
    std::string interpolate(const char *sType, const char *sArg1=NULL, const char *sArg2=NULL) ;

    static I18N * GetDefaultI18N() ;
    static std::string I18N_interpolate(const char *sType, const char *sArg1=NULL, const char *sArg2=NULL) ;
    
private:

    std::map<std::string, std::string> m_xMapping ;

    } ;

#endif /* I18N_HPP */

