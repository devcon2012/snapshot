#
# CPPUnit - build cppunit if needed
#
#	Author:
#		CPPUnit developers
#		tiny mods by Dr. Ing. Klaus Ramstöck klaus@ramstoeck.name
#


if(WIN32)
	add_definitions( -DWIN32_LEAN_AND_MEAN )
	add_definitions( -D_CRT_SECURE_NO_DEPRECATE )
endif()


FILE(GLOB COMMONSOURCES *.cpp)
set(MODULE_NAME "SnapshotLibrary") 
set(MODULE_PREFIX "SNAPSHOTLIB")

add_library(${MODULE_NAME} STATIC ${COMMONSOURCES})


