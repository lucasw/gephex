cmake_minimum_required(VERSION 2.8)
project(frboutmodule)

find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)
find_package(SDL)
# TODO(lucasw) required if SDL is used?
find_package(SDL_image)

# TODO(lucasw) move these to higher lever cmake file
add_custom_command(OUTPUT ${PROJECT_NAME}.h
    COMMAND python ${CMAKE_SOURCE_DIR}/modules/pluc.py h ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.spec
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.spec
    COMMENT "generating ${PROJECT_NAME} header"
)

add_custom_command(OUTPUT ${PROJECT_NAME}_auto.c
    COMMAND python ${CMAKE_SOURCE_DIR}/modules/pluc.py c ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.spec
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.spec
    COMMENT "generating ${PROJECT_NAME} header"
)

include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/engine/src/engine
  ${CMAKE_SOURCE_DIR}/types/src/framebuffertype
  ${CMAKE_SOURCE_DIR}/types/src/numbertype
  ${CMAKE_SOURCE_DIR}/types/src/positiontype
  ${CMAKE_SOURCE_DIR}/types/src/stringtype
  ${CMAKE_SOURCE_DIR}/util/include
  ${CMAKE_SOURCE_DIR}/util/src/libgeo
  ${CMAKE_CURRENT_LIST_DIR}/../../libscale
  ${CMAKE_CURRENT_LIST_DIR}/../../libcolorconv
  ${SDL_INCLUDE_DIR}
)

link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(${PROJECT_NAME} MODULE
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.c
  # ${CMAKE_CURRENT_LIST_DIR}/aaoutput.c
  ${CMAKE_CURRENT_LIST_DIR}/gloutput.cpp
  ${CMAKE_CURRENT_LIST_DIR}/glxutil.c
  ${CMAKE_CURRENT_LIST_DIR}/sdloutput.c
  ${CMAKE_CURRENT_LIST_DIR}/slist.c
  ${CMAKE_CURRENT_LIST_DIR}/vloopbackoutput.c
  ${CMAKE_CURRENT_LIST_DIR}/x11output.c
  ${CMAKE_CURRENT_LIST_DIR}/x11stuff.c
  ${PROJECT_NAME}.h
  ${PROJECT_NAME}_auto.c
)

# windows
  # ${CMAKE_CURRENT_LIST_DIR}/dxoutput.c
  # ${CMAKE_CURRENT_LIST_DIR}/multimonitor.c
  # ${CMAKE_CURRENT_LIST_DIR}/wglutil.c
# mac?
  # ${CMAKE_CURRENT_LIST_DIR}/quartzoutput.c

target_link_libraries(${PROJECT_NAME} scale colorconv)

# TODO(lwalter) maybe these can be made optional
# TODO(lwalter) not sure what to bring Xv in with
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} Xv)
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})

if(${SDL_IMAGE_FOUND})
  # target_sources(${PROJECT_NAME} PRIVATE
  #   ${CMAKE_CURRENT_LIST_DIR}/sdlimagedriver.cpp)
  target_link_libraries(${PROJECT_NAME} ${SDL_IMAGE_LIBRARIES})
endif(${SDL_IMAGE_FOUND})

if(${SDL_FOUND})
  # target_sources(${PROJECT_NAME} PRIVATE
  #   ${CMAKE_CURRENT_LIST_DIR}/sdlimagedriver.cpp)
  target_link_libraries(${PROJECT_NAME} ${SDL_LIBRARY})
endif(${SDL_FOUND})

# target_link_libraries(${PROJECT_NAME} geo)
set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/modules
  PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
