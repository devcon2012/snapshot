/*
 * File:   ClientConnectTest.cpp
 * Author: ramst
 *
 * Created on 13.12.2012, 09:55:25
 */

#include "ClientConnectTest.hpp"

#include <boost/filesystem.hpp>
using namespace boost::filesystem ;

CPPUNIT_TEST_SUITE_REGISTRATION(ClientConnectTest);

/// Create a new SnapshotData object Test
ClientConnectTest::ClientConnectTest() 
    {
    m_pData = NULL; // ground pointer
    }

ClientConnectTest::~ClientConnectTest()
    {
    clean();
    }

/// delete all pointers that may be there
void ClientConnectTest::clean()
    {
    if (m_pData )
        {
        delete m_pData ;
        m_pData = NULL ;
        }    
    }

/// setup a test - cleanup leftovers, create a test object
void ClientConnectTest::setUp()
    {
    clean() ;
    m_pData = new SnapshotData () ;
    }

/// teardown a test
void ClientConnectTest::tearDown()
    {
    clean() ;
    }

/// basic test
void ClientConnectTest::testConnect()
    {
    
    }

