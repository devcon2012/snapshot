/* 
 * File:   SnapshotConnector.cpp
 * Author: klaus
 * 
 * Created on 2. Januar 2019, 14:39
 */

#include <wx-3.0/wx/event.h>

#include "SnapshotClient.hpp"
#include "SnapshotConnector.hpp"
#include "SnapshotCmds.hpp"
#include "SnapshotCmdResponse.hpp"
#include "ConnectorException.hpp"

#include "../http/client_https.hpp"



using namespace std;
using HttpsClient = SimpleWeb::Client<SimpleWeb::HTTPS>;

#define ConnectorError(x,y) ConnectorException(x, y, __FUNCTION__,  __FILE__, __LINE__ )

SnapshotConnector::SnapshotConnector()
    {
    }

SnapshotConnector::SnapshotConnector(const SnapshotConnector& orig)
    {
    }

SnapshotConnector::~SnapshotConnector()
    {
    }

int SnapshotConnector::Connect(const std::string & server, int port, 
                               const std::string & ca, const std::string & cert, 
                               const std::string & key, const std::string & passwd )
    {
    m_sServer   = server ;
    m_nPort     = port ;
    m_sCertFile = cert ;
    m_sKeyFile  = key ;
    m_sPasswd   = passwd ;

    int nState = 0 ;
    
    HttpsClient client(server, false, cert, key, ca, password_callback);
    std::string sLogin = SnapshotCmds::GetClienthandle("cn=test") ;
    try
        {
        SimpleWeb::CaseInsensitiveMultimap headers ;
        headers.emplace("Content-Type", "application/json") ;
        auto r1 = client.request("POST", "/json", sLogin.c_str(), headers);
        SnapshotCmdResponse r( r1->content.string() ) ;
        if ( r.IsError() )
            {
            throw ConnectorError(r.ErrorMessage().c_str(), "GetClientHandle") ;
            }
        else
            {
            m_sClientHandle = r.GetClienthandle() ;
            nState = 200 ;
            }
        }
    catch ( std::exception &e )
        {
        SnapshotClient::PostError(e, 
            std::string("while trying to connect to ") + server.c_str() );
        SnapshotClient::PostUpdateServerState("disconnected") ;
        m_sClientHandle = "" ;
        }
    
    return nState ;
    }

std::string SnapshotConnector::password_callback( std::size_t max_length, boost::asio::ssl::context::password_purpose purpose )
    {
    return "test" ;
    }
   
#ifdef _NEVER
  // Client examples
  // Second create() parameter set to false: no certificate verification
  HttpsClient client("localhost:8080", false);

  string json_string = "{\"firstName\": \"John\",\"lastName\": \"Smith\",\"age\": 25}";

  // Synchronous request examples
  try {
    auto r1 = client.request("GET", "/match/123");
    cout << r1->content.rdbuf() << endl; // Alternatively, use the convenience function r1->content.string()

    auto r2 = client.request("POST", "/string", json_string);
    cout << r2->content.rdbuf() << endl;
  }
  catch(const SimpleWeb::system_error &e) {
    cerr << "Client request error: " << e.what() << endl;
  }
    }

 Client(const std::string &server_port_path, bool verify_certificate = true, const std::string &cert_file = std::string(),
           const std::string &private_key_file = std::string(), const std::string &verify_file = std::string())
        : ClientBase<HTTPS>::ClientBase(server_port_path, 443), context(asio::ssl::context::tlsv12)

#endif
         