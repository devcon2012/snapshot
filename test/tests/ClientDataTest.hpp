/* 
 * File:   baseTests.h
 * Author: Klaus Ramstöck
 *
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "TestFixture.h"
#include "src/client/SnapshotData.hpp"

class ClientDataTest: public TestFixture
    {
    CPPUNIT_TEST_SUITE(ClientDataTest);

    CPPUNIT_TEST(testBasic);
    CPPUNIT_TEST(testCollect);

    CPPUNIT_TEST_SUITE_END();

public:
    ClientDataTest();
    virtual ~ClientDataTest();
    void setUp();
    void tearDown();

private:
    void clean() ;
    void testBasic();
    void testCollect();
    
    SnapshotData * m_pData ;
    };




