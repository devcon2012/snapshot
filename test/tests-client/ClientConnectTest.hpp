
#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "TestFixture.h"
#include "src/client/SnapshotData.hpp"

class ClientConnectTest: public TestFixture
    {
    CPPUNIT_TEST_SUITE(ClientConnectTest);

    CPPUNIT_TEST(testConnect);
    CPPUNIT_TEST(testNotify);

    CPPUNIT_TEST_SUITE_END();

public:
    ClientConnectTest();
    virtual ~ClientConnectTest();
    void setUp();
    void tearDown();

private:
    void clean() ;
    void testConnect() ;
    void testNotify() ;
    
    SnapshotData * m_pData ;
    };




