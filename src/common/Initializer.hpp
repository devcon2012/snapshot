/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Initializer.hpp
 * Author: klaus
 *
 * Created on 22. Dezember 2018, 14:27
 */

#ifndef INITIALIZER_HPP
#define INITIALIZER_HPP

class Initializer {
public:
    static Initializer * GetInitializer() ;
protected:
    Initializer();
    Initializer(const Initializer& orig);
    virtual ~Initializer();
    static Initializer * m_pInitializer ;
    void OpenSSLInitializer() ;
    void I18NInitializer() ;
};

#endif /* INITIALIZER_HPP */

