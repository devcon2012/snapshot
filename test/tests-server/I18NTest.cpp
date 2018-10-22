/*
 * File:   I18NTest.cpp
 * Author: ramst
 *
 * Created on 13.12.2012, 09:55:25
 */

#include "I18NTest.hpp"
#include "src/common/I18N.hpp"

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
    }

/// teardown a test
void I18NTest::tearDown()
    {
    clean() ;
    }

/// basi test
void I18NTest::testBasic()
    {
    I18N * pI18N = I18N::GetDefaultI18N() ;
    
    CPPUNIT_ASSERT_MESSAGE( "I18N exists?" , pI18N != NULL ) ;
    
    std::string sTestI18N = pI18N -> interpolate("test_i18n", "ARG1", "ARG2") ;
    CPPUNIT_ASSERT_MESSAGE( "I18N works (1)?" , sTestI18N == "I18N TEST: ARG1 ARG2" ) ;

    std::string sTestI18NNoArgs = pI18N -> interpolate("test_i18n" ) ;
    CPPUNIT_ASSERT_MESSAGE( "I18N works (2)?" , sTestI18NNoArgs == "I18N TEST:  " ) ;
    
    std::string sTestMissingI18N = pI18N -> interpolate("test_missing_i18n", "ARG1", "ARG2") ;
    CPPUNIT_ASSERT_MESSAGE( "I18N works (3)?" , sTestMissingI18N == "test_missing_i18n (I18N MISSING): ARG1 ARG2" );
 
    
    }
