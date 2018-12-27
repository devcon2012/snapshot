#
#
#
# 
#
#a
message(STATUS "Client")

#wxWidgets_ROOT_DIR      - Base wxWidgets directory
#                          (e.g., C:/wxWidgets-2.6.3).
#wxWidgets_LIB_DIR       - Path to wxWidgets libraries
#                          (e.g., C:/wxWidgets-2.6.3/lib/vc_lib).
#wxWidgets_CONFIGURATION - Configuration to use
#                          (e.g., msw, mswd, mswu, mswunivud, etc.)
#wxWidgets_EXCLUDE_COMMON_LIBRARIES
#                        - Set to TRUE to exclude linking of
#                          commonly required libs (e.g., png tiff
#                          jpeg zlib regex expat).

find_package(wxWidgets REQUIRED core base) 

if ( NOT ${wxWidgets_FOUND} )
    message(FATAL_ERROR "No Wx!")
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common ${wxWidgets_INCLUDE_DIRS})
add_definitions(-I/usr/lib64/wx/include/gtk2-unicode-3.0 -I/usr/include/wx-3.0 -D_FILE_OFFSET_BITS=64 -DwxDEBUG_LEVEL=0 -DWXUSINGDLL -D__WXGTK__ -pthread
)

FILE(GLOB CLIENTSOURCES Client.cpp wx*.cpp)
FILE(GLOB CLIENTHEADERS *.hpp)

FILE(GLOB TOOLSOURCES Tool*.cpp )
FILE(GLOB TOOLHEADERS Tool*.hpp)

message(STATUS "Client sources/headers: " ${CLIENTSOURCES} ${CLIENTHEADERS} ${wxWidgets_CXX_FLAGS} )
source_group("Includes" REGULAR_EXPRESSION \\.hpp )

FILE(GLOB CLIENTLIBSOURCES Snapshot*.cpp Notificator.cpp)
message(STATUS "Clientlib: " ${CLIENTLIBSOURCES} )

set(MODULE_NAME "SnapshotClientLibrary")
set(MODULE_PREFIX "SNAPSHOTCLIENTLIB")

add_library(${MODULE_NAME} STATIC ${CLIENTLIBSOURCES})

add_executable(SnapshotClient ${CLIENTSOURCES} ${CLIENTHEADERS} )

target_link_libraries(SnapshotClient ${MODULE_NAME} SnapshotLibrary boost_filesystem boost_system ${wxWidgets_LIBRARIES}) 
   
add_executable(SnapshotTool ${TOOLSOURCES} ${TOOLHEADERS} )

target_link_libraries(SnapshotTool SnapshotLibrary SnapshotClientLibrary boost_filesystem boost_system pthread    ) 

