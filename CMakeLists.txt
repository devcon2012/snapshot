#
# RWS Mobile Office stick Cmake
#   Copyright (c) 2017 Klaus Ramstöck
#
#	Author:
#		Dr. Ing Klaus Ramstöck (klra67@freenet.de)
#
# Usage:
#       -DWITH_TESTS    build tests, too
#       

cmake_minimum_required(VERSION 2.8)

set(PRJNAME DEMO)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/script/cmake)

# Include cmake modules
if ( NOT ARCH )
    include(PlatformAutoDetect)
endif()

include(ProjectIncludes)

#add_definitions( -m32)
set(C_STD "")
set(CPP_STD "--std=c++14")
add_definitions(${CPP_STD})

set(REQUIRED_MODULES OpenSSL z)
set(OPTIONAL_MODULES WX APR)

if ( WINDOWS )
endif()

if ( APPLE )
endif()

if ( LINUX )
endif()

LOCATE_MODULES(REQUIRED ${REQUIRED_MODULES})
LOCATE_MODULES(OPTIONAL ${OPTIONAL_MODULES})

add_subdirectory(src)

if(WITH_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

MESSAGE(STATUS "<<< CONFIG >>>
ARCH = ${ARCH}
CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}
CMAKE_C_COMPILER_ID = ${CMAKE_C_COMPILER_ID}
CMAKE_C_COMPILER = ${CMAKE_C_COMPILER}
CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG}
CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE}
CMAKE_CXX_COMPILER_ID = ${CMAKE_C_COMPILER_ID}
CMAKE_CXX_COMPILER = ${CMAKE_C_COMPILER}
CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG}
CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE}
OPENSSL_INCLUDE_DIR = ${OPENSSL_LIBRARY_DIR}
OPENSSL_LIBRARY_DIR = ${OPENSSL_LIBRARY_DIR}
OPENSSL_LIBRARIES = ${OPENSSL_LIBRARIES}"
)
