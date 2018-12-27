/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Key.hpp
 * Author: klaus
 *
 * Created on 22. Dezember 2018, 13:25
 */

#ifndef KEY_HPP
#define KEY_HPP

#include <istream>
#include <ostream>
#include <openssl/evp.h>

#include "Initializer.hpp"

class Key 
    {
    public:
        Key() ;
        Key(const Key& orig) ;
        virtual ~Key();

        void LoadPEM(std::istream &s, std::string const &pass = "") ;    
        void LoadPEM(std::string const &s, std::string const &pass = "") ;    

        void SavePEM(std::ostream &s, std::string const &pass = "") const ; 
        void SavePEM(std::string const &s, std::string const &pass = "") const ;    

        void NewRSA(int size) ;
        bool hasPrivKey() const ;
        std::string Fingerprint() const ;
        
        int Size() const ;
        
    protected:
        EVP_PKEY    * m_pKey ;
        RSA         * m_pRSA ;
        BIGNUM      * m_pExponent ;
        bool          m_bPrivKey ; 
        std::string   m_sPassWord ;
        
        static int cb(char *buf, int size, int rwflag, void *u) ;
        void Init(bool first = false) ;
        void Clean() ;
        Initializer * m_pInitializer ;

} ;

#endif /* KEY_HPP */

