/* 
 * File:   Server.cpp
 * Author: klaus
 *
 * Created on 25. Dezember 2017, 21:02
 */

#include <cstdlib>
#include "SnapshotServer.hpp"
#include "../common/SnapshotConfig.hpp"
#include "../common/SnapshotLog.hpp"

#include "http/server_http.hpp"

// Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#ifdef __linux__
#include <signal.h>
#include <unistd.h>
#endif

// Added for the default_resource example
#include <vector>
#include "http/crypto.hpp"

using namespace std;
using namespace boost::property_tree;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
 
SnapshotServer  * pDefaultServer    = NULL ;
SnapshotConfig  * pConfig           = NULL ;
std::string       sConfigFilename ;
SnapshotLog     * pLog              = NULL ;

#ifdef __linux__

typedef void (*sighandler_t)(int);
static sighandler_t 
install_handler(int sig_nr, sighandler_t signalhandler) {
   struct sigaction neu_sig, alt_sig;
   neu_sig.sa_handler = signalhandler;
   sigemptyset (&neu_sig.sa_mask);
   neu_sig.sa_flags = SA_RESTART;   
   if (sigaction (sig_nr, &neu_sig, &alt_sig) < 0)
      return SIG_ERR;
   return alt_sig.sa_handler;
}
static void handle_shutdown (int signr) 
    {
    std::cerr << "Shutdown..\n" ;
    pConfig = SnapshotConfig::GetDefaultConfig() ;
    pConfig -> Save(sConfigFilename) ;
    
   exit (0) ;
    }
#endif

