cmake_minimum_required(VERSION 2.8)
project(gphxnetwork)

include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_BINARY_DIR}
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
  ${CMAKE_HOME_DIRECTORY}/util/include
)

include(${CMAKE_HOME_DIRECTORY}/base/src/interfaces/interfaces.cmake)

link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(${PROJECT_NAME} STATIC
  # TODO(lucasw) unix only
  ${CMAKE_CURRENT_LIST_DIR}/domainserversocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/domainclientsocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/domainserversocket.h
  ${CMAKE_CURRENT_LIST_DIR}/domainclientsocket.h
  #
  ${CMAKE_CURRENT_LIST_DIR}/netexceptions.cpp
  ${CMAKE_CURRENT_LIST_DIR}/protocol.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tagutils.cpp
  ${CMAKE_CURRENT_LIST_DIR}/isocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/sotimeout.cpp
  ${CMAKE_CURRENT_LIST_DIR}/socketutils.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tcpserversocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tcpclientsocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/fdsocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/socketadaptor.cpp
  ${CMAKE_CURRENT_LIST_DIR}/convertbin.cpp
  ${CMAKE_CURRENT_LIST_DIR}/protocol.h
  ${CMAKE_CURRENT_LIST_DIR}/idatalistener.h
  ${CMAKE_CURRENT_LIST_DIR}/isender.h
  ${CMAKE_CURRENT_LIST_DIR}/netexceptions.h
  ${CMAKE_CURRENT_LIST_DIR}/itagger.h
  ${CMAKE_CURRENT_LIST_DIR}/itaginterpreter.h
  ${CMAKE_CURRENT_LIST_DIR}/tagger.h
  # ${CMAKE_CURRENT_LIST_DIR}/tagger.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tagutils.h
  ${CMAKE_CURRENT_LIST_DIR}/isocket.h
  ${CMAKE_CURRENT_LIST_DIR}/socketutils.h
  ${CMAKE_CURRENT_LIST_DIR}/sotimeout.h
  ${CMAKE_CURRENT_LIST_DIR}/iclientsocket.h
  ${CMAKE_CURRENT_LIST_DIR}/iserversocket.h
  ${CMAKE_CURRENT_LIST_DIR}/tcpclientsocket.h
  ${CMAKE_CURRENT_LIST_DIR}/tcpserversocket.h
  ${CMAKE_CURRENT_LIST_DIR}/fdsocket.h
  ${CMAKE_CURRENT_LIST_DIR}/socketadaptor.h
  ${CMAKE_CURRENT_LIST_DIR}/tagdispatcher.h
  # ${CMAKE_CURRENT_LIST_DIR}/tagdispatcher.cpp
  ${CMAKE_CURRENT_LIST_DIR}/protocoltest.h
  ${CMAKE_CURRENT_LIST_DIR}/tcpsockettest.h
  ${CMAKE_CURRENT_LIST_DIR}/tagdispatchertest.h
  # ${CMAKE_CURRENT_LIST_DIR}/taggertest.h
  ${CMAKE_CURRENT_LIST_DIR}/domainsockettest.h
  ${CMAKE_CURRENT_LIST_DIR}/convertbin.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  PREFIX ""
)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

