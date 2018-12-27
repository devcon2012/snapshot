/*
 * File:   CATest.cpp
 * Author: ramst
 *
 * Created on 13.12.2012, 09:55:25
 */

#include "CATest.hpp"
#include "client/Notificator.hpp"
#include <boost/filesystem.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(CATest);

CATest::CATest() 
    {
    }

CATest::~CATest()
    {
    clean();
    }

/// delete all pointers that may be there
void CATest::clean()
    {
    }

/// setup a test - cleanup leftovers, create a test object
void CATest::setUp()
    {
    clean() ;
    }

/// teardown a test
void CATest::tearDown()
    {
    clean() ;
    }

/// basic test
void CATest::testCreate()
    {
    CACertificate *pCA = new CACertificate() ;
    
    delete pCA;
    }