int main(int argc, char **argv)
    {
    // HTTP-server at port 8080 using 1 thread
    // Unless you do more heavy non-threaded processing in the resources,
    // 1 thread is usually faster than several threads
    HttpServer server;

#ifdef __linux__
    install_handler(SIGINT, handle_shutdown) ;
#endif
    
    if( argc>2 )
        {
        if ( std::string(argv[1]) == "-c" )
            sConfigFilename = std::string(argv[2]) ;
        
        char * tmp = argv[0] ;
        argc-- ; argc --;
        argv++ ; argv ++;
        argv[0] = tmp ;
        }
    else
        {
        const char * base = ( getenv("HOME") ? getenv("HOME") : "." ) ;
        sConfigFilename = std::string(base) + "/.snapshotserver" ;
        }
    pConfig = SnapshotConfig::GetDefaultConfig() ;
    pConfig -> InitServerDefaults() ;
    
    int verbosity = pConfig -> GetInt("Verbosity", 0) ;
    pConfig -> Set("Verbosity", verbosity) ;
    
    pLog = new SnapshotLog();
    
    try 
        {
        pConfig -> Load(sConfigFilename) ;
        log(1,std::string("Got config from ") + sConfigFilename) ;
        
        }
    catch(...)
        {
        log(1, "Use standard config\n") ;
        }
    
    pLog -> Init() ;
    
    server.config.address   = pConfig -> GetString("ServerAddress", "127.0.0.1") ;
    server.config.port      = pConfig -> GetInt("ServerPort", 8080) ;
    
    log(1, std::string("Server listening on ") 
            + pConfig -> GetString("ServerAddress", "127.0.0.1") 
            + ":" + pConfig -> GetString("ServerPort", "8080") ) ;
    
    SnapshotServer *pServer = new SnapshotServer(argc, argv, pConfig) ;
    pDefaultServer = pServer ;

    // JSON Posts: Query snapshots etc
    server.resource["^/json$"]["POST"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request)
        {
        pDefaultServer -> log(request);
        try
            {

            auto result = pDefaultServer -> Control(request);
            
             *response << "HTTP/1.1 200 OK\r\n"
                << "Content-Length: " << result.length() << "\r\n"
                << "Content-Type: application/json\r\n\r\n"
                << result;
                        
            }
        catch (const exception &e)
            {
            pDefaultServer -> log(e);
            response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
            }
        pDefaultServer -> log(response);
        };
        
    // uploads
    server.resource["^/ul$"]["POST"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request)
        {
        pDefaultServer -> log(request);
        try
            {

            string filepath = pDefaultServer -> Uploadpath(request);

            SimpleWeb::CaseInsensitiveMultimap header;

            auto ofs = make_shared<ofstream>();
            ofs->open(filepath, ofstream::out | ios::binary | ios::trunc);

            if (*ofs)
                {
                pDefaultServer ->receive_and_write(request, ofs);
                }
            else
                {
                
                }
                std::string content = "OK" ;
                *response << "HTTP/1.1 200 OK\r\n"
                         << "Content-Type: text/ascii\r\n"
                         << "Content-Length: " << content.length() << "\r\n\r\n"
                         << content;

/*             *response << "HTTP/1.1 200 OK\r\n" ;
                << "Content-Length: " << result.length() << "\r\n"
                << "Content-Type: application/json\r\n\r\n"
                << result; */
                        
            }
        catch (const exception &e)
            {
            pDefaultServer -> log(e);
            response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
            }
        pDefaultServer -> log(response);
        };
        
    // downloads
    server.resource["^/dl$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request)
        {
        pDefaultServer -> log(request);
        try
            {

            string filepath = pDefaultServer -> Downloadpath(request);
            auto path = boost::filesystem::canonical(filepath);
            SimpleWeb::CaseInsensitiveMultimap header;

            auto ifs = make_shared<ifstream>();
            ifs->open(filepath, ifstream::in | ios::binary | ios::ate);

            if (*ifs)
                {
                auto length = ifs->tellg();
                ifs->seekg(0, ios::beg);

                header.emplace("Content-Length", to_string(length));
                header.emplace("Content-Type", pDefaultServer->ext2mime(path.extension().c_str()));
                response->write(header);

                pDefaultServer ->read_and_send(response, ifs);
                }
            else
                {
                
                }
            
                        
            }
        catch (const exception &e)
            {
            pDefaultServer -> log(e);
            response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
            }
        pDefaultServer -> log(response);
        };

    // Default GET-example. If no other matches, this anonymous function will be called.
    // Will respond with content in the web/-directory, and its subdirectories.
    // Default file: index.html
    // Can for instance be used to retrieve an HTML 5 client that uses REST-resources on this server
    server.default_resource["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request)
        {
        pDefaultServer -> log(request);
        auto server_root_path = boost::filesystem::path( pConfig -> GetString("ServerRoot") ) ;
        auto web_root_path = server_root_path  / "src/server/html" ;
        try
            {
            auto path = web_root_path / request->path ;
            // Check if path is within web_root_path
            if (distance(web_root_path.begin(), web_root_path.end()) > distance(path.begin(), path.end()) ||
                !equal(web_root_path.begin(), web_root_path.end(), path.begin()))
                throw invalid_argument("path must be within root path");
            if (boost::filesystem::is_directory(path))
                path /= "index.html";

            SimpleWeb::CaseInsensitiveMultimap header;

            auto ifs = make_shared<ifstream>();
            ifs->open(path.string(), ifstream::in | ios::binary | ios::ate);

            if (*ifs)
                {
                auto length = ifs->tellg();
                ifs->seekg(0, ios::beg);

                header.emplace("Content-Length", to_string(length));
                header.emplace("Content-Type", pDefaultServer->ext2mime(path.extension().c_str()));
                response->write(header);
                pDefaultServer ->read_and_send(response, ifs);
                }
            else
                throw invalid_argument("could not read file");
            }
        catch (const exception &e)
            {
            pDefaultServer -> log(e);
            response->write(SimpleWeb::StatusCode::client_error_bad_request, "Could not open path " + request->path + ": " + e.what());
            }
        pDefaultServer -> log(response);
        };

    server.on_error = [](shared_ptr<HttpServer::Request> request, const SimpleWeb::error_code & ec)
        {
        pDefaultServer -> log(request, ec);
        };

    thread server_thread([&server]()
        {
        // Start server
        server.start();
        });

    // Wait for server to start so that the client can connect
    this_thread::sleep_for(chrono::seconds(1));

    server_thread.join();
    
    pConfig -> Save(sConfigFilename) ;

    }
