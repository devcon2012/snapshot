/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Server.cpp
 * Author: klaus
 *
 * Created on 25. Dezember 2017, 21:02
 */

#include <cstdlib>
#include "SnapshotServer.hpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
    {

    SnapshotServer *pServer = new SnapshotServer(argc, argv) ;
    
    return pServer -> Run() ;
    
    }

