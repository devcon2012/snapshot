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

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>


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

    static void add_vector(boost::property_tree::ptree &pt,
                        std::string const &sArrayName,
                        std::vector<std::string> &sArray);
    
    static void get_vector(boost::property_tree::ptree &pt,
                        std::string const &sArrayName,
                        std::vector<std::string> &sArray);
    
    static std::string str2json(const char ** str, int n) ;
    static boost::property_tree::ptree pt_from_json(std::string const &sJSON) ;
    static std::string json_from_pt(boost::property_tree::ptree const &pt)  ;
 
    static void dump_pt(std::ostream &out, boost::property_tree::ptree &pt);
    static void dump_pt(boost::property_tree::ptree &pt);

private:

    };

#endif /* STRUTIL_HPP */

