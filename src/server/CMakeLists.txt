#
#
#
#
#
#
message(STATUS "Server") 

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)

find_package(KyotoCabinet REQUIRED ) 
include_directories(${KYOTOCABINET_INCLUDE_DIR})

FILE(GLOB SERVERSOURCES Server.cpp)
FILE(GLOB SERVERHEADERS Server.hpp)
FILE(GLOB SERVERLIBSOURCES Snapshot*.cpp) 
FILE(GLOB SERVERLIBHEADERS Snapshot*.hpp) 
message(STATUS "Server sources/headers: " ${SERVERSOURCES} ${SERVERHEADERS})
message(STATUS "ServerLib sources/headers: " ${SERVERLIBSOURCES} )

# kyotocabinet requires this or we get spammed
add_definitions(-Wno-unused-but-set-variable)

source_group("Includes" REGULAR_EXPRESSION \\.hpp )

set(MODULE_NAME "SnapshotServerLibrary")
set(MODULE_PREFIX "SNAPSHOTSERVERLIB")
add_library(${MODULE_NAME} STATIC ${SERVERLIBSOURCES} ${SERVERLIBHEADERS})

add_executable(SnapshotServer ${SERVERSOURCES} ${SERVERHEADERS} )

target_link_libraries(SnapshotServer ${MODULE_NAME} SnapshotLibrary 
                        ${KYOTOCABINET_LIBRARIES}
                        boost_filesystem boost_system crypto ssl
                        pthread ) 
   
