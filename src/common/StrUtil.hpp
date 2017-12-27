/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StrUtil.hpp
 * Author: klaus
 *
 * Created on 27. Dezember 2017, 11:28
 */

#ifndef STRUTIL_HPP
#define STRUTIL_HPP

#include <string>

class StrUtil 
    {
public:
    StrUtil();
    StrUtil(const StrUtil& orig);
    virtual ~StrUtil();
    
    static std::string StrSubst(const std::string &sIn, 
                         const std::string &sOld,
                         const std::string &sNew);
    static std::string StrSubstAll(const std::string &sIn,
                            const std::string &sOld, 
                            const std::string &sNew);
    
private:

    };

#endif /* STRUTIL_HPP */

