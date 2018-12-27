/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OpenSSLException.cpp
 * Author: klaus
 * 
 * Created on 22. Dezember 2018, 20:53
 */

#include <sstream>
#include "openssl/err.h"

#include "OpenSSLException.hpp"

OpenSSLException::OpenSSLException() noexcept
    {
    }

OpenSSLException::OpenSSLException(const OpenSSLException& orig) noexcept
    {
    }

OpenSSLException::~OpenSSLException() noexcept
    {
    }

OpenSSLException& OpenSSLException::operator= (const OpenSSLException &src) noexcept 
    {
    return *this ;
    }

const char* OpenSSLException::what() const noexcept 
    {
    static std::stringstream buf ;
    buf.clear() ; buf.str("") ;
    unsigned long e ;
    while ( (e = ERR_get_error()) != 0  )
        {
        buf << ERR_error_string(e, NULL) << std::endl ;
        }
    return buf.str().c_str() ;
    }

