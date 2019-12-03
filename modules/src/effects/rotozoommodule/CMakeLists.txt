cmake_minimum_required(VERSION 2.8)
project(rotozoommodule)

# generate the .h and _auto.c files from the spec
include(${CMAKE_HOME_DIRECTORY}/modules/pluc.cmake)

include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_HOME_DIRECTORY}/engine/src/engine
  ${CMAKE_HOME_DIRECTORY}/types/src/framebuffertype
  ${CMAKE_HOME_DIRECTORY}/types/src/numbertype
  ${CMAKE_HOME_DIRECTORY}/types/src/positiontype
  ${CMAKE_HOME_DIRECTORY}/types/src/stringtype
  ${CMAKE_HOME_DIRECTORY}/util/include
  ${CMAKE_HOME_DIRECTORY}/util/src/libgeo
)

# is this needed?  Does something that fPIC now does?
# add_definitions(-DPIC)
# target_compile_definitions(${PROJECT_NAME} -DPIC)
# -Wl, -soname?
# set(CMAKE_SHARED_LIBRARY_PREFIX "blah")
# message("binary dir: " ${CMAKE_CURRENT_BINARY_DIR})
link_directories(${CMAKE_BINARY_DIR}
  ${CMAKE_BINARY_DIR}/util/src/libgeo  # TODO(lucasw) should this get pulled in below?
)
add_library(${PROJECT_NAME} MODULE
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.c
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.xpm
  ${PROJECT_NAME}.h
  ${PROJECT_NAME}_auto.c
)
add_dependencies(${PROJECT_NAME} libgeo)
target_link_libraries(${PROJECT_NAME} geo)
# set(NO_SONAME ON)
# Is there a target_link_definitions?
# target_compile_definitions(${PROJECT_NAME} PRIVATE PIC)
set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
#    NO_SONAME True   # Doesn't work - but is it even needed?
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/modules
  PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
