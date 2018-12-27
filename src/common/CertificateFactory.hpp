/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CertificateFactory.hpp
 * Author: klaus
 *
 * Created on 22. Dezember 2018, 13:15
 */

#ifndef CERTIFICATEFACTORY_HPP
#define CERTIFICATEFACTORY_HPP

#include "ServerCertificate.hpp"
#include "CACertificate.hpp"

class CertificateFactory {
public:
    CertificateFactory();
    CertificateFactory(const CertificateFactory& orig);
    virtual ~CertificateFactory();
    
    /* */
    virtual ServerCertificate * NewServerCertificate() ;
    virtual CACertificate * NewCACertificate() ;
    
    void SetIssuer(CACertificate &issuer);
    void SetProp(const char * prop, const char *val) ;
    void SetProp(const char * prop, int val) ;
    int  GetIntProp(const char * prop) ;
    const char * GetCharProp(const char * prop) ;
    int  GetIntProp(const char * prop, int defaultint) ;
    const char * GetCharProp(const char * prop, const char * defaultcstr) ;
    
private:

};

#endif /* CERTIFICATEFACTORY_HPP */

