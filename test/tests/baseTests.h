/* 
 * File:   baseTests.h
 * Author: Klaus Ramstöck
 *
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "TestFixture.h"

class baseTests: public TestFixture
    {
    CPPUNIT_TEST_SUITE(baseTests);

    CPPUNIT_TEST(testBasic);

    CPPUNIT_TEST_SUITE_END();

public:
    baseTests();
    virtual ~baseTests();
    void setUp();
    void tearDown();

private:
    void testBasic();
    };




