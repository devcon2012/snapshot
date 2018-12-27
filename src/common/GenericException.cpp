/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GenericException.cpp
 * Author: klaus
 * 
 * Created on 22. Dezember 2018, 21:05
 */

#include <string.h>
#include <cerrno>
#include <sstream>
#include "GenericException.hpp"

GenericException::GenericException() noexcept
    {
    }

GenericException::GenericException(const char* sWhat, const char * sFunction, 
            const char * sFile, int nLine) noexcept 
    {
    m_sWhat = sWhat ;
    m_sFunction = sFunction ;
    m_sFile = sFile ;
    m_nLine = nLine ;
    }

GenericException::GenericException(const GenericException& orig) noexcept
    {
    }

GenericException::~GenericException() noexcept
    {
    }

GenericException& GenericException::operator= (const GenericException &src) noexcept 
    {
    m_sWhat         = src.m_sWhat ;
    m_sFunction     = src.m_sFunction ;
    m_sFile         = src.m_sFile ;
    m_nLine         = src.m_nLine ;
    
    return *this;
    }

const char* GenericException::what() const noexcept 
    {
    static std::ostringstream buf ;
    buf.clear() ; buf.str("") ;
    buf << m_sWhat << ": " << m_sFunction << "@" << m_sFile << ":" << m_nLine ;
    return buf.str().c_str() ;
    }

/*  */

SystemException::SystemException() noexcept
    {
    }

SystemException::SystemException(const char* sWhat, const char * sFunction, 
            const char * sFile, int nLine) noexcept :
                    GenericException(sWhat, sFunction, sFile, nLine)
    {
    
    }

SystemException::SystemException(const SystemException& orig) noexcept
    {
    }

SystemException::~SystemException() noexcept
    {
    }

SystemException& SystemException::operator= (const SystemException &src) noexcept 
    {
    m_sWhat         = src.m_sWhat ;
    m_sFunction     = src.m_sFunction ;
    m_sFile         = src.m_sFile ;
    m_nLine         = src.m_nLine ;
    
    return *this;
    }

const char* SystemException::what() const noexcept 
    {
    static std::ostringstream buf ;
    buf.clear() ; buf.str("") ;
    buf << "System error " << errno << ": " << strerror(errno) << "\n" ;
    buf << m_sWhat << ": " << m_sFunction << "@" << m_sFile << ":" << m_nLine ;
    return buf.str().c_str() ;
    }



