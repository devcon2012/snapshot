/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Client.cpp
 * Author: klaus
 *
 * Created on 25. Dezember 2017, 21:02
 */

#include <cstdlib>
#include "SnapshotClient.hpp"

using namespace std;

/*
 * 
 */
int main2(int argc, char** argv)
    {

    SnapshotClient *pClient = new SnapshotClient(argc, argv) ;
    
    return pClient -> Run() ;
    
    }

