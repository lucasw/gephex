cmake_minimum_required(VERSION 2.8)
project(framebuffertype)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_library(${PROJECT_NAME} SHARED
  ${PROJECT_NAME}.c
  ${PROJECT_NAME}.h
)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# TODO(lucasw) maybe don't need all these, do need basic_types.h
include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_HOME_DIRECTORY}/engine/src/engine
  ${CMAKE_HOME_DIRECTORY}/util/include
)

link_directories(${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
  PREFIX ""
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/types
  PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
