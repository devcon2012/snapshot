/*
 * File:   KeyTest.cpp
 * Author: ramst
 *
 * Created on 13.12.2012, 09:55:25
 */

#include "KeyTest.hpp"
#include "client/Notificator.hpp"
#include <boost/filesystem.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(KeyTest);

/// Create a new SnapshotData object Test
KeyTest::KeyTest() 
    {
    }

KeyTest::~KeyTest()
    {
    clean();
    }

/// delete all pointers that may be there
void KeyTest::clean()
    {
    system("rm -f /tmp/sav.pem") ;
    }

/// setup a test - cleanup leftovers, create a test object
void KeyTest::setUp()
    {
    clean() ;
    }

/// teardown a test
void KeyTest::tearDown()
    {
    clean() ;
    }

/// basic test
void KeyTest::testCreate()
    {
    
    Key *pKey = new Key() ;
    CPPUNIT_ASSERT_MESSAGE( "got new empty key" , pKey ) ;
    CPPUNIT_ASSERT_MESSAGE( "has privkey?" , ! pKey->hasPrivKey() ) ;

    pKey -> NewRSA(512) ;
    CPPUNIT_ASSERT_MESSAGE( "created new rsa key" , pKey->hasPrivKey() ) ;
    
    pKey -> SavePEM("/tmp/sav.pem") ;

    delete pKey ;
    
    }

/// 
void KeyTest::testProps()
    {
    
    Key *pKey = new Key() ;
    pKey -> LoadPEM("/tmp/sav.pem") ;
    std::string fp = pKey -> Fingerprint() ;
    
    int siz = pKey -> Size() ;
    CPPUNIT_ASSERT_MESSAGE( "Key size ok" , siz == 512 ) ;
    
    delete pKey ;    
    }

/// load/save etc.
void KeyTest::testReadWrite()
    {
    
    Key *pKey = new Key() ;
    pKey -> NewRSA(512) ;
    CPPUNIT_ASSERT_MESSAGE( "created new rsa key" , pKey->hasPrivKey() ) ;
    std::string fp = pKey -> Fingerprint() ;
    
    pKey -> SavePEM("/tmp/sav.pem") ;
    
    Key *pKey2 = new Key() ;
    pKey2 -> LoadPEM("/tmp/sav.pem") ;

    std::string fp2 = pKey2 -> Fingerprint() ;

    CPPUNIT_ASSERT_MESSAGE( "load of saved worked" , fp == fp2 ) ;
    
    delete pKey ;
    delete pKey2 ;
  
    }


