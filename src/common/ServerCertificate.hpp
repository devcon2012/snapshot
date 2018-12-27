/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerCertificate.hpp
 * Author: klaus
 *
 * Created on 22. Dezember 2018, 13:11
 */

#ifndef SERVERCERTIFICATE_HPP
#define SERVERCERTIFICATE_HPP

#include "BaseCertificate.hpp"

class ServerCertificate : public BaseCertificate{
public:
    ServerCertificate();
    ServerCertificate(const ServerCertificate& orig);
    virtual ~ServerCertificate();
private:

};

#endif /* SERVERCERTIFICATE_HPP */

