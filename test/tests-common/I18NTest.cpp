/*
 * File:   I18NTest.cpp
 * Author: ramst
 *
 * Created on 13.12.2012, 09:55:25
 */

#include "I18NTest.hpp"
#include "client/Notificator.hpp"
#include <boost/filesystem.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(I18NTest);

/// Create a new SnapshotData object Test
I18NTest::I18NTest() 
    {
    }

I18NTest::~I18NTest()
    {
    clean();
    }

/// delete all pointers that may be there
void I18NTest::clean()
    {
    }

/// setup a test - cleanup leftovers, create a test object
void I18NTest::setUp()
    {
    clean() ;
    }

/// teardown a test
void I18NTest::tearDown()
    {
    clean() ;
    }

/// basic test
void I18NTest::testCreate()
    {
    I18NCollector *pI18NCollector = I18NCollector::GetI18NCollector(".") ;
    
    CPPUNIT_ASSERT_MESSAGE( "got new empty I18NCollector" , pI18NCollector ) ; 
    
    I18N * pI18Nde = pI18NCollector ->GetI18N("de") ;
    CPPUNIT_ASSERT_MESSAGE( "got new de I18N" , pI18Nde ) ; 

    pI18Nde -> addTag("load", "Laden") ;

    delete pI18NCollector ;    
    }

