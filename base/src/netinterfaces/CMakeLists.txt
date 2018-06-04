cmake_minimum_required(VERSION 2.8)
project(netinterfaces)

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

include(${CMAKE_HOME_DIRECTORY}/base/src/interfaces/CMakeLists.txt)

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

link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(${PROJECT_NAME} STATIC
  netinterfaces/enginecontrolsendernet.cpp
  netinterfaces/enginecontrolreceivernet.cpp
  netinterfaces/renderercontrolreceivernet.cpp
  netinterfaces/renderercontrolsendernet.cpp
  netinterfaces/modelcontrolreceivernet.cpp
  netinterfaces/moduledatareceivernet.cpp
  netinterfaces/moduledatasendernet.cpp
  netinterfaces/moduleconstructiondumbreceivernet.cpp
  netinterfaces/modelcontrolsendernet.cpp
  netinterfaces/moduleconstructiondumbsendernet.cpp
  netinterfaces/moduleclassinforeceivernet.cpp
  netinterfaces/moduleclassinfosendernet.cpp
  netinterfaces/controlvaluereceivernet.cpp
  netinterfaces/controlvaluesendernet.cpp
  netinterfaces/modulestatisticsreceivernet.cpp
  netinterfaces/modulestatisticssendernet.cpp
  netinterfaces/errorsendernet.cpp
  netinterfaces/errorreceivernet.cpp
  netinterfaces/graphnamereceivernet.cpp
  netinterfaces/graphnamesendernet.cpp
  netinterfaces/modelstatusreceivernet.cpp
  netinterfaces/modelstatussendernet.cpp
  netinterfaces/rendererstatusreceivernet.cpp
  netinterfaces/rendererstatussendernet.cpp
  netinterfaces/graphdatareceivernet.cpp
  netinterfaces/graphdatasendernet.cpp
  netinterfaces/controlvaluereceivernet.h
  netinterfaces/controlvaluesendernet.h
  netinterfaces/enginecontrolreceivernet.h
  netinterfaces/enginecontrolsendernet.h
  netinterfaces/errorreceivernet.h
  netinterfaces/errorsendernet.h
  netinterfaces/graphnamereceivernet.h
  netinterfaces/graphnamesendernet.h
  netinterfaces/modelcontrolreceivernet.h
  netinterfaces/modelcontrolsendernet.h
  netinterfaces/moduleclassinforeceivernet.h
  netinterfaces/moduleclassinfosendernet.h
  netinterfaces/moduleconstructiondumbreceivernet.h
  netinterfaces/moduleconstructiondumbsendernet.h
  netinterfaces/moduledatareceivernet.h
  netinterfaces/moduledatasendernet.h
  netinterfaces/modulestatisticsreceivernet.h
  netinterfaces/modulestatisticssendernet.h
  netinterfaces/renderercontrolreceivernet.h
  netinterfaces/renderercontrolsendernet.h
  netinterfaces/modelstatusreceivernet.h
  netinterfaces/modelstatussendernet.h
  netinterfaces/rendererstatusreceivernet.h
  netinterfaces/rendererstatussendernet.h
  netinterfaces/graphdatareceivernet.h
  netinterfaces/graphdatasendernet.h
)

# ${CMAKE_CURRENT_LIST_DIR}/nodelcontrolreceivertest.h

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

