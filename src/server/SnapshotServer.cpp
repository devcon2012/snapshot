/* 
 * File:   SnapshotServer.cpp
 * Author: klaus
 * 
 * Created on 26. Dezember 2017, 12:44
 */

#include <stdexcept>

#include "../common/SnapshotException.hpp"
#include "../common/StrUtil.hpp"
#include "SnapshotServer.hpp"
#include "SnapshotServerModelKC.hpp"

using namespace boost::property_tree::json_parser;

/// Construct new snapshot server. This is the control component of the server gui
/// The view is the html/jquery component
SnapshotServer::SnapshotServer(int argc, char** argv)
    {
    m_sMimeMap [".css"]  = "text/css" ;
    m_sMimeMap [".ico"]  = "image/x-icon" ;
    m_sMimeMap [".png"]  = "image/png" ;
    m_sMimeMap [".js"]   = "application/javascript" ;
    m_sMimeMap [".json"] = "application/json" ;
    m_sMimeMap [".html"] = "text/html" ;
    m_pModel = new SnapshotServerModelKC() ;
    
 
    boost::property_tree::ptree test_settings 
            = StrUtil::pt_from_json("{\"DBRoot\": \"/home/klaus/src/owngit/snapshot/build/src/server/db\"}");
    m_pModel -> Provision(test_settings)  ;   
    }

SnapshotServer::SnapshotServer(const SnapshotServer& orig)
    {
    }

SnapshotServer::~SnapshotServer()
    {
    if (m_pModel)
        delete m_pModel ;
    m_pModel = NULL;
    }

std::string SnapshotServer::ext2mime(std::string const &s)
    {
    std::string sRet = "application/octet-stream" ;
    auto t = m_sMimeMap.find(s);
    if ( t != m_sMimeMap.end())
        sRet = t->second;
    //std::cerr << "Type: " << s << "-->" << sRet << "\n";
    return sRet ;
    }

boost::property_tree::ptree SnapshotServer::Action(boost::property_tree::ptree &pt)
    {
    std::string sAction = pt.get<std::string>("action");
    
    if ( sAction == "enumerate" )
        return Enumerate(pt);

    if ( sAction == "get" )
        return Getter(pt);

    if ( sAction == "set" )
        return Setter(pt);

    if ( sAction == "add" )
        return Adder(pt);
    
    if ( sAction == "delete" )
        return Deleter(pt);
    
    
    throw SnapshotException("invalid_argument", "action", sAction.c_str());
    }

boost::property_tree::ptree SnapshotServer::Enumerate(boost::property_tree::ptree &pt)
    {
    std::string sArg = pt.get<std::string>("arg");
    
    if ( sArg == "snapshots" )
        return m_pModel -> GetSnapshots(pt);

    if ( sArg == "files" )
        return m_pModel -> GetSnapshotFiles(pt);

    if ( sArg == "pathes" )
        return m_pModel -> GetSnapshotPathes(pt);

    throw SnapshotException("invalid_argument", "enumerate", sArg.c_str());
    
    }

boost::property_tree::ptree SnapshotServer::Getter(boost::property_tree::ptree &pt)
    {
    std::string sArg = pt.get<std::string>("arg");
    
    if ( sArg == "clienthandle" )
        return m_pModel -> GetClientHandle(pt);

    if ( sArg == "snapshotpathes" )
        return m_pModel -> GetSnapshotPathes(pt);

    if ( sArg == "snapshotfiles" )
        return m_pModel -> GetSnapshotFiles(pt);
    
    throw SnapshotException("invalid_argument", "getter", sArg.c_str());
    }

boost::property_tree::ptree SnapshotServer::Setter(boost::property_tree::ptree &pt)
    {
    std::string sArg = pt.get<std::string>("arg");
    
    if ( sArg == "clienthandle" )
        return m_pModel -> SetClientHandle(pt);

    throw SnapshotException("invalid_argument", "setter", sArg.c_str());
    
    }

