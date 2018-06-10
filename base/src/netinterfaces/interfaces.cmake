cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../../../base/src
  ${CMAKE_CURRENT_LIST_DIR}/../../../engine/src/engine
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/framebuffertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/numbertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/positiontype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/stringtype
#  ${CMAKE_CURRENT_LIST_DIR}/../../../util/include
  ${CMAKE_CURRENT_LIST_DIR}/../../../util/src/libgeo
  ${CMAKE_CURRENT_LIST_DIR}/../libscale
  ${CMAKE_CURRENT_LIST_DIR}/../libcolorconv
  ${CMAKE_CURRENT_BINARY_DIR}
)

include(${CMAKE_HOME_DIRECTORY}/base/src/interfaces/interfaces.cmake)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/netinterfaces)

foreach(T_NAME ${IF_SOURCES})
add_custom_command(OUTPUT netinterfaces/${T_NAME}receivernet.h
    PRE_BUILD
    COMMAND python ${CMAKE_HOME_DIRECTORY}/base/nic.py nrh ${CMAKE_CURRENT_BINARY_DIR}/netinterfaces ${CMAKE_HOME_DIRECTORY}/base/src/interfaces/${T_NAME}.if
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_HOME_DIRECTORY}/base/src/interfaces/${T_NAME}.if interfaces/i${T_NAME}receiver.h
    COMMENT "generating i${T_NAME}receivernet.h"
)

add_custom_command(OUTPUT netinterfaces/${T_NAME}receivernet.cpp
    PRE_BUILD
    COMMAND python ${CMAKE_HOME_DIRECTORY}/base/nic.py nrc ${CMAKE_CURRENT_BINARY_DIR}/netinterfaces ${CMAKE_HOME_DIRECTORY}/base/src/interfaces/${T_NAME}.if
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_HOME_DIRECTORY}/base/src/interfaces/${T_NAME}.if
    COMMENT "generating i${T_NAME}receivernet.cpp"
)

add_custom_command(OUTPUT netinterfaces/${T_NAME}sendernet.h
    PRE_BUILD
    COMMAND python ${CMAKE_HOME_DIRECTORY}/base/nic.py nsh ${CMAKE_CURRENT_BINARY_DIR}/netinterfaces ${CMAKE_HOME_DIRECTORY}/base/src/interfaces/${T_NAME}.if
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_HOME_DIRECTORY}/base/src/interfaces/${T_NAME}.if interfaces/i${T_NAME}sender.h
    COMMENT "generating i${T_NAME}sendernet.h"
)

add_custom_command(OUTPUT netinterfaces/${T_NAME}sendernet.cpp
    PRE_BUILD
    COMMAND python ${CMAKE_HOME_DIRECTORY}/base/nic.py nsc ${CMAKE_CURRENT_BINARY_DIR}/netinterfaces ${CMAKE_HOME_DIRECTORY}/base/src/interfaces/${T_NAME}.if
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_HOME_DIRECTORY}/base/src/interfaces/${T_NAME}.if
    COMMENT "generating i${T_NAME}sendernet.cpp"
)

endforeach()

