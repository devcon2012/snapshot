/* 
 * File:   ToolBody.cpp
 * Author: klaus
 * 
 * 
 * Created on 27. Februar 2018, 19:55
 */

#include "ToolBody.hpp"
#include "../http/client_http.hpp"
#include "../common/StrUtil.hpp"
#include "SnapshotCmds.hpp"

using namespace std;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

ToolBody::ToolBody(int argc, char** argv)
    {
    m_pConfig = SnapshotConfig::GetDefaultConfig() ;
    }

ToolBody::ToolBody(const ToolBody& orig)
    {
    }

ToolBody::~ToolBody()
    {
    }

int ToolBody::Run()
    {
    std::string sServer = m_pConfig -> GetString("Server", "localhost:8088") ;

    SnapshotConfig xStore ;
    
    std::cerr << "try server " << sServer << std::endl ;

    HttpClient client(sServer) ;
    
    // Synchronous request examples
    try 
        {
        
        string sJson , sSubject ;
        sSubject = m_pConfig -> GetString( "Subject", "cn=test") ;
        sJson = SnapshotCmds::GetClienthandle(sSubject) ;
        
        SimpleWeb::CaseInsensitiveMultimap xJsonHeaders;
        xJsonHeaders.emplace("Content-Length", to_string(sJson.length()));
        xJsonHeaders.emplace("Content-Type", "application/json");

        auto r2 = client.request("POST", "/json", sJson, xJsonHeaders);
        boost::property_tree::ptree pRet = StrUtil::pt_from_json( r2->content.rdbuf() );
        
        if ( SnapshotCmds::IsError(pRet) )
            {
            std::cerr << "Error: " << SnapshotCmds::ErrorMessage(pRet) << std::endl ;
            }
        else
            {
            xStore.Set("clienthandle", pRet.get<std::string>("clienthandle") ) ;
            }

        StrUtil::dump_pt(pRet) ;

        sJson = SnapshotCmds::GetClienthandle(sSubject) ;
        
        
        
        }
    catch(const SimpleWeb::system_error &e) 
        {
        cerr << "Client request error: " << e.what() << endl;
        }
    catch(const std::exception &e) 
        {
        cerr << "exception: " << e.what() << endl;
        }
    catch(...) 
        {
        cerr << "unspecified error" << endl;
        }
    
    return 0;
    }

