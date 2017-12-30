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
    
    boost::property_tree::ptree pt, res ;
    
        {
        //pt = m_pModel -> pt_from_json ("{'action': 'set', 'arg': 'clienthandle', 'subject': 'cn=test'}") ;
        pt = m_pModel -> pt_from_json ("{\"action\":\"set\"}") ;

        res = m_pModel -> SetClientHandle(pt) ;
        boost::property_tree::write_json(std::cerr, res) ;
        }
    }

