
# LOCATE_MODULES: 

MACRO(SHIFT RESULT LISTVAR)
    LIST(GET ${LISTVAR} 0 ${RESULT})
    LIST(REMOVE_AT ${LISTVAR} 0)
ENDMACRO(SHIFT)


function(LOCATE_MODULES )
    SHIFT(MODE ARGV)
    message(STATUS "Locate Modules ${MODE}: " ${ARGV} )
    foreach(_lib ${ARGV})
    message(STATUS "locate ${_lib}")
    endforeach()

endfunction()

