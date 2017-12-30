/* 
 * File:   Server.cpp
 * Author: klaus
 *
 * Created on 25. Dezember 2017, 21:02
 */

#include <cstdlib>
#include "SnapshotServer.hpp"

#include "http/server_http.hpp"

// Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// Added for the default_resource example
#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>
#include "http/crypto.hpp"

using namespace std;
using namespace boost::property_tree;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

SnapshotServer * pDefaultServer = NULL ;


int main(int argc, char **argv)
    {
    // HTTP-server at port 8080 using 1 thread
    // Unless you do more heavy non-threaded processing in the resources,
    // 1 thread is usually faster than several threads
    HttpServer server;
    server.config.port = 8080;
    
    SnapshotServer *pServer = new SnapshotServer(argc, argv);
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

            auto result = pDefaultServer -> Upload(request);
            
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
        
    // downloads
    server.resource["^/dl$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request)
        {
        pDefaultServer -> log(request);
        try
            {

            auto result = pDefaultServer -> Download(request);
            
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

    // Default GET-example. If no other matches, this anonymous function will be called.
    // Will respond with content in the web/-directory, and its subdirectories.
    // Default file: index.html
    // Can for instance be used to retrieve an HTML 5 client that uses REST-resources on this server
    server.default_resource["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request)
        {
        pDefaultServer -> log(request);
        try
            {
            auto web_root_path = boost::filesystem::canonical("html");
            auto path = boost::filesystem::canonical(web_root_path / request->path);
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

                // Trick to define a recursive function within this scope (for example purposes)

                class FileServer
                    {
                public:

                    static void read_and_send(const shared_ptr<HttpServer::Response> &response, const shared_ptr<ifstream> &ifs)
                        {
                        // Read and send 128 KB at a time
                        static vector<char> buffer(131072); // Safe when server is running on one thread
                        streamsize read_length;
                        if ((read_length = ifs->read(&buffer[0], static_cast<streamsize> (buffer.size())).gcount()) > 0)
                            {
                            response->write(&buffer[0], read_length);
                            if (read_length == static_cast<streamsize> (buffer.size()))
                                {
                                response->send([response, ifs](const SimpleWeb::error_code & ec)
                                    {
                                    if (!ec)
                                        read_and_send(response, ifs);
                                    else
                                        cerr << "Connection interrupted" << endl;
                                    });
                                }
                            }
                        }
                                    };
                FileServer::read_and_send(response, ifs);
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
    }
