/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DefaultObject.cpp
 * Author: klaus
 * 
 * Created on 27. Dezember 2017, 10:57
 */

#include "DefaultObject.hpp"
#include <stdlib.h>

DefaultObject * DefaultObject::ms_DefaultObject = NULL ;

DefaultObject::DefaultObject()
    {
    if(!ms_DefaultObject)
        ms_DefaultObject = this ;
    }

DefaultObject::DefaultObject(const DefaultObject& orig)
    {
    }

DefaultObject::~DefaultObject()
    {
    if(ms_DefaultObject == this)
        ms_DefaultObject = NULL ;
    }


