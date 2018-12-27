
#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "TestFixture.h"
#include "src/common/CACertificate.hpp"

class CATest: public TestFixture
    {
    CPPUNIT_TEST_SUITE(CATest);

    CPPUNIT_TEST(testCreate);

    CPPUNIT_TEST_SUITE_END();

public:
    CATest();
    virtual ~CATest();
    void setUp();
    void tearDown();

private:
    void clean() ;
    void testCreate() ;
    
    };




