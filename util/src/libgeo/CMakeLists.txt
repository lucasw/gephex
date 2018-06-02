cmake_minimum_required(VERSION 2.8)
project(libgeo)


message(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR})

add_library(${PROJECT_NAME} SHARED ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.c)

# TODO(lucasw) maybe don't need all these, do need basic_types.h
include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../../../engine/src/engine
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/framebuffertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/numbertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/positiontype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/stringtype
  ${CMAKE_CURRENT_LIST_DIR}/../../../util/include
  ${CMAKE_CURRENT_LIST_DIR}/../../../util/src/libgeo
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  PREFIX ""
)

# TODO geotest.c
