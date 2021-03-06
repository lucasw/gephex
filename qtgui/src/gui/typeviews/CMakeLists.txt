cmake_minimum_required(VERSION 2.8)
project(typeviews)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  find_package(Qt5Widgets REQUIRED)
else()
  find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
  include(${QT_USE_FILE})
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../..
  ${CMAKE_HOME_DIRECTORY}/base/src
  ${CMAKE_HOME_DIRECTORY}/util/include
)

set(HDRS
  ${CMAKE_CURRENT_LIST_DIR}/boundednumberview.h
  ${CMAKE_CURRENT_LIST_DIR}/checkboxnumberview.h
  ${CMAKE_CURRENT_LIST_DIR}/colorview.h
  ${CMAKE_CURRENT_LIST_DIR}/comboboxstringview.h
  ${CMAKE_CURRENT_LIST_DIR}/filestringview.h
  ${CMAKE_CURRENT_LIST_DIR}/fontview.h
  ${CMAKE_CURRENT_LIST_DIR}/frameview.h
  ${CMAKE_CURRENT_LIST_DIR}/positionview.h
  ${CMAKE_CURRENT_LIST_DIR}/positionview.h
  ${CMAKE_CURRENT_LIST_DIR}/radionumberview.h
  ${CMAKE_CURRENT_LIST_DIR}/slidernumberview.h
  ${CMAKE_CURRENT_LIST_DIR}/stringview.h
  ${CMAKE_CURRENT_LIST_DIR}/unboundednumberview.h
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  qt5_wrap_cpp(${PROJECT_NAME}_MOCS ${HDRS})
else()
  qt4_wrap_cpp(${PROJECT_NAME}_MOCS ${HDRS})
endif()

include(${CMAKE_HOME_DIRECTORY}/base/src/interfaces/interfaces.cmake)

# link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(${PROJECT_NAME} STATIC
  ${CMAKE_CURRENT_LIST_DIR}/boundednumberview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/boundednumberview.h
  ${CMAKE_CURRENT_LIST_DIR}/checkboxnumberview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/checkboxnumberview.h
  ${CMAKE_CURRENT_LIST_DIR}/colorview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/colorview.h
  ${CMAKE_CURRENT_LIST_DIR}/comboboxstringview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/comboboxstringview.h
  ${CMAKE_CURRENT_LIST_DIR}/filestringview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/filestringview.h
  ${CMAKE_CURRENT_LIST_DIR}/fontview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/fontview.h
  ${CMAKE_CURRENT_LIST_DIR}/frameview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/frameview.h
  ${CMAKE_CURRENT_LIST_DIR}/positionview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/positionview.h
  ${CMAKE_CURRENT_LIST_DIR}/radionumberview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/radionumberview.h
  ${CMAKE_CURRENT_LIST_DIR}/slidernumberview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/slidernumberview.h
  ${CMAKE_CURRENT_LIST_DIR}/stringview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/stringview.h
  ${CMAKE_CURRENT_LIST_DIR}/unboundednumberview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/unboundednumberview.h
  ${${PROJECT_NAME}_MOCS}
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
else()
  target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
endif()


# add_dependencies(${PROJECT_NAME}
# )

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# install(TARGETS ${PROJECT_NAME}
#   DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/modules
#   PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
# )
