/*
 * File:   RWSTestRunner.cpp
 * Author: ecos
 *
 * Created on 16.01.2013, 16:23:22
 */

#include <cstring>
#include <cstdlib>
#include <assert.h>


#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

#include "TestSelektor.h"

int main_initializer(int argc, char **argv);

int main(int argc, char **argv)
    {
  

    main_initializer(argc, argv);    
    TestSelektor *pTestSelector = GetTestSelektor();

  
    // Create the event manager and test controller
    CPPUNIT_NS::TestResult controller;

    // Add a listener that collects test result
    CPPUNIT_NS::TestResultCollector result;
    controller.addListener(&result);

    // Add a listener that print dots as test run.
    //CPPUNIT_NS::BriefTestProgressListener progress;
    CPPUNIT_NS::TextTestProgressListener progress;
    controller.addListener(&progress);

    // Add the top suite to the test runner
    CPPUNIT_NS::TestRunner runner;
    
    CPPUNIT_NS::Test * autotest = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();

    CPPUNIT_NS::Test * myTests =  pTestSelector->makeMyTests(autotest);

    if(pTestSelector->isListOnly())
       {
           pTestSelector->List();
           return 0;
       }

    runner.addTest(myTests);

    runner.run(controller);

    
    // Print test in a compiler compatible format.
    CPPUNIT_NS::CompilerOutputter outputter(&result, CPPUNIT_NS::stdCOut());
    outputter.write();

    return result.wasSuccessful() ? 0 : 1;
    
    }


void Usage()
    {
    std::cout << "Usage: xxx-runner [-v] [-d] [-l] [-c <class>] [-t <test>]" << std::endl;
    std::cout << "-l list classes / tests " << std::endl;
    std::cout << "-c <class> test only class" << std::endl;
    std::cout << "-t <test> test only test" << std::endl;
    std::cout << "-v toggles verbose output" << std::endl;
    std::cout << "-d waits for keyboard input to allow debugger attach (include -v)" << std::endl;
    }

int main_initializer(int argc, char **argv)
    {

    TestSelektor *pTestSelector = GetTestSelektor();
    
    for(int i=1; i<argc; i++)
        {
        if(strcmp(argv[i], "-d") == 0)
            {
            std::cout << "Attach debugger and enter any string, then press enter" << std::endl;
            std::string bla;
            std::cin >> bla;
            continue;
            }
        if(strcmp(argv[i], "-v") == 0)
            {
            continue;
            }
        if(strcmp(argv[i], "-c") == 0)
            {
            i++;
            std::string sClass;
            if(i<argc)
                {
                sClass = std::string(argv[i]);
                }
            else
                {
                Usage();
                exit(1);
                }
            pTestSelector->RegisterClass(sClass);
            continue;
            }
        if(strcmp(argv[i], "-l") == 0)
            {
            pTestSelector->ListOnly();
            continue;
            }
        if(strcmp(argv[i], "-t") == 0)
            {
            i++;
            std::string sTest;
            if(i<argc)
                {
                sTest = std::string(argv[i]);
                }
            else
                {
                Usage();
                exit(1);
                }
            pTestSelector->RegisterTest(sTest);
            continue;
            }
        else
            {
            Usage();
            exit(1);
            }
        }
    
    
    return 0;
    }

