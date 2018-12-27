/*
 * File:   ClientConnectTest.cpp
 * Author: ramst
 *
 * Created on 13.12.2012, 09:55:25
 */

#include "ClientConnectTest.hpp"
#include "client/Notificator.hpp"
#include <boost/filesystem.hpp>


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
    system("rm -rf /var/tmp/cct") ;
    }

/// teardown a test
void ClientConnectTest::tearDown()
    {
    clean() ;
    system("rm -rf /var/tmp/cct") ;
    }

/// basic test
void ClientConnectTest::testConnect()
    {
    
    }

std::string s1, s2, s3, s4, s5 ;
int wd ;
class testNotifyEventReader : public NotifyEventReader
    {
    virtual void OnClose(int wd, const path_t &p) 
        {s1 = std::string(p.c_str()) ; } 
    
    virtual void OnCreate(int wd, const path_t &p) 
        {s2 = std::string(p.c_str()) ; } 
    
    /* delete is the last op so we shutdown the thread here */
    virtual void OnDelete(int wdd, const path_t &p) 
        {s3 = std::string(p.c_str()) ; run=false ; wd=wdd; }
    
    virtual void OnMove(int wd, const path_t &from, const path_t &to) 
        {s4 = std::string(from.c_str()) ;
         s5 = std::string(to.c_str()) ;
        } 
    
    };

/// basic test
void ClientConnectTest::testNotify()
    {
    boost::filesystem::path p ;
    system("mkdir /var/tmp/cct") ;
    Notificator N("/var/tmp/cct") ;
    
    testNotifyEventReader R ;
    
    R.ReadEvents(N);

    system("touch /var/tmp/cct/bla") ;
    system("mv /var/tmp/cct/bla /var/tmp/cct/bla2") ;
    system("rm /var/tmp/cct/bla2") ;
    
    R.Stop() ;

    CPPUNIT_ASSERT_MESSAGE( "s1" , s1 == "bla" ) ;
    CPPUNIT_ASSERT_MESSAGE( "s2" , s2 == "bla" ) ;
    CPPUNIT_ASSERT_MESSAGE( "s3" , s3 == "bla2" ) ;
    CPPUNIT_ASSERT_MESSAGE( "s4" , s4 == "bla" ) ;
    CPPUNIT_ASSERT_MESSAGE( "s5" , s5 == "bla2" ) ;
    
    std::string wdpath = N.GetPath(wd) ;
    CPPUNIT_ASSERT_MESSAGE( "wd" , wdpath == "/var/tmp/cct" ) ;

    }

