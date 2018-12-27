/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotException.hpp
 * Author: klaus
 *
 * Created on 25. Dezember 2017, 23:05
 */

#ifndef SNAPSHOTEXCEPTION_HPP
#define SNAPSHOTEXCEPTION_HPP

#include <string>
#include <exception>

class SnapshotException : public std::exception 
    {

    public:
    explicit SnapshotException(const std::string &sArg) noexcept ;
    explicit SnapshotException(const char * sType, const char * sArg1=NULL, const char * sArg2=NULL) noexcept ;
    SnapshotException(const SnapshotException& orig) noexcept ;
    exception & operator= (const exception&) noexcept ;
    virtual ~SnapshotException() noexcept ;
    virtual const char * Message() const noexcept { return what(); }
    virtual const char * what() const noexcept { return m_sMessage.c_str(); }

    private:
    std::string m_sMessage ;
    } ;

#endif /* SNAPSHOTEXCEPTION_HPP */

