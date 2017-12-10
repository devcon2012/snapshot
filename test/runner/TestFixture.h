/*
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>


class TestFixture : public CPPUNIT_NS::TestFixture 
    {


public:
    TestFixture();
    virtual ~TestFixture();

    void setUp();

    void tearDown();

protected:

    };


    