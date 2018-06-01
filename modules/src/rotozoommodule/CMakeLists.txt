cmake_minimum_required(VERSION 2.8)
project(rotozoommodule)

# Need to run these commands:
# python ../../../../gephex/modules/src/rotozoommodule/../../pluc.py h ../../../../gephex/modules/src/rotozoommodule/rotozoommodule.spec
add_custom_command(OUTPUT ${PROJECT_NAME}.h
    COMMAND python ${CMAKE_CURRENT_LIST_DIR}/../../pluc.py h ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.spec
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.spec
    COMMENT "generating ${PROJECT_NAME} header"
)

add_custom_command(OUTPUT ${PROJECT_NAME}_auto.c
    COMMAND python ${CMAKE_CURRENT_LIST_DIR}/../../pluc.py c ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.spec
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.spec
    COMMENT "generating ${PROJECT_NAME} header"
)

# python ../../../../gephex/modules/src/rotozoommodule/../../pluc.py c ../../../../gephex/modules/src/rotozoommodule/rotozoommodule.spec

include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../../../engine/src/engine
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/framebuffertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/numbertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/positiontype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/stringtype
  ${CMAKE_CURRENT_LIST_DIR}/../../../util/include
  ${CMAKE_CURRENT_LIST_DIR}/../../../util/src/libgeo
)

# is this needed?  Does something that fPIC now does?
# add_definitions(-DPIC)
# target_compile_definitions(${PROJECT_NAME} -DPIC)
# -Wl, -soname?
# set(NO_SONAME ON)
# set(CMAKE_SHARED_LIBRARY_PREFIX "blah")
add_library(${PROJECT_NAME} MODULE ${PROJECT_NAME}.c ${PROJECT_NAME}.h ${PROJECT_NAME}_auto.c)
set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
)
#    LINK_FLAGS -soname
