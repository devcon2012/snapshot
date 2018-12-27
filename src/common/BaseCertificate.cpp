/* 
 * File:   BaseCertificate.cpp
 * Author: klaus
 * 
 * Created on 22. Dezember 2018, 13:10
 */

#include <cstring>
#include <fstream>

#include <openssl/pem.h>

#include "BaseCertificate.hpp"
#include "GenericException.hpp"

void BaseCertificate::Init()
    {
    }

void BaseCertificate::Clean()
    {
    }

BaseCertificate::BaseCertificate()
    {
    Init() ;
    }

BaseCertificate::BaseCertificate(const BaseCertificate& orig)
    {
    Init() ;
    }

BaseCertificate::~BaseCertificate()
    {
    Clean() ;
    }

bool BaseCertificate::HasPrivKey() const
    {
    return m_pPrivKey ;
    }

const Key * BaseCertificate::GetKey() const
    {
    return m_pPrivKey ;
    }

int BaseCertificate::cb(char *buf, int size, int rwflag, void *u)
    {
    // Key * self = (Key * ) u ;
    std::string pw = "" ;
    strncpy(buf, pw.c_str(), size) ;
    return pw.length() ;
    }

void BaseCertificate::LoadPEM(std::string const &fn) 
    {
    std::fstream s;
    s.open(fn, std::ios_base::in) ;
    if ( s.fail() )
        throw SysException( fn.c_str() ) ;
    LoadPEM(s) ;
    s.close() ;
    }

void BaseCertificate::LoadPEM(std::istream &s) 
    {
    Clean() ;
    std::string pem( (std::istreambuf_iterator<char>(s)), std::istreambuf_iterator<char>() );

    BIO *bio = BIO_new_mem_buf(pem.c_str(), pem.length() ) ;
   // m_pX509 = PEM_read_bio_X509(bio, NULL, cb, this) ;
    m_pX509 = PEM_read_bio_X509(bio, NULL, NULL, NULL) ;
    BIO_free(bio) ;
    }

void BaseCertificate::SavePEM(std::string const &fn) const
    {
    std::fstream s;
    s.open(fn, std::ios_base::out) ;
    if ( s.fail() )
        throw SysException( fn.c_str() ) ;
    SavePEM(s) ;
    s.close() ;
    }

void BaseCertificate::SavePEM(std::ostream &s) const
    {
    BIO *bio = BIO_new(BIO_s_mem()) ;
    PEM_write_bio_X509(bio, m_pX509) ;
    char *buf ;
    long siz = BIO_get_mem_data(bio, &buf) ;
    s.write(buf, siz) ;
    BIO_free(bio) ;
    }

void BaseCertificate::SetKey(const Key &privKey) 
    {
    
    }

const Subject * BaseCertificate::GetSubject() const 
    {
    return NULL ;    
    }

const Issuer * BaseCertificate::GetIssuer() const 
    {
    return NULL ;    
    }

const CACertificate * BaseCertificate::GetIssuerCA() const 
    {
    return NULL ;
    }
