#
#
#
#
#
#
message(STATUS "Server")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)

FILE(GLOB SERVERSOURCES Server.cpp)
FILE(GLOB SERVERHEADERS *.hpp)
FILE(GLOB SERVERLIBSOURCES Snapshot*.cpp)
message(STATUS "Server sources/headers: " ${SERVERSOURCES} ${SERVERHEADERS})

source_group("Includes" REGULAR_EXPRESSION \\.hpp )

set(MODULE_NAME "SnapshotServerLibrary")
set(MODULE_PREFIX "SNAPSHOTSERVERLIB")
add_library(${MODULE_NAME} STATIC ${SERVERLIBSOURCES})

add_executable(SnapshotServer ${SERVERSOURCES} ${SERVERHEADERS} )

target_link_libraries(SnapshotServer ${MODULE_NAME} SnapshotLibrary) 
   
