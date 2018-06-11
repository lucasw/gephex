cmake_minimum_required(VERSION 2.8)
project(guieditor)

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
  ${CMAKE_CURRENT_LIST_DIR}/controleditor.h
  ${CMAKE_CURRENT_LIST_DIR}/editorwidget.h
  ${CMAKE_CURRENT_LIST_DIR}/grapheditor.h
  ${CMAKE_CURRENT_LIST_DIR}/labelwidget.h
  ${CMAKE_CURRENT_LIST_DIR}/mouseover.h
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  qt5_wrap_cpp(${PROJECT_NAME}_MOCS ${HDRS})
else()
  qt4_wrap_cpp(${PROJECT_NAME}_MOCS ${HDRS})
endif()

include(${CMAKE_HOME_DIRECTORY}/base/src/interfaces/interfaces.cmake)

# link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(${PROJECT_NAME} STATIC
  controleditor.cpp
  editorwidget.cpp
  grapheditor.cpp
  controleditorwindow.cpp
  grapheditorwindow.cpp
  labelwidget.cpp
  mouseover.cpp
  controleditor.h
  grapheditor.h
  ieditorcommandlistener.h
  editorwidget.h
  ieditor.h
  ivisibleelement.h
  controleditorwindow.h
  grapheditorwindow.h
  labelwidget.h
  mouseover.h
  ${${PROJECT_NAME}_MOCS}
  interfaces/imodelcontrolreceiver.h
  interfaces/imoduledatareceiver.h
  interfaces/igraphdatareceiver.h
  interfaces/icontrolvaluereceiver.h
  interfaces/imodulestatisticsreceiver.h
  interfaces/imodelstatusreceiver.h
  interfaces/imoduleconstructiondumbreceiver.h
  interfaces/imodulestatisticssender.h
  interfaces/imodelstatussender.h
  interfaces/ierrorreceiver.h
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
