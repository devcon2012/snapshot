/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DefaultObject.hpp
 * Author: klaus
 *
 * Created on 27. Dezember 2017, 10:57
 */

#ifndef DEFAULTOBJECT_HPP
#define DEFAULTOBJECT_HPP

/// DefaultObjects are improved Singletons
class DefaultObject {
public:
    DefaultObject();
    DefaultObject(const DefaultObject& orig);
    virtual ~DefaultObject();
        
    /// Get the default Object
    static DefaultObject * GetDefault() 
        { return ms_DefaultObject;}
    
    /// Set the default Object
    static void SetDefault( DefaultObject * pDefault) 
        {ms_DefaultObject = pDefault; }
    
private:

    static DefaultObject * ms_DefaultObject ;
};

#endif /* DEFAULTOBJECT_HPP */

