/* 
 * File:   SnapshotConnector.hpp
 * Author: klaus
 *
 * Created on 2. Januar 2019, 14:39
 */

#ifndef SNAPSHOTCONNECTOR_HPP
#define SNAPSHOTCONNECTOR_HPP

#include <string>
#include <boost/asio/ssl/context.hpp>

class SnapshotConnector {
public:
    SnapshotConnector();
    SnapshotConnector(const SnapshotConnector& orig);
    virtual ~SnapshotConnector();
    
    /// Connect to the server specified & verified with ca,  with credentials specified, obtain client handle and return http status
    int Connect(const std::string & server, int port, 
            const std::string & ca, const std::string & cert, 
            const std::string & key, const std::string & passwd ) ;
    static std::string password_callback( std::size_t max_length, boost::asio::ssl::context::password_purpose  purpose );

    int GetSyncDirs() ;

protected:
    std::string         m_sServer ;
    int                 m_nPort ;
    std::string         m_sCertFile ;
    std::string         m_sKeyFile ;
    std::string         m_sPasswd ;
    std::string         m_sClientHandle ;
};

#endif /* SNAPSHOTCONNECTOR_HPP */

