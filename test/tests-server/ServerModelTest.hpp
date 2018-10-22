/* 
 * File:   baseTests.h
 * Author: Klaus Ramstöck
 *
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "TestFixture.h"
#include "src/server/SnapshotServerModelKC.hpp"  

class ServerModelTest: public TestFixture
    {
    CPPUNIT_TEST_SUITE(ServerModelTest);

    CPPUNIT_TEST(testBasic);

    CPPUNIT_TEST_SUITE_END();

public:
    ServerModelTest();
    virtual ~ServerModelTest();
    void setUp();
    void tearDown();

private:
    void clean() ;
    void testBasic();
    
    SnapshotServerModel * m_pModel ;
    };




