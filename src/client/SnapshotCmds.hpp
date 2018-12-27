/* 
 * File:   SnapshotCmds.hpp
 * Author: klaus
 *
 * Created on 1. März 2018, 21:42
 */

/**
 * Create JSON commands snt to the server and analyze results received.
 * 
 * 
 **/

#ifndef SNAPSHOTCMDS_HPP
#define SNAPSHOTCMDS_HPP

#include <sstream>
#include <boost/property_tree/ptree.hpp>

class SnapshotCmds 
    {

    public:
        SnapshotCmds();
        SnapshotCmds(const SnapshotCmds& orig);
        virtual ~SnapshotCmds();

        static std::string GetClienthandle(const std::string &sSubject) ;
        static bool IsError(boost::property_tree::ptree &p) ;
        static std::string ErrorMessage(boost::property_tree::ptree &p) ;

    private:

    };

#endif /* SNAPSHOTCMDS_HPP */

