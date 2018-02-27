/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tool.cpp
 * Author: klaus
 *
 * Created on 27. Februar 2018, 19:54
 */

#include <cstdlib>
#include "ToolBody.hpp"

using namespace std;

/*
 * 
 */

SnapshotConfig * pConfig = NULL ;

int main(int argc, char** argv)
    {
    const char * base = ( getenv("HOME") ? getenv("HOME") : "." ) ;
    string sConfigFilename = std::string(base) + "/.snapshotclient" ;

    pConfig = SnapshotConfig::GetDefaultConfig() ;
    pConfig -> InitClientDefaults() ;
    pConfig -> Load(sConfigFilename) ;
    
    ToolBody *pBody = new ToolBody(argc, argv);
    int ret = pBody -> Run() ;
    pConfig -> Save(sConfigFilename) ;
    return ret;
    }

