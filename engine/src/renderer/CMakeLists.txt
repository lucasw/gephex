cmake_minimum_required(VERSION 2.8)
project(renderer)

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

link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(${PROJECT_NAME} STATIC
  ${CMAKE_CURRENT_LIST_DIR}/renderer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/runtimesystem.cpp
  ${CMAKE_CURRENT_LIST_DIR}/modulefactory.cpp
  ${CMAKE_CURRENT_LIST_DIR}/typefactory.cpp
  ${CMAKE_CURRENT_LIST_DIR}/modulefactory.h
  ${CMAKE_CURRENT_LIST_DIR}/runtimesystem.h
  ${CMAKE_CURRENT_LIST_DIR}/typefactory.h
  interfaces/ismartcontrolvaluesender.h
  interfaces/imodulestatisticssmartsender.h
  interfaces/irendererstatussender.h
  interfaces/irendererstatusreceiver.h
  interfaces/imoduleclassreceiver.h
  interfaces/itypeclassreceiver.h
  interfaces/imoduleconstructionsmartreceiver.h
  interfaces/ismartcontrolvaluereceiver.h
  interfaces/imodulestatisticssmartreceiver.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  PREFIX ""
)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

