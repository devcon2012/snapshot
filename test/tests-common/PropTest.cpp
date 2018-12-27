/*
 * File:   PropTest.cpp
 * Author: ramst
 *
 * Created on 13.12.2012, 09:55:25
 */

#include "PropTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(PropTest);

/// Create a new SnapshotData object Test
PropTest::PropTest() 
    {
    }

PropTest::~PropTest()
    {
    clean();
    }

/// delete all pointers that may be there
void PropTest::clean()
    {
    }

/// setup a test - cleanup leftovers, create a test object
void PropTest::setUp()
    {
    clean() ;
    }

/// teardown a test
void PropTest::tearDown()
    {
    clean() ;
    }

/// basic test
void PropTest::testCreate()
    {
    const Dictionary xDict(std::vector({"A", "B", "C"})) ;
    Properties *pProp = new Properties() ;
    CPPUNIT_ASSERT_MESSAGE( "got new empty properties" , pProp ) ;

    delete pProp ;
    
    }

/// 
void PropTest::testProps()
    {
    
    }
