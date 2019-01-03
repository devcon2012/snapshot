/* 
 * File:   SnapshotCmdResponse.hpp
 * Author: klaus
 *
 * Created on 1. März 2018, 21:42
 */

/**
 * Create JSON commands snt to the server and analyze results received.
 * 
 * 
 **/

#ifndef SNAPSHOTCMDRESPONSE_HPP
#define SNAPSHOTCMDRESPONSE_HPP

#include <sstream>
#include <boost/property_tree/ptree.hpp>

class SnapshotCmdResponse 
    {

    public:
        SnapshotCmdResponse();
        SnapshotCmdResponse(const std::string &sJsonResponse);
        SnapshotCmdResponse(const SnapshotCmdResponse& orig);
        virtual ~SnapshotCmdResponse();

        bool IsError(const std::string &sJsonResponse = std::string("")) ;
        std::string ErrorMessage(const std::string &sJsonResponse = std::string("")) ;
        void SetResponse(const std::string &sJsonResponse) ;
        std::string GetResponse() const {return m_sJson; } ;
        std::string GetClienthandle(const std::string &sJsonResponse = std::string("") ) ;

    private:
        std::string     m_sJson ;
        boost::property_tree::ptree m_xPTree ;
    };

#endif /* SNAPSHOTCMDRESPONSE_HPP */

