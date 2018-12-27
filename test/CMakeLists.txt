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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

find_package(KyotoCabinet REQUIRED ) 
include_directories(${KYOTOCABINET_INCLUDE_DIR})

FILE(GLOB RUNNERSOURCES runner/*.cpp)
FILE(GLOB RUNNERHEADERS runner/*.h)
message(STATUS "Runner sources/headers: " ${RUNNERSOURCES} ${RUNNERHEADERS}) 

# Common tests
FILE(GLOB TESTSCOMMONSOURCES tests-common/*Test.cpp)
FILE(GLOB TESTSCOMMONHEADERS tests-common/*.h)
message(STATUS "Test common sources/headers: " ${TESTSCOMMONSOURCES} ${TESTSCOMMONHEADERS})
source_group("Includes" REGULAR_EXPRESSION \\.hp* )

add_definitions(-Wno-unused-but-set-variable)

add_executable(test-runner-common ${RUNNERSOURCES} ${RUNNERHEADERS} ${TESTSCOMMONSOURCES} ${TESTSCOMMONHEADERS})

target_link_libraries(test-runner-common 
                        cppunit SnapshotLibrary SnapshotClientLibrary SnapshotServerLibrary
                        ${KYOTOCABINET_LIBRARIES}
                        boost_filesystem boost_system) 
   
# Server tests
FILE(GLOB TESTSERVERSOURCES tests-server/*Test.cpp)
FILE(GLOB TESTSERVERHEADERS tests-server/*.h)
message(STATUS "Test Server sources/headers: " ${TESTSERVERSOURCES} ${TESTSERVERHEADERS})
source_group("Includes" REGULAR_EXPRESSION \\.hp* )

add_definitions(-Wno-unused-but-set-variable)

add_executable(test-runner-server ${RUNNERSOURCES} ${RUNNERHEADERS} ${TESTSERVERSOURCES} ${TESTSERVERHEADERS})

target_link_libraries(test-runner-server 
                        cppunit SnapshotLibrary SnapshotClientLibrary SnapshotServerLibrary
                        ${KYOTOCABINET_LIBRARIES}
                        boost_filesystem boost_system) 

# Client tests
FILE(GLOB TESTCLIENTSOURCES tests-client/*Test.cpp)
FILE(GLOB TESTCLIENTHEADERS tests-client/*.h)
message(STATUS "Test Client sources/headers: " ${TESTCLIENTSOURCES} ${TESTCLIENTHEADERS})
source_group("Includes" REGULAR_EXPRESSION \\.hp* )

add_definitions(-Wno-unused-but-set-variable)

add_executable(test-runner-client ${RUNNERSOURCES} ${RUNNERHEADERS} ${TESTCLIENTSOURCES} ${TESTCLIENTHEADERS})

target_link_libraries(test-runner-client 
                        cppunit SnapshotClientLibrary SnapshotLibrary SnapshotServerLibrary
                        ${KYOTOCABINET_LIBRARIES}
                        boost_filesystem boost_system pthread) 
   

# kcdump tool
add_executable(kcdump kcdump.cpp)
target_link_libraries(kcdump 
                        ${KYOTOCABINET_LIBRARIES}
                        boost_filesystem boost_system) 
    
add_test(test1 test-runner-server arg1 arg2 ..)
add_test(test2 test-runner-client arg1 arg2 ..)

