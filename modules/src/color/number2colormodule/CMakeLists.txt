cmake_minimum_required(VERSION 2.8)
project(number2colormodule)

# generate the .h and _auto.c files from the spec
include(${CMAKE_HOME_DIRECTORY}/modules/pluc.cmake)

include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_HOME_DIRECTORY}/engine/src/engine
  ${CMAKE_HOME_DIRECTORY}/types/src/rgbtype
  ${CMAKE_HOME_DIRECTORY}/types/src/framebuffertype
  ${CMAKE_HOME_DIRECTORY}/types/src/numbertype
  ${CMAKE_HOME_DIRECTORY}/types/src/positiontype
  ${CMAKE_HOME_DIRECTORY}/types/src/stringtype
  ${CMAKE_HOME_DIRECTORY}/util/include
  ${CMAKE_HOME_DIRECTORY}/util/src/misc
)

add_library(${PROJECT_NAME} MODULE
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.c
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.xpm
  ${PROJECT_NAME}.h
  ${PROJECT_NAME}_auto.c
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  PREFIX ""
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/modules
  PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
