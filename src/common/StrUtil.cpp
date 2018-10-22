/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StrUtil.cpp
 * Author: klaus
 * 
 * Created on 27. Dezember 2017, 11:28
 */

#include <iostream>
#include "StrUtil.hpp"

StrUtil::StrUtil()
    {
    }

StrUtil::StrUtil(const StrUtil& orig)
    {
    }

StrUtil::~StrUtil()
    {
    }

std::string StrUtil::StrSubst(const std::string &sIn, 
                     const std::string &sOld,
                     const std::string &sNew)
    {
    std::string sRet = sIn ;
    
    size_t i = sIn.find(sOld, 0) ;
    
    if( i != std::string::npos )
        {
        sRet.replace(i, sOld.length(), sNew);
        }

    return sRet ;
    }

std::string StrUtil::StrSubstAll(const std::string &sIn,
                        const std::string &sOld, 
                        const std::string &sNew)
    {
    std::string sRet =sIn;
    
    for(size_t i = 0; (i = sRet.find(sOld, i)) != std::string::npos;)
        {
        sRet.replace(i, sOld.length(), sNew);
        i += sNew.length();
        }

    return sRet ;    
    }

/// set a string vector to a pt so it is later rendered as a JSON array
void StrUtil::set_vector(boost::property_tree::ptree &pt,
                        std::string const &sArrayName,
                        std::vector<std::string> &sArray)
    {
    auto parray = pt.find(sArrayName) ;
    
    if( parray == pt.not_found())
        {
        boost::property_tree::ptree array;

        for ( auto i = sArray.begin(); i != sArray.end(); i++)
            {
            boost::property_tree::ptree kid ;
            kid.put("", *i);
            array.push_back(std::make_pair("", kid));
            }

        pt.add_child(sArrayName, array) ;
        }
    else
        {
        boost::property_tree::ptree &array = (pt.to_iterator(parray))->second;
        array.clear() ;
        for ( auto i = sArray.begin(); i != sArray.end(); i++)
            {
            boost::property_tree::ptree kid ;
            kid.put("", *i);
            array.push_back(std::make_pair("", kid));
            }
        
        }
    }

/// Add a string vector to a pt so it is later rendered as a JSON array
void StrUtil::add_vector(boost::property_tree::ptree &pt,
                        std::string const &sArrayName,
                        std::vector<std::string> &sArray)
    {
    auto parray = pt.find(sArrayName) ;
    
    if( parray == pt.not_found())
        {
        boost::property_tree::ptree array;

        for ( auto i = sArray.begin(); i != sArray.end(); i++)
            {
            boost::property_tree::ptree kid ;
            kid.put("", *i);
            array.push_back(std::make_pair("", kid));
            }

        pt.add_child(sArrayName, array) ;
        }
    else
        {
        boost::property_tree::ptree &array = (pt.to_iterator(parray))->second;
        
        for ( auto i = sArray.begin(); i != sArray.end(); i++)
            {
            boost::property_tree::ptree kid ;
            kid.put("", *i);
            array.push_back(std::make_pair("", kid));
            }
        
        }
    }

/// get a string vector from a ptreee
/// Will append to sArray
void StrUtil::get_vector(boost::property_tree::ptree &pt,
                    std::string const &sArrayName,
                    std::vector<std::string> &sArray)
    {
    boost::property_tree::ptree &array = pt.get_child(sArrayName) ;

    for ( auto i = array.begin(); i != array.end(); i++)
        {
        sArray.push_back(i->second.get_value<std::string>());
        }

    }


/// Add a list of files in one path to a snapshot
/// pt contains a snapshot handle, a path handle and a filename
/// returned is a new file handle and maybe a digest for the same
/// file in a previous snapshot
/// @var sJSON JSON String to be parsed
/// @ret parsed JSOn ptree
boost::property_tree::ptree StrUtil::pt_from_json(std::string const &sJSON) 
    {
    std::istringstream sOut(sJSON);
    boost::property_tree::ptree xRet;
    
    boost::property_tree::read_json(sOut, xRet);
    return xRet ;
    
    }
boost::property_tree::ptree StrUtil::pt_from_json(std::basic_streambuf<char>* sJSON) 
    {
    std::istream sOut(sJSON);
    boost::property_tree::ptree xRet;
    
    boost::property_tree::read_json(sOut, xRet);
    return xRet ;
    }

/// Add a list of files in one path to a snapshot
/// pt contains a snapshot handle, a path handle and a filename
/// returned is a new file handle and maybe a digest for the same
/// file in a previous snapshot
/// @var sJSON JSON String to be parsed
/// @ret parsed JSOn ptree
std::string StrUtil::json_from_pt(boost::property_tree::ptree const &pt) 
    {
    std::ostringstream sOut;
    
    boost::property_tree::write_json(sOut, pt);
    return sOut.str() ;
    
    }

/// construct a simple json key->value list
/// @var str a la "key1;value1;key2;value..."
/// @ret sJSON a la "{key1:value1, key2: ..."
std::string StrUtil::str2json(const char ** str, int n) 
    {
    std::stringstream sJSON ;
    std::string  sIn("");
    
    sJSON << "{" ;
    while(true)
        {
        }
    sJSON << "}";
    return sJSON.str();
    }

void StrUtil::dump_pt(std::ostream &out, boost::property_tree::ptree &pt)
    {
    out << json_from_pt(pt) ;
    }

void StrUtil::dump_pt(boost::property_tree::ptree &pt)
    {
    dump_pt(std::cout, pt);
    }
