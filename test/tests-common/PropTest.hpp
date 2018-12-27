
#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "TestFixture.h"
#include "src/common/Properties.hpp"

class PropTest: public TestFixture
    {
    CPPUNIT_TEST_SUITE(PropTest);

    CPPUNIT_TEST(testCreate);
    CPPUNIT_TEST(testProps);

    CPPUNIT_TEST_SUITE_END();

public:
    PropTest();
    virtual ~PropTest();
    void setUp();
    void tearDown();

private:
    void clean() ;
    void testCreate() ;
    void testProps() ;
    
    };




