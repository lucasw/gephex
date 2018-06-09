cmake_minimum_required(VERSION 2.8)
project(gui)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  find_package(Qt5Widgets REQUIRED)
else()
  find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
  include(${QT_USE_FILE})
endif()

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
include(${CMAKE_CURRENT_LIST_DIR}/dialogs/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/base/CMakeLists.txt)

link_directories(${CMAKE_CURRENT_BINARY_DIR})

set(HDRS
  ${CMAKE_CURRENT_LIST_DIR}/controlwidget.h
  ${CMAKE_CURRENT_LIST_DIR}/graphnameview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/graphnameview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/graphnameview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/graphnameview.h
  ${CMAKE_CURRENT_LIST_DIR}/hidebutton.h
  ${CMAKE_CURRENT_LIST_DIR}/inputplugwidget.h
  ${CMAKE_CURRENT_LIST_DIR}/modulebutton.h
  ${CMAKE_CURRENT_LIST_DIR}/moduleclassview.h
  ${CMAKE_CURRENT_LIST_DIR}/nodewidget.h
  ${CMAKE_CURRENT_LIST_DIR}/outputplugwidget.h
  ${CMAKE_CURRENT_LIST_DIR}/picswitch.h
  ${CMAKE_CURRENT_LIST_DIR}/plugwidget.h
  ${CMAKE_CURRENT_LIST_DIR}/propertywidget.h
  ${CMAKE_CURRENT_LIST_DIR}/typeview.h
  ${CMAKE_CURRENT_LIST_DIR}/vjmainwindow.h
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  qt5_wrap_cpp(${PROJECT_NAME}_MOCS ${HDRS})
else()
  qt4_wrap_cpp(${PROJECT_NAME}_MOCS ${HDRS})
endif()

add_executable(gephex-${PROJECT_NAME}
  ${${PROJECT_NAME}_MOCS}
  ${CMAKE_CURRENT_LIST_DIR}/connectionwidget.cpp
  ${CMAKE_CURRENT_LIST_DIR}/controlwidget.cpp
  ${CMAKE_CURRENT_LIST_DIR}/graphnameview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/hidebutton.cpp
  ${CMAKE_CURRENT_LIST_DIR}/hidebuttonconstructor.cpp
  ${CMAKE_CURRENT_LIST_DIR}/inputplugwidget.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/modulebutton.cpp
  ${CMAKE_CURRENT_LIST_DIR}/moduleclassview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/nodeproperty.cpp
  ${CMAKE_CURRENT_LIST_DIR}/nodewidget.cpp
  ${CMAKE_CURRENT_LIST_DIR}/outputplugwidget.cpp
  ${CMAKE_CURRENT_LIST_DIR}/picswitch.cpp
  ${CMAKE_CURRENT_LIST_DIR}/plugwidget.cpp
  ${CMAKE_CURRENT_LIST_DIR}/propertywidget.cpp
  ${CMAKE_CURRENT_LIST_DIR}/propertywidgetconstructor.cpp
  ${CMAKE_CURRENT_LIST_DIR}/typeview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/typeviewfactory.cpp
  ${CMAKE_CURRENT_LIST_DIR}/vjmainwindow.cpp
  ${CMAKE_CURRENT_LIST_DIR}/connectionwidget.h
  ${CMAKE_CURRENT_LIST_DIR}/controlwidget.h
  ${CMAKE_CURRENT_LIST_DIR}/graphnameview.h
  ${CMAKE_CURRENT_LIST_DIR}/hidebutton.h
  ${CMAKE_CURRENT_LIST_DIR}/hidebuttonconstructor.h
  ${CMAKE_CURRENT_LIST_DIR}/imoduleinfobasestation.h
  ${CMAKE_CURRENT_LIST_DIR}/inputplugwidget.h
  ${CMAKE_CURRENT_LIST_DIR}/modulebutton.h
  ${CMAKE_CURRENT_LIST_DIR}/moduleclassview.h
  ${CMAKE_CURRENT_LIST_DIR}/nodeproperty.h
  ${CMAKE_CURRENT_LIST_DIR}/nodewidget.h
  ${CMAKE_CURRENT_LIST_DIR}/outputplugwidget.h
  ${CMAKE_CURRENT_LIST_DIR}/picswitch.h
  ${CMAKE_CURRENT_LIST_DIR}/plugwidget.h
  ${CMAKE_CURRENT_LIST_DIR}/propertywidget.h
  ${CMAKE_CURRENT_LIST_DIR}/propertywidgetconstructor.h
  ${CMAKE_CURRENT_LIST_DIR}/typeview.h
  ${CMAKE_CURRENT_LIST_DIR}/typeviewfactory.h
  ${CMAKE_CURRENT_LIST_DIR}/vjmainwindow.h
  interfaces/imoduleclassnamesender.h
)

target_link_libraries(${PROJECT_NAME}
  dialogs
  gphxnetwork
  guibase
  guieditor
  guimodel
  netinterfaces
  typeviews
  utils
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
else()
  target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
endif()

# set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