boost::property_tree::ptree SnapshotServer::Adder(boost::property_tree::ptree &pt)
    {
    std::string sArg = pt.get<std::string>("arg");
    
    if ( sArg == "snapshot" )
        return m_pModel -> AddSnapshot(pt);

    if ( sArg == "snapshotpath" )
        return m_pModel -> AddSnapshotPath(pt);

    if ( sArg == "snapshotfiles" )
        return m_pModel -> AddSnapshotFiles(pt);
    
    throw SnapshotException("invalid_argument", "adder", sArg.c_str());
    }

boost::property_tree::ptree SnapshotServer::Deleter(boost::property_tree::ptree &pt)
    {
    std::string sArg = pt.get<std::string>("arg");
    
    if ( sArg == "clienthandle" )
        return m_pModel -> GetSnapshots(pt);

    throw SnapshotException("invalid_argument", "deleter", sArg.c_str());
    
    }


void SnapshotServer::log(std::shared_ptr<HttpServer::Request> const &request)
    {
    time_t now = time(NULL) ;
    std::cerr << now << " " << "Request " << request->method << ": " << request->path << "\n" ;
    /* char buf[257] ;
    buf[0] = 0;
    request -> content.read(buf, 256);
    buf[request->content.gcount()] = 0;
    buf[256] = 0;
    std::cerr << ".." << buf  << "XX\n\n"; */
    }

void SnapshotServer::log(std::shared_ptr<HttpServer::Request> const &request, SimpleWeb::error_code const &e)
    {
    time_t now = time(NULL) ;
    std::cerr << now << " " << "Request " << request->method << " ERROR " << e.message() << ": " << request->path << "\n" ;
    }

void SnapshotServer::log(std::shared_ptr<HttpServer::Response> const &response)
    {
    time_t now = time(NULL) ;
    std::cerr << now << " " << "Response \n" ;
    }

void SnapshotServer::log(std::shared_ptr<HttpServer::Response> const &response, SimpleWeb::error_code const &e)
    {
    time_t now = time(NULL) ;
    std::cerr << now << " " << "Response error " << e.message() << "\n" ;
    }

void SnapshotServer::log(const std::exception &e) 
    {
    time_t now = time(NULL) ;
    std::cerr << now << " " << "Error: " << e.what() << "\n" ;
    }

std::string SnapshotServer::Control(std::shared_ptr<HttpServer::Request> &request) 
    {
    boost::property_tree::ptree pt;
    auto xContentType = request -> header.find("Content-Type") ;
    std::string sContentType("application/octet-stream") ;

    if (xContentType != request->header.end())
        sContentType = xContentType -> second ;

    std::cerr << "JSON:: ContentType:" << sContentType << "\n" ;

    if(sContentType == "application/json")
        read_json(request->content, pt);
    else
        throw std::invalid_argument("no valid json");


    boost::property_tree::ptree res = Action(pt);
    
    std::ostringstream xRet;
    write_json(xRet, res);
    std::cerr << "JSON:: return" << xRet.str() << "\n" ;
    return xRet.str();
    
    } // ends Control

std::string SnapshotServer::Upload(std::shared_ptr<HttpServer::Request> &request) 
    {
    boost::property_tree::ptree pt;
    auto xContentType = request -> header.find("Content-Type") ;
    std::string sContentType("application/octet-stream") ;

    if (xContentType != request->header.end())
        sContentType = xContentType -> second ;

    if(sContentType == "application/json")
        read_json(request->content, pt);
    
    pt.add("Key", "Value") ;
    std::ostringstream xRet ;
    write_json(xRet, pt);
    std::cerr << "JSON:: return" << xRet.str() << "\n" ;
    return xRet.str();
    }

std::string SnapshotServer::Download(std::shared_ptr<HttpServer::Request> &request) 
    {
    boost::property_tree::ptree pt;
    auto xContentType = request -> header.find("Content-Type") ;
    std::string sContentType("application/octet-stream") ;

    if (xContentType != request->header.end())
        sContentType = xContentType -> second ;

    if(sContentType == "application/json")
        read_json(request->content, pt);
    
    pt.add("Key", "Value") ;
    std::ostringstream xRet ;
    write_json(xRet, pt);
    std::cerr << "JSON:: return" << xRet.str() << "\n" ;
    return xRet.str();
    }
