/*
 * File:   ClientDataTest.cpp
 * Author: ramst
 *
 * Created on 13.12.2012, 09:55:25
 */

#include "ClientDataTest.hpp"

#include <boost/filesystem.hpp>
using namespace boost::filesystem ;

CPPUNIT_TEST_SUITE_REGISTRATION(ClientDataTest);

/// Create a new SnapshotData object Test
ClientDataTest::ClientDataTest()
    {
    m_pData = NULL; // ground pointer
    }

ClientDataTest::~ClientDataTest()
    {
    clean();
    }

/// delete all pointers that may be there
void ClientDataTest::clean()
    {
    if (m_pData )
        {
        delete m_pData ;
        m_pData = NULL ;
        }    
    }

/// setup a test - cleanup leftovers, create a test object
void ClientDataTest::setUp()
    {
    clean() ;
    m_pData = new SnapshotData () ;
    }

/// teardown a test
void ClientDataTest::tearDown()
    {
    clean() ;
    }

/// basic test
void ClientDataTest::testBasic()
    {
    CPPUNIT_ASSERT_MESSAGE( "Test set up?" , m_pData != NULL ) ;
    CPPUNIT_ASSERT_MESSAGE( "No servers predefined?" , m_pData->GetServerCount() == 0 ) ;
    m_pData -> AddServer("http://127.0.0.1:8888") ;
    CPPUNIT_ASSERT_MESSAGE( "One server defined?" , m_pData->GetServerCount() == 1 ) ;
    CPPUNIT_ASSERT_MESSAGE( "Server is ok?" , m_pData -> GetServer(0) == std::string("http://127.0.0.1:8888") ) ;
    
    
    CPPUNIT_ASSERT_MESSAGE( "No paths predefined?" , m_pData->GetPathCount() == 0 ) ;
        {
        bool bThrow = false ;
        try
            {
            m_pData -> AddPath("DOES_NOT_EXIST") ;
            }
        catch (...)
            {
            bThrow = true ;
            }
        CPPUNIT_ASSERT_MESSAGE( "Add non-existing path throws?" , bThrow == true ) ;
        }

        {
        path p = current_path() ;
        bool bThrow = false ;
        try
            {
            m_pData -> AddPath(p.c_str()) ;
            }
        catch (...)
            {
            bThrow = true ;
            }
        CPPUNIT_ASSERT_MESSAGE( "Add current path throws not?" , bThrow == false ) ;
        }
    
    }

/// collect test
void ClientDataTest::testCollect()
    {
    CPPUNIT_ASSERT_MESSAGE( "Test set up?" , m_pData != NULL ) ;
    m_pData -> AddServer("http://127.0.0.1:8888") ;
    path p = current_path() ;
    m_pData -> AddPath(p.c_str()) ;
    m_pData -> CollectFileSnapshot() ;
    
    int nFiles = m_pData -> GetSnapshotCount() ;
    CPPUNIT_ASSERT_MESSAGE( "Files found (>0)?" , nFiles >0 ) ;
    CPPUNIT_ASSERT_MESSAGE( "Files found (sane) ?" , nFiles <100 ) ;
    for (int i=0; i<nFiles; i++)
        {
        SnapshotData::tFileSnapshot s = m_pData -> GetSnapshot(i) ;
        path p1 = m_pData -> GetSnapshotPath(i) ;
        path p2 = m_pData -> GetSnapshotPath(s) ;
        std::string s1(p1.generic_string()), s2(p2.generic_string()) ;

        CPPUNIT_ASSERT_MESSAGE( "p1 == p2?"     , s1 == s2 ) ;        
        CPPUNIT_ASSERT_MESSAGE( "File exists"   , exists(p1) ) ;
        CPPUNIT_ASSERT_MESSAGE( "File size ok?" , file_size(p1) == s.nFileSize ) ;
        }
    }
