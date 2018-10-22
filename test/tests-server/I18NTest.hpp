/* 
 * File:   I18NTest.h
 * Author: Klaus Ramstöck
 *
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "TestFixture.h"
#include "src/common/I18N.hpp"

class I18NTest: public TestFixture
    {
    CPPUNIT_TEST_SUITE(I18NTest);

    CPPUNIT_TEST(testBasic);

    CPPUNIT_TEST_SUITE_END();

public:
    I18NTest();
    virtual ~I18NTest();
    void setUp();
    void tearDown();

private:
    void clean() ;
    void testBasic();
    
    };




