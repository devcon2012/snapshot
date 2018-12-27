/*
 * 
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

