cmake_minimum_required(VERSION 2.8)
project(libgeo)

include_directories(${CMAKE_CURRENT_LIST_DIR})

# TODO(lucasw) is there a static vs shared speed difference?
# add_library(${PROJECT_NAME} SHARED ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.c)
add_library(${PROJECT_NAME} STATIC ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.c)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# TODO(lucasw) maybe don't need all these, do need basic_types.h
include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../../../engine/src/engine
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/framebuffertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/numbertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/positiontype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/stringtype
  ${CMAKE_CURRENT_LIST_DIR}/../../../util/include
)

link_directories(${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
  PREFIX ""
)

# TODO geotest.c
