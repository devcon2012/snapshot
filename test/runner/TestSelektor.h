
/* 
 * File:   TestSelektor.h
 * Author: klaus
 *
 * Created on 22. Oktober 2017, 17:33
 */

#pragma once

#include <cstdlib>
#include <vector>
#include <cppunit/extensions/HelperMacros.h>

class TestSelektor
    {
public:
    TestSelektor();
    ~TestSelektor();
    
    void RegisterClass(const std::string &sClass);
    void RegisterTest(const std::string &sTest);

    void ListOnly();
    void List();
    bool isListOnly() { return m_bListOnly; }
    void addToList(const std::string &sClass, const std::string &sTest);
        
    bool ChecksEnabled() const { return m_bMustCheck; }
    CPPUNIT_NS::Test * makeMyTests(CPPUNIT_NS::Test * pFullTestSet);

    void dumpTestSuite(CPPUNIT_NS::Test * pTest, int nLevel = 0);
    void testMatches(CPPUNIT_NS::Test * pTest, CPPUNIT_NS::TestSuite * pSelection, int nLevel);
    void Cleanup();
protected:
        
    bool                        m_bMustCheck;

    bool                        m_bListOnly;
    std::vector<std::string>    m_sClassTestList;
    
    std::vector<std::string>    m_sClasses;
    std::vector<std::string>    m_sTests;
    CPPUNIT_NS::Test          * m_pTestSuite;

    };
    
TestSelektor * GetTestSelektor();
