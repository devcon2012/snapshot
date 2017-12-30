/* 
 * File:   DefaultObject.hpp
 * Author: klaus
 *
 * Created on 27. Dezember 2017, 10:57
 */

#ifndef DEFAULTOBJECT_HPP
#define DEFAULTOBJECT_HPP

#include <cstdlib>

/// DefaultObjects are improved Singletons
template<class T> class DefaultObject {
public:
    DefaultObject() 
        {
        if(!ms_DefaultObject)
                ms_DefaultObject = dynamic_cast<T *>(this) ;
        }
    
    virtual ~DefaultObject()
        {
        if( ms_DefaultObject == dynamic_cast<T *>(this) )
                ms_DefaultObject = NULL;
        }
        
    /// Get the default Object
    static T * GetDefault() 
        { return ms_DefaultObject;}
    
    /// Set the default Object
    static void SetDefault( T * pDefault) 
        {ms_DefaultObject = pDefault; }
    
private:

    static T * ms_DefaultObject ;
};
#endif /* DEFAULTOBJECT_HPP */

