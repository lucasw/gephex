cmake_minimum_required(VERSION 2.8)
project(frbinmodule)

find_package(SDL)
find_package(SDL_image)

include(${CMAKE_HOME_DIRECTORY}/modules/pluc.cmake)

include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../../../engine/src/engine
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/framebuffertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/numbertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/positiontype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/stringtype
  ${CMAKE_CURRENT_LIST_DIR}/../../../util/include
  ${CMAKE_CURRENT_LIST_DIR}/../../../util/src/libgeo
  ${CMAKE_CURRENT_LIST_DIR}/../libscale
  ${SDL_INCLUDE_DIR}
)

link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(${PROJECT_NAME} MODULE
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.xpm
  # ${CMAKE_CURRENT_LIST_DIR}/avifiledriver.cpp
  ${CMAKE_CURRENT_LIST_DIR}/bmpdriver.cpp
  # ${CMAKE_CURRENT_LIST_DIR}/ffmpegdriver.cpp
  ${CMAKE_CURRENT_LIST_DIR}/framecache.cpp
  # ${CMAKE_CURRENT_LIST_DIR}/mpeg3driver.cpp
  ${PROJECT_NAME}.h
  ${PROJECT_NAME}_auto.c
)

# windows
  # ${CMAKE_CURRENT_LIST_DIR}/timer.cpp
  # ${CMAKE_CURRENT_LIST_DIR}/dshowdriver.cpp
  # ${CMAKE_CURRENT_LIST_DIR}/vfwdriver.cpp

# TODO(lwalter) need to trigger the cmake file
target_link_libraries(${PROJECT_NAME} scale)

if(${SDL_IMAGE_FOUND})
  # target_sources(${PROJECT_NAME} PRIVATE
  #   ${CMAKE_CURRENT_LIST_DIR}/sdlimagedriver.cpp)
  target_link_libraries(${PROJECT_NAME} ${SDL_IMAGE_LIBRARIES})
endif(${SDL_IMAGE_FOUND})

if(SDL_FOUND)
  target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/sdlimagedriver.cpp)
  target_link_libraries(${PROJECT_NAME} ${SDL_LIBRARY})
endif(SDL_FOUND)

# target_link_libraries(${PROJECT_NAME} geo)
set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/modules
  PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
