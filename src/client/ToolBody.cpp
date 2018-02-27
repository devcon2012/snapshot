/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ToolBody.cpp
 * Author: klaus
 * 
 * Created on 27. Februar 2018, 19:55
 */

#include "ToolBody.hpp"
#include "../server/http/client_http.hpp"

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
    std::string sServer = m_pConfig -> GetString("Server", "localhost.:8080") ;

    HttpClient client(sServer) ;
    
    // Synchronous request examples
    try 
        {
        auto r1 = client.request("GET", "/match/123");
        cout << r1->content.rdbuf() << endl; // Alternatively, use the convenience function r1->content.string()

        auto r2 = client.request("POST", "/string", "Wurgel");
        cout << r2->content.rdbuf() << endl;
        }
    catch(const SimpleWeb::system_error &e) 
        {
        cerr << "Client request error: " << e.what() << endl;
        }
    
    return 0;
    }

