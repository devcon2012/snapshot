/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GenericException.hpp
 * Author: klaus
 *
 * Created on 22. Dezember 2018, 20:53
 */

#ifndef GENERICEXCEPTION_HPP
#define GENERICEXCEPTION_HPP

#include <string>
#include <exception>

#define MemoryException() GenericException("memory", __FUNCTION__,  __FILE__, __LINE__ )
#define SysException(x) SystemException(x, __FUNCTION__,  __FILE__, __LINE__ )

class GenericException : public std::exception 
    {
    public:
        GenericException() noexcept ;
        GenericException(const char* sWhat, const char * sFunction, 
                    const char * sFile, int nLine) noexcept ;
        GenericException(const GenericException& orig) noexcept ;
        virtual ~GenericException() noexcept ;
        GenericException& operator= (const GenericException &) noexcept ;
        virtual const char* what() const noexcept ;

    protected:
        std::string     m_sBuf ;
        std::string     m_sWhat ;
        std::string     m_sFunction ;
        std::string     m_sFile ;
        int             m_nLine ;

} ;

class SystemException : public GenericException 
    {
    public:
        SystemException() noexcept ;
        SystemException(const char* sWhat, const char * sFunction, 
                    const char * sFile, int nLine) noexcept ;
        SystemException(const SystemException& orig) noexcept ;
        virtual ~SystemException() noexcept ;
        SystemException& operator= (const SystemException &) noexcept ;
        virtual const char* what() const noexcept ;

    protected:

} ;

#endif /* OPENSSLEXCEPTION_HPP */

