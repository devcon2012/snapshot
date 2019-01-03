/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotServer.hpp
 * Author: klaus
 *
 * Created on 26. Dezember 2017, 12:44
 */

#ifndef SNAPSHOTSERVER_HPP
#define SNAPSHOTSERVER_HPP

#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <memory>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>

#include "../http/server_http.hpp"
#include "../http/server_https.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpsServer = SimpleWeb::Server<SimpleWeb::HTTPS>;

class SnapshotServerModel ;
class SnapshotConfig ;

class SnapshotServer {
public:
    SnapshotServer(int argc, char** argv, SnapshotConfig  * pConfig) ;
    SnapshotServer(const SnapshotServer& orig) ;
    virtual ~SnapshotServer();

    /// Control - query snapshots, prepare UL/DL
    std::string Control(std::shared_ptr<HttpServer::Request> &request) ;

    /// Downloadpath - return path of a saved file
    std::string Downloadpath(std::shared_ptr<HttpServer::Request> &request) ;

    /// Uploadpath - return path to save an upload
    std::string Uploadpath(std::shared_ptr<HttpServer::Request> &request) ;

    /// Control - query snapshots, prepare UL/DL
    std::string Control(std::shared_ptr<HttpsServer::Request> &request) ;

    /// Downloadpath - return path of a saved file
    std::string Downloadpath(std::shared_ptr<HttpsServer::Request> &request) ;

    /// Uploadpath - return path to save an upload
    std::string Uploadpath(std::shared_ptr<HttpsServer::Request> &request) ;

    boost::property_tree::ptree Action(boost::property_tree::ptree &pt) ;
    boost::property_tree::ptree Enumerate(boost::property_tree::ptree &pt) ;
    boost::property_tree::ptree Getter(boost::property_tree::ptree &pt) ;
    boost::property_tree::ptree Setter(boost::property_tree::ptree &pt) ;
    boost::property_tree::ptree Adder(boost::property_tree::ptree &pt) ;
    boost::property_tree::ptree Deleter(boost::property_tree::ptree &pt) ;
    
    /// Logging
    void log(std::shared_ptr<HttpServer::Request> const &request, SimpleWeb::error_code const &e) ;
    void log(std::shared_ptr<HttpServer::Request> const &request) ;
    void log(std::shared_ptr<HttpServer::Response> const &response) ;
    void log(std::shared_ptr<HttpServer::Response> const &response, SimpleWeb::error_code const &e) ; 
    void log(std::shared_ptr<HttpsServer::Request> const &request, SimpleWeb::error_code const &e) ;
    void log(std::shared_ptr<HttpsServer::Request> const &request) ;
    void log(std::shared_ptr<HttpsServer::Response> const &response) ;
    void log(std::shared_ptr<HttpsServer::Response> const &response, SimpleWeb::error_code const &e) ; 
    void log(const std::exception &e) ;

    /// map file extensions to mime type (utility function)
    std::string ext2mime(std::string const &s) ;

    static void read_and_send    (const std::shared_ptr<HttpServer::Response> &response,
                                    const std::shared_ptr<std::ifstream> &ifs) ;
    static void receive_and_write(const std::shared_ptr<HttpServer::Request> &request,
                                    const std::shared_ptr<std::ofstream> &ifs) ;

    static void read_and_send    (const std::shared_ptr<HttpsServer::Response> &response,
                                    const std::shared_ptr<std::ifstream> &ifs) ;
    static void receive_and_write(const std::shared_ptr<HttpsServer::Request> &request,
                                    const std::shared_ptr<std::ofstream> &ifs) ;

private:
    std::map<std::string, std::string>      m_sMimeMap ;
    SnapshotServerModel                   * m_pModel ;
} ;

#endif /* SNAPSHOTSERVER_HPP */

