/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ToolBody.hpp
 * Author: klaus
 *
 * Created on 27. Februar 2018, 19:55
 */

#ifndef TOOLBODY_HPP
#define TOOLBODY_HPP

#include "../common/SnapshotConfig.hpp"

class ToolBody {
public:
    ToolBody(int argc, char** argv) ;
    ToolBody(const ToolBody& orig) ;
    virtual ~ToolBody() ;
    
    int Run() ;
protected:
     SnapshotConfig * m_pConfig ;
};

#endif /* TOOLBODY_HPP */

