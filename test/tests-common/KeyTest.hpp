
#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "TestFixture.h"
#include "src/common/Key.hpp"

class KeyTest: public TestFixture
    {
    CPPUNIT_TEST_SUITE(KeyTest);

    CPPUNIT_TEST(testCreate);
    CPPUNIT_TEST(testProps);
    CPPUNIT_TEST(testReadWrite);

    CPPUNIT_TEST_SUITE_END();

public:
    KeyTest();
    virtual ~KeyTest();
    void setUp();
    void tearDown();

private:
    void clean() ;
    void testCreate() ;
    void testProps() ;
    void testReadWrite() ;
    
    };




