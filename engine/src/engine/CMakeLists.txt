cmake_minimum_required(VERSION 2.8)
project(engine)

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
  ${CMAKE_CURRENT_BINARY_DIR}/interfaces
  ${CMAKE_CURRENT_BINARY_DIR}/netinterfaces
  ${CMAKE_HOME_DIRECTORY}/base/src/interfaces
)

include(${CMAKE_HOME_DIRECTORY}/base/src/interfaces/CMakeLists.txt)

link_directories(${CMAKE_CURRENT_BINARY_DIR})

include(${CMAKE_HOME_DIRECTORY}/base/src/interfaces/CMakeLists.txt)
add_executable(${PROJECT_NAME}
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/scheduler.cpp
  ${CMAKE_CURRENT_LIST_DIR}/netlogger.cpp
  ${CMAKE_CURRENT_LIST_DIR}/netlogger.h
  ${CMAKE_CURRENT_LIST_DIR}/scheduler.h
  ${CMAKE_CURRENT_LIST_DIR}/controller.h
  ${CMAKE_CURRENT_LIST_DIR}/controller.cpp
  ${CMAKE_CURRENT_LIST_DIR}/bufferedsender.h
  ${CMAKE_CURRENT_LIST_DIR}/bufferedsender.cpp
  ${CMAKE_CURRENT_LIST_DIR}/synced_tasks.h
  netinterfaces/moduleconstructiondumbreceivernet.h
)
target_link_libraries(${PROJECT_NAME}
  dllloader
  model
  renderer
  net
  netinterfaces
  utils
)

# set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

