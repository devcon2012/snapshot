/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseCertificate.hpp
 * Author: klaus
 *
 * Created on 22. Dezember 2018, 13:10
 */

#ifndef BASECERTIFICATE_HPP
#define BASECERTIFICATE_HPP

#include <stdlib.h>

#include "openssl/x509.h"

#include "Key.hpp"
#include "Issuer.hpp"
#include "Subject.hpp"

class CACertificate ;

class BaseCertificate 
    {
    public:
        BaseCertificate();
        BaseCertificate(X509 *);
        BaseCertificate(const BaseCertificate& orig);
        virtual ~BaseCertificate();

        virtual bool                    HasPrivKey() const ;
        virtual const Key             * GetKey() const ;
        virtual void                    SetKey(const Key &privKey) ;
        virtual const Subject         * GetSubject() const ;
        virtual const Issuer          * GetIssuer() const ;
        virtual const CACertificate   * GetIssuerCA() const ;

        virtual void                    LoadPEM(std::string const &fn) ;
        virtual void                    LoadPEM(std::istream &s) ;
        virtual void                    SavePEM(std::string const &fn) const ;
        virtual void                    SavePEM(std::ostream &s) const ; 
        
    protected:
        Key const   * m_pPrivKey ;
        X509        * m_pX509 ;
        
        void Init() ;
        void Clean() ;
        static int cb(char *buf, int size, int rwflag, void *u) ;

    } ;

#endif /* BASECERTIFICATE_HPP */

