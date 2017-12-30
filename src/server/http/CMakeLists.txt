#
#
#
#
#
#
message(STATUS "HTTPLib")

set(MODULE_NAME "HttpLibrary")
set(MODULE_PREFIX "HTTPLIB")

FILE(GLOB SERVERSOURCES *.cpp)
FILE(GLOB SERVERHEADERS *.hpp)

source_group("Includes" REGULAR_EXPRESSION \\.hpp )

add_library(${MODULE_NAME} INTERFACE)

target_include_directories(${MODULE_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Threads REQUIRED)
target_link_libraries(${MODULE_NAME} INTERFACE ${CMAKE_THREAD_LIBS_INIT})

# TODO 2020 when Debian Jessie LTS ends:
# Remove Boost system, thread, regex components; use Boost::<component> aliases; remove Boost target_include_directories
find_package(Boost 1.53.0 COMPONENTS system thread REQUIRED)
target_link_libraries(${MODULE_NAME} INTERFACE ${Boost_LIBRARIES})
target_include_directories(${MODULE_NAME} INTERFACE ${Boost_INCLUDE_DIR})
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
    target_compile_definitions(${MODULE_NAME} INTERFACE USE_BOOST_REGEX)
    find_package(Boost 1.53.0 COMPONENTS regex REQUIRED)
    target_link_libraries(${MODULE_NAME} INTERFACE ${Boost_LIBRARIES})
    target_include_directories(${MODULE_NAME} INTERFACE ${Boost_INCLUDE_DIR})
endif()

if(WIN32)
    target_link_libraries(${MODULE_NAME} INTERFACE ws2_32 wsock32)
endif()

find_package(OpenSSL)
if(OPENSSL_FOUND)
    target_compile_definitions(${MODULE_NAME} INTERFACE HAVE_OPENSSL)
    target_link_libraries(${MODULE_NAME} INTERFACE ${OPENSSL_LIBRARIES})
    target_include_directories(${MODULE_NAME} INTERFACE ${OPENSSL_INCLUDE_DIR})
endif()
