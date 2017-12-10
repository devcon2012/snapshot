
/* 
 * File:   TestSelektor.cpp
 * Author: klaus
 * 
 * Created on 22. Oktober 2017, 17:33
 */

#include "TestSelektor.h"


TestSelektor::TestSelektor() 
    {
    m_bMustCheck = false;
    m_bListOnly = false;
    }

TestSelektor::~TestSelektor() {}

void TestSelektor::ListOnly()
    {
    m_bListOnly = true;
    }

void TestSelektor::List()
{
    std::cout << "Registered Classes & Tests: " << std::endl;
    dumpTestSuite(m_pTestSuite, 0);
}

void TestSelektor::addToList( const std::string & sClass, const std::string & sTest)
{
    std::string sTestClass = sClass + "::" + sTest;
    m_sClassTestList.push_back(sTestClass);
}

void TestSelektor::RegisterClass(const std::string &sClass)
{
    m_bMustCheck = true;
    m_sClasses.push_back(sClass);
}

void TestSelektor::RegisterTest(const std::string &sTest)
    {
    m_bMustCheck = true;
    m_sTests.push_back(sTest);
    }
    
void TestSelektor::testMatches(CPPUNIT_NS::Test * pTest, CPPUNIT_NS::TestSuite * pSelection, int nLevel)
    {
    std::string sName = pTest->getName();
    if( nLevel == 0 )
        {
        if( m_sClasses.size() == 0 )
            for(int j=0; j<pTest->getChildTestCount(); j++)
                 testMatches(pTest->getChildTestAt(j), pSelection, 1);

        for(auto i= m_sClasses.begin(); i!= m_sClasses.end(); i++ )
            {
            if( sName == *i )
                {
                // Ganze Klasse dazu
                pSelection->addTest(pTest);
                continue;
                }
            for(int j=0; j<pTest->getChildTestCount(); j++)
                testMatches(pTest->getChildTestAt(j), pSelection, 1);
            }
        }
    else
        {
        if( m_sTests.size() == 0 && m_sClasses.size() == 0)
            pSelection->addTest(pTest);
        for(auto i= m_sTests.begin(); i!= m_sTests.end(); i++ )
            {
            if(sName == *i)
                {
                pSelection->addTest(pTest);
                continue;
                }
            }
        }
    }

void TestSelektor::Cleanup()
    {

    }
    
CPPUNIT_NS::Test * TestSelektor::makeMyTests(CPPUNIT_NS::Test * pFullTestSet)
    {
    // dumpTestSuite(pFullTestSet);
    CPPUNIT_NS::TestSuite *pMySelection = new CPPUNIT_NS::TestSuite("my selection");

    for ( int i=0; i < pFullTestSet->getChildTestCount (); i++)
        {
        CPPUNIT_NS::Test *pChild = pFullTestSet->getChildTestAt(i);
        testMatches(pChild, pMySelection, 0);
        }
    //dumpTestSuite(pMySelection);

    m_pTestSuite = pMySelection;
    
    return pMySelection;
    }

void TestSelektor::dumpTestSuite(CPPUNIT_NS::Test * pTest, int level)
{
	static std::string sIndent("                    ");
	std::cerr << sIndent.substr(0, level) << "Test name: " << pTest->getName() << std::endl;
	if (pTest->getChildTestCount() > 0)
	{
		std::cerr << sIndent.substr(0, level) << "Kids: " << pTest->getChildTestCount() << std::endl;
		for (int i = 0; i < pTest->getChildTestCount(); i++)
		{
			dumpTestSuite(pTest->getChildTestAt(i), level + 1);
		}
	}
}
    
    
static TestSelektor *pTestSelector = NULL;

TestSelektor * GetTestSelektor()
    {
    if(! pTestSelector )
        pTestSelector = new TestSelektor;
    
    return pTestSelector;
    }


