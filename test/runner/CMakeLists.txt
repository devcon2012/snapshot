#
#
#
#
#
#
message(STATUS "Test-runner library")


FILE(GLOB TESTSOURCES *.cpp)
message(STATUS "Testrunner sources: " ${TESTSOURCES})

FILE(GLOB TESTHEADERS *.h)
message(STATUS "Testrunner headers: " ${TESTHEADERS})

set(MODULE_NAME "runner")

add_library(runner STATIC ${TESTSOURCES} ${TESTHEADERS} )
source_group("Includes" REGULAR_EXPRESSION *.h )

add_dependencies(runner cppunit)
target_include_directories(runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
