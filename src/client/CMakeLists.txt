#
#
#
#
#
#
message(STATUS "Client")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)

FILE(GLOB CLIENTSOURCES Client.cpp)
FILE(GLOB CLIENTHEADERS *.hpp)
message(STATUS "Client sources/headers: " ${CLIENTSOURCES} ${CLIENTHEADERS})

source_group("Includes" REGULAR_EXPRESSION \\.hpp )

FILE(GLOB CLIENTLIBSOURCES Snapshot*.cpp)

set(MODULE_NAME "SnapshotClientLibrary")
set(MODULE_PREFIX "SNAPSHOTCLIENTLIB")

add_library(${MODULE_NAME} STATIC ${CLIENTLIBSOURCES})

add_executable(SnapshotClient ${CLIENTSOURCES} ${CLIENTHEADERS} )

target_link_libraries(SnapshotClient ${MODULE_NAME} SnapshotLibrary boost_filesystem) 
   

