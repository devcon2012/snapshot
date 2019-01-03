/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OpenSSLException.hpp
 * Author: klaus
 *
 * Created on 22. Dezember 2018, 20:53
 */

#ifndef OPENSSLEXCEPTION_HPP
#define OPENSSLEXCEPTION_HPP

#include <string>
#include <exception>

class OpenSSLException : public std::exception
    {
    public:
        OpenSSLException(const std::string &sWhere = std::string() ) noexcept ;
        OpenSSLException(const OpenSSLException& orig) noexcept ;
        virtual ~OpenSSLException() noexcept ;
        OpenSSLException& operator= (const OpenSSLException &) noexcept ;
        virtual const char* what() const noexcept ;
    protected:
        std::string m_sWhere ;
    } ;

#endif /* OPENSSLEXCEPTION_HPP */

