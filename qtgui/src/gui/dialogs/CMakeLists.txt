cmake_minimum_required(VERSION 2.8)
project(dialogs)

find_package(Qt5Widgets REQUIRED)

message(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../..
  ${CMAKE_HOME_DIRECTORY}/base/src
  ${CMAKE_HOME_DIRECTORY}/util/include
)

set(UIS
  ${CMAKE_CURRENT_LIST_DIR}/aboutdialog.ui
  ${CMAKE_CURRENT_LIST_DIR}/changesdialog.ui
)

qt5_wrap_ui(${PROJECT_NAME}_UIS ${UIS})

link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(${PROJECT_NAME} STATIC
  ${CMAKE_CURRENT_LIST_DIR}/aboutdialog.cpp
  ${CMAKE_CURRENT_LIST_DIR}/aboutdialog.h
  ${CMAKE_CURRENT_LIST_DIR}/changesdialog.cpp
  ${CMAKE_CURRENT_LIST_DIR}/changesdialog.h
  ${CMAKE_CURRENT_LIST_DIR}/newgraphdialog.cpp
  ${CMAKE_CURRENT_LIST_DIR}/newgraphdialog.h
  ${${PROJECT_NAME}_UIS}
)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

# add_dependencies(${PROJECT_NAME}
# )

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# install(TARGETS ${PROJECT_NAME}
#   DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/modules
#   PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
# )
