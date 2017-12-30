# FindKYOTOCABINET
# ----------
#
# Try to find Kyoto Cabinet. Hints:
#       ${KYOTOCABINET_ROOT}
#       ENV  KYOTOCABINET_INCLUDE  KYOTOCABINET_LIBRARY
#
# Once done this will define
#
# ::
#
#   KYOTOCABINET_FOUND - system has KyotoCabinet
#   KYOTOCABINET_INCLUDE_DIR - the KyotoCabinet include directory
#   KYOTOCABINET_LIBRARIES - The libraries needed to use KyotoCabinet
#   KYOTOCABINET_DEFINITIONS - Compiler switches required for using KyotoCabinet
#
#
#
# ::
#
#   KYOTOCABINET_VERSION_STRING - The version of KyotoCabinet found (x.y)
#   KYOTOCABINET_MAJOR_VERSION  - the major version of KyotoCabinet
#   KYOTOCABINET_MINOR_VERSION  - The minor version of KyotoCabinet


find_path(KYOTOCABINET_INCLUDE_DIR kcdb.h
            HINTS ${KYOTOCABINET_ROOT}/include ENV KYOTOCABINET_INCLUDE)

find_library(KYOTOCABINET_LIBRARIES NAMES kyotocabinet
            HINTS ${KYOTOCABINET_ROOT}/lib ${KYOTOCABINET_ROOT}/lib64 ENV KYOTOCABINET_LIB)
        

if (KYOTOCABINET_INCLUDE_DIR)
    #file(STRINGS "${KYOTOCABINET_INCLUDE_DIR}/hspell.h" KYOTOCABINET_H REGEX "#define KYOTOCABINET_VERSION_M(AJO|INO)R [0-9]+")
    #string(REGEX REPLACE ".*#define KYOTOCABINET_VERSION_MAJOR ([0-9]+).*" "\\1" KYOTOCABINET_VERSION_MAJOR "${KYOTOCABINET_H}")
    #string(REGEX REPLACE ".*#define KYOTOCABINET_VERSION_MINOR ([0-9]+).*" "\\1" KYOTOCABINET_VERSION_MINOR "${KYOTOCABINET_H}")
    set(KYOTOCABINET_VERSION_STRING "1.2")
    unset(KYOTOCABINET_H)
endif()

# handle the QUIETLY and REQUIRED arguments and set KYOTOCABINET_FOUND to TRUE if
# all listed variables are TRUE
#include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(KYOTOCABINET
                                  REQUIRED_VARS KYOTOCABINET_LIBRARIES KYOTOCABINET_INCLUDE_DIR
                                  VERSION_VAR KYOTOCABINET_VERSION_STRING)

mark_as_advanced(KYOTOCABINET_INCLUDE_DIR KYOTOCABINET_LIBRARIES)

 
