/*
 * File:   ServerModelTest.cpp
 * Author: ramst
 *
 * Created on 13.12.2012, 09:55:25
 */

#include "ServerModelTest.hpp"

#include <boost/filesystem.hpp>
using namespace boost::filesystem ;
using namespace std ;


CPPUNIT_TEST_SUITE_REGISTRATION(ServerModelTest);

/// Create a new SnapshotData object Test
ServerModelTest::ServerModelTest()
    {
    m_pModel = NULL; // ground pointer
    }

ServerModelTest::~ServerModelTest()
    {
    clean();
    }

/// delete all pointers that may be there
void ServerModelTest::clean()
    {
    if ( m_pModel )
        {
        delete m_pModel ;
        m_pModel = NULL ;
        }    
    }

/// setup a test - cleanup leftovers, create a test object
void ServerModelTest::setUp()
    {
    clean() ;
    m_pModel = new SnapshotServerModelKC () ;
    
    boost::property_tree::ptree test_settings 
            = m_pModel -> pt_from_json("{\"DBRoot\": \"/tmp\"}");
    m_pModel -> Provision(test_settings);
    }

/// teardown a test
void ServerModelTest::tearDown()
    {
    clean() ;
    }

/// basic test
void ServerModelTest::testBasic()
    {
    CPPUNIT_ASSERT_MESSAGE( "Test set up?" , m_pModel != NULL ) ;
    
    string sHandle = m_pModel -> create_handle() ;
    CPPUNIT_ASSERT_MESSAGE( "create_handle ok?" , sHandle.length() == 17 ) ;
    
    boost::property_tree::ptree pt, res ;
    
        {
        // Try missing args error response
        pt = m_pModel -> pt_from_json ("{\"action\":\"set\"}") ;

        res = m_pModel -> SetClientHandle(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "Missing args gives error?" , res.find("ERROR") != res.not_found() ) ;
        }

    string sClientHandle ;
        {
        // obtain a new handle
        pt = m_pModel -> pt_from_json ("{\"action\": \"set\", \"arg\": \"clienthandle\", \"subject\": \"cn=test\"}") ;

        res = m_pModel -> SetClientHandle(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "SetClientHandle gives no error?" , res.find("ERROR") == res.not_found() ) ;
        CPPUNIT_ASSERT_MESSAGE( "SetClientHandle yields handle?" , res.find("clienthandle") != res.not_found() ) ;
        sClientHandle = res.get<std::string>("clienthandle") ;
        }

        {
        // get handle
        pt = m_pModel -> pt_from_json ("{\"action\": \"get\", \"arg\": \"clienthandle\", \"subject\": \"cn=test\"}") ;

        res = m_pModel -> GetClientHandle(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "GetClientHandle gives no error?" , res.find("ERROR") == res.not_found() ) ;
        CPPUNIT_ASSERT_MESSAGE( "GetClientHandle yields handle?" , res.find("clienthandle") != res.not_found() ) ;
        std::string sClientHandle2 = res.get<std::string>("clienthandle") ;
        CPPUNIT_ASSERT_MESSAGE( "GetClientHandle got old handle?" , sClientHandle == sClientHandle2 ) ;
        }

        std::string sSnapshotHandle ;
        {
        // add a snapshot
        std::string sJSON = std::string("{\"action\": \"add\", "
                            " \"arg\": \"snapshot\","
                            " \"timestamp\": 131313,"
                            " \"clienthandle\": \"") + sClientHandle + "\"}" ;
        pt = m_pModel -> pt_from_json (sJSON) ;

        res = m_pModel -> AddSnapshot(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshot gives no error?" , res.find("ERROR") == res.not_found() ) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshot yields handle?" , res.find("snapshothandle") != res.not_found() ) ;
        sSnapshotHandle = res.get<std::string>("snapshothandle") ;
        }

        std::string sSnapshotPathHandle ;
        {
        // add a snapshot path
        std::string sJSON = std::string("{\"action\": \"add\", "
                            " \"arg\": \"snapshotpath\","
                            " \"path\": \"test\","
                            " \"clienthandle\": \"") + sClientHandle + "\"," 
                            " \"snapshothandle\": \""+ sSnapshotHandle + "\"}" ;
        pt = m_pModel -> pt_from_json (sJSON) ;

        res = m_pModel -> AddSnapshotPath(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotPath gives no error?" , res.find("ERROR") == res.not_found() ) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotPath yields handle?" , res.find("pathhandle") != res.not_found() ) ;
        sSnapshotPathHandle = res.get<std::string>("pathhandle") ;
        }
        
        std::string sSnapshotFileHandle ;
        {
        // add a snapshot path
        std::string sJSON = std::string("{\"action\": \"add\", "
                            " \"arg\": \"snapshotpath\","
                            " \"file\": \"test.txt\","
                            " \"clienthandle\": \"") + sClientHandle + "\"," 
                            " \"snapshothandle\": \""+ sSnapshotPathHandle + "\"}" ;
        pt = m_pModel -> pt_from_json (sJSON) ;

        res = m_pModel -> AddSnapshotFiles(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotFiles gives no error?" , res.find("ERROR") == res.not_found() ) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotFiles yields handle?" , res.find("filehandle") != res.not_found() ) ;
        sSnapshotFileHandle = res.get<std::string>("filehandle") ;
        }

    }

