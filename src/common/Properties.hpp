/* 
 * File:   Properties.hpp
 * Author: klaus
 *
 * Created on 27. Dezember 2018, 10:47
 */

#ifndef PROPERTIES_HPP
#define PROPERTIES_HPP

#include <string>
#include <vector>
#include <map>

/// a dictionary is just a list of words.
/// You can check if a word is in the dictionyry
class Dictionary
    {
    public:
        Dictionary () ;
        Dictionary (const std::vector<const std::string> &words) ;
        Dictionary (const Dictionary& orig) ;
        virtual ~Dictionary() ;
        bool isDictionaryWord(const std::string & word) ;
        
    protected:
        std::map<const std::string, int > m_nDict ;
        
    } ;

/// Properties is a helper to get/set properties via a dictionary
class Properties 
    {
    public:
        Properties(const Dictionary &);
        Properties(const Properties& orig);
        virtual ~Properties();
        int GetIntProp(const char *Prop) const ;
        double GetFloatProp(const char *Prop) const ;
        const std::string & GetStringProp(const char *Prop) const ;
        void SetProp(const char * prop, int val) ;
        void SetProp(const char * prop, double val) ;
        void SetProp(const char * prop, const std::string & val) ;
        void DelProp(const char * prop) ; 
        
    protected:
        
        typedef struct prop_t
            {
            prop_t() {type = 0 ; }
            prop_t(const prop_t &p) 
                { type = p.type;
                if( p.type==1 ) nval = p.nval ;
                if( p.type==2 ) fval = p.fval ;
                if( p.type==3 ) sval = p.sval ;
                }
            ~prop_t() {} ;
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

#endif /* PROPERTIES_HPP */

