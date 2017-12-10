#
# CPPUnit - build cppunit if needed
#
#	Author:
#		CPPUnit developers
#		tiny mods by Dr. Ing. Klaus Ramstöck klaus@ramstoeck.name
#


if(WIN32)
	add_definitions( -D_MBCS_DISABLED )
	add_definitions( -DWIN32_LEAN_AND_MEAN )
	add_definitions( -D_WIN32_WINNT=0x0400 )
	add_definitions( -D_CRT_SECURE_NO_DEPRECATE )
endif()


FILE(GLOB CPPUNITSOURCES src/*.cpp)
set(MODULE_NAME "cppunit")
set(MODULE_PREFIX "CPPUNIT")

set(CPPUNIT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${MODULE_NAME} STATIC ${CPPUNITSOURCES})
target_include_directories(${MODULE_NAME} PUBLIC ${CPPUNIT_INCLUDE_DIR})

