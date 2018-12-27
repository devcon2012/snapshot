/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Initializer.cpp
 * Author: klaus
 * 
 * Created on 22. Dezember 2018, 14:27
 */

#include <stdio.h>

#include "openssl/err.h"
#include "openssl/evp.h"
#include "openssl/rand.h"

#include "Initializer.hpp"
#include "OpenSSLException.hpp"

Initializer * Initializer::m_pInitializer = NULL ;

Initializer * Initializer::GetInitializer() 
    {
    if ( m_pInitializer )
        return m_pInitializer ;
    else
        return new Initializer() ;
    }

Initializer::Initializer()
    {
    OpenSSLInitializer() ;
    }


Initializer::~Initializer()
    {
    }

void Initializer::OpenSSLInitializer() 
    {
    ERR_load_crypto_strings() ;    
    OpenSSL_add_all_algorithms() ;
    
    char rndfn[256] ;
    if ( ! RAND_file_name(rndfn, sizeof(rndfn) ) )
        throw OpenSSLException() ;
    
    if ( RAND_load_file(rndfn, 100) < 0 )
        throw OpenSSLException() ;
    
    }
