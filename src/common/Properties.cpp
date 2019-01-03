/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Properties.cpp
 * Author: klaus
 * 
 * Created on 27. Dezember 2018, 10:47
 */

#include "Properties.hpp"

Dictionary::Dictionary ()
    {
    }

Dictionary::Dictionary (const std::vector<const std::string> &words) 
    {
    /* for ( auto i = words.begin(); i != words.end(); i++ )
        {
        m_nDict[*i] = 1;
        } */
    }

Dictionary::Dictionary (const Dictionary & orig) 
    {
    }

Dictionary::~Dictionary() 
    {
    }

bool Dictionary::isDictionaryWord(const std::string & word) 
    {
    if ( m_nDict.find(word) != m_nDict.end() )
        return true ;
    return false ;
    }


Properties::Properties(const Dictionary &)
    {
    }

Properties::Properties(const Properties& orig)
    {
    }

Properties::~Properties()
    {
    }

int Properties::GetIntProp(const char *Prop) const 
    {
    return 0 ;
    }

double Properties::GetFloatProp(const char *Prop) const 
    {
    return 0. ;
    }

const std::string & Properties::GetStringProp(const char *Prop) const 
    {
    static std::string x = std::string("") ;
    return x ;
    }

void Properties::SetProp(const char * prop, int val) 
    {
    if ( ! m_xDict.isDictionaryWord( std::string(prop) ) )
        throw std::exception();
    
    prop_t p ;
    p.type = 1 ;
    p.nVal = val ;
    const std::string sProp = std::string(prop) ;
    // m_xProps[sProp] = (const prop_t) p ;
        
    }

void Properties::SetProp(const char * prop, double val) 
    {
    }

void Properties::SetProp(const char * prop, const std::string & val) 
    {
    }

void Properties::DelProp(const char * prop) 
    {
    }
        

/*
 * typedef struct
            {
            int type ;
            union 
                {
                std::string sVal ;
                int         nVal ;
                double      fVal ;
                } ;
            } prop_t;
            
        Dictionary  m_xDict ;
        std::map<const std::string, const prop_t> m_xProps ;
  

    } ;

*/