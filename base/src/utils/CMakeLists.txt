cmake_minimum_required(VERSION 2.8)
project(utils)

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
  ${CMAKE_BINARY_DIR}
)

include(${CMAKE_HOME_DIRECTORY}/base/src/interfaces/interfaces.cmake)

link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(${PROJECT_NAME} STATIC
  ${CMAKE_CURRENT_LIST_DIR}/buffer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/bufferstream.cpp
  ${CMAKE_CURRENT_LIST_DIR}/bufferutils.cpp
  ${CMAKE_CURRENT_LIST_DIR}/circularbuffer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/configfile.cpp
  ${CMAKE_CURRENT_LIST_DIR}/configmanager.cpp
  ${CMAKE_CURRENT_LIST_DIR}/filesystem.cpp
  ${CMAKE_CURRENT_LIST_DIR}/itokenizer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/sharedlibrary.cpp
  ${CMAKE_CURRENT_LIST_DIR}/spawn.cpp
  ${CMAKE_CURRENT_LIST_DIR}/streamlogger.cpp
  ${CMAKE_CURRENT_LIST_DIR}/streamtokenizer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/string_.cpp
  ${CMAKE_CURRENT_LIST_DIR}/stringtokenizer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/structreader.cpp
  ${CMAKE_CURRENT_LIST_DIR}/structscanner.cpp
  ${CMAKE_CURRENT_LIST_DIR}/timing.cpp
  ${CMAKE_CURRENT_LIST_DIR}/xmlutils.cpp
  ${CMAKE_CURRENT_LIST_DIR}/autoptr.h
  ${CMAKE_CURRENT_LIST_DIR}/block.h
  ${CMAKE_CURRENT_LIST_DIR}/buffer.h
  ${CMAKE_CURRENT_LIST_DIR}/bufferstream.h
  ${CMAKE_CURRENT_LIST_DIR}/bufferutils.h
  ${CMAKE_CURRENT_LIST_DIR}/circularbuffer.h
  ${CMAKE_CURRENT_LIST_DIR}/configfile.h
  ${CMAKE_CURRENT_LIST_DIR}/configmanager.h
  ${CMAKE_CURRENT_LIST_DIR}/filesystem.h
  ${CMAKE_CURRENT_LIST_DIR}/ilogger.h
  ${CMAKE_CURRENT_LIST_DIR}/istructtokenlistener.h
  ${CMAKE_CURRENT_LIST_DIR}/itokenizer.h
  ${CMAKE_CURRENT_LIST_DIR}/sharedlibrary.h
  ${CMAKE_CURRENT_LIST_DIR}/spawn.h
  ${CMAKE_CURRENT_LIST_DIR}/streamlogger.h
  ${CMAKE_CURRENT_LIST_DIR}/streamtokenizer.h
  ${CMAKE_CURRENT_LIST_DIR}/string_.h
  ${CMAKE_CURRENT_LIST_DIR}/stringtokenizer.h
  ${CMAKE_CURRENT_LIST_DIR}/structreader.h
  ${CMAKE_CURRENT_LIST_DIR}/structscanner.h
  ${CMAKE_CURRENT_LIST_DIR}/timing.h
  ${CMAKE_CURRENT_LIST_DIR}/xmlutils.h
)

# TODO(lucasw) only link this if HAVE_DLFCN
target_link_libraries(${PROJECT_NAME} dl)

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

