/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CACertificate.hpp
 * Author: klaus
 *
 * Created on 22. Dezember 2018, 13:11
 */

#ifndef CACERTIFICATE_HPP
#define CACERTIFICATE_HPP

#include "BaseCertificate.hpp"

class CACertificate : public BaseCertificate {
public:
    CACertificate();
    CACertificate(const CACertificate& orig);
    virtual ~CACertificate();
private:

};

#endif /* CACERTIFICATE_HPP */

