/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Key.cpp
 * Author: klaus
 * 
 * Created on 22. Dezember 2018, 13:25
 */
#include <cstring>
#include <fstream>
#include <openssl/rsa.h>
#include <openssl/pem.h>

#include "Key.hpp"
#include "Initializer.hpp"
#include "OpenSSLException.hpp"
#include "GenericException.hpp"


void Key::Init(bool first)
    {
    m_pInitializer      = Initializer::GetInitializer();
    m_bPrivKey          = false ;
    m_pRSA              = NULL ;
    m_pKey              = NULL ;
    m_sPassWord         = "secret" ;
    
    if ( first )
        {
        m_pExponent         = BN_new();
        if ( ! m_pExponent )
            throw MemoryException() ;
        unsigned long f4 = 0x10001 ;
        BN_set_word(m_pExponent, f4) ;
        }
    }

void Key::Clean()
    {
    if ( m_pRSA )
        RSA_free(m_pRSA) ;
    m_pRSA = NULL ;
    
    if ( m_pKey )
        EVP_PKEY_free (m_pKey) ;
    m_pKey = NULL ;
    
    /* if ( m_pExponent )
        BN_free (m_pExponent) ;
    m_pExponent = NULL ; */

    m_bPrivKey          = false ;
    
    }

Key::Key()
    {
    Init(true) ;
    }

Key::Key(const Key& orig)
    {
    Init(true) ;
    }

Key::~Key()
    {
    Clean() ;
    if ( m_pExponent )
        BN_free (m_pExponent) ;
    m_pExponent = NULL ; 
    }

int Key::Size() const
    {
    if ( m_pRSA ) 
        {
        return RSA_size(m_pRSA) ;
        }
    else
        return -1 ;
    }

std::string Key::Fingerprint() const
    {
    return std::string("TODO") ;
    }

int Key::cb(char *buf, int size, int rwflag, void *u)
    {
    Key * self = (Key * ) u ;
    std::string pw = self ->m_sPassWord ;
    strncpy(buf, pw.c_str(), size) ;
    return pw.length() ;
    }

void Key::LoadPEM(std::string const &fn, std::string const &pass) 
    {
    std::fstream s;
    s.open(fn, std::ios_base::in) ;
    if ( s.fail() )
        throw SysException( fn.c_str() ) ;
    LoadPEM(s) ;
    s.close() ;
    }

void Key::LoadPEM(std::istream &s, std::string const &pass) 
    {
    Clean() ;
    std::string pem( (std::istreambuf_iterator<char>(s)), std::istreambuf_iterator<char>() );

    BIO *bio = BIO_new_mem_buf(pem.c_str(), pem.length() ) ;
    m_pRSA = PEM_read_bio_RSAPrivateKey(bio, NULL, cb, this) ;
    BIO_free(bio) ;
    
    m_bPrivKey = true ;
    }

void Key::SavePEM(std::string const &fn, std::string const &pass) const
    {
    std::fstream s;
    s.open(fn, std::ios_base::out) ;
    SavePEM(s) ;
    s.close() ;
    }

void Key::SavePEM(std::ostream &s, std::string const &pass) const
    {
    BIO *bio = BIO_new(BIO_s_mem()) ;
    const EVP_CIPHER *enc = EVP_aes_256_cbc() ;
    PEM_write_bio_RSAPrivateKey(bio, m_pRSA, enc, NULL, 0, cb, (void *) this) ;
    char *buf ;
    long siz = BIO_get_mem_data(bio, &buf) ;
    s.write(buf, siz) ;
    BIO_free(bio) ;
    }

void Key::NewRSA(int size)
    {
    Clean() ;
    m_pRSA = RSA_new() ;
    if ( ! m_pRSA )
        throw MemoryException() ;
                
    if ( RSA_generate_key_ex(m_pRSA, size, m_pExponent, NULL) == 0 )
        {
        throw OpenSSLException() ;
        }
    m_bPrivKey = true ;
    
    }

bool Key::hasPrivKey() const
    {
    return m_bPrivKey ;
    }

