#
#
#
#
#
#
message(STATUS "Tests")

enable_testing()

add_subdirectory(cppunit)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/runner)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tests)

FILE(GLOB RUNNERSOURCES runner/*.cpp)
FILE(GLOB RUNNERHEADERS runner/*.h)
message(STATUS "Runner sources/headers: " ${RUNNERSOURCES} ${RUNNERHEADERS})

FILE(GLOB TESTSOURCES tests/*.cpp)
FILE(GLOB TESTHEADERS tests/*.h)
message(STATUS "Test sources/headers: " ${TESTSOURCES} ${TESTHEADERS})
source_group("Includes" REGULAR_EXPRESSION *.h )

add_executable(test-runner ${RUNNERSOURCES} ${RUNNERHEADERS} ${TESTSOURCES} ${TESTHEADERS})

target_link_libraries(test-runner cppunit)
   
add_test(test1 test-runner arg1 arg2 ..)

