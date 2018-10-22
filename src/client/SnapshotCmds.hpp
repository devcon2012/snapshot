/* 
 * File:   SnapshotCmds.hpp
 * Author: klaus
 *
 * Created on 1. März 2018, 21:42
 */

/**
 * Create JSON Commands 
 * 
 * 
 **/

#ifndef SNAPSHOTCMDS_HPP
#define SNAPSHOTCMDS_HPP

#include <sstream>

class SnapshotCmds 
    {

    public:
        SnapshotCmds();
        SnapshotCmds(const SnapshotCmds& orig);
        virtual ~SnapshotCmds();

        static std::string GetClienthandle(const std::string &sSubject) ;

    private:

    };

#endif /* SNAPSHOTCMDS_HPP */

