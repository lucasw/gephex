cmake_minimum_required(VERSION 2.8)
project(gephex-gui)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  find_package(Qt5Widgets REQUIRED)
else()
  find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
  include(${QT_USE_FILE})
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/dialogs
  ${CMAKE_CURRENT_LIST_DIR}/../../../base/src
  ${CMAKE_CURRENT_LIST_DIR}/../../../engine/src/engine
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/framebuffertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/numbertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/positiontype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/stringtype
  ${CMAKE_CURRENT_LIST_DIR}/../../../util/src/libgeo
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_HOME_DIRECTORY}/base/src/interfaces
  ${CMAKE_HOME_DIRECTORY}/util/include
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/dialogs)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/editor)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/base)  # guibase
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/typeviews)  # guibase

include(${CMAKE_HOME_DIRECTORY}/base/src/interfaces/interfaces.cmake)

link_directories(${CMAKE_CURRENT_BINARY_DIR})

set(HDRS
  ${CMAKE_CURRENT_LIST_DIR}/controlwidget.h
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

add_executable(${PROJECT_NAME}
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
  interfaces/icontrolvaluereceiver.h
  interfaces/igraphnamereceiver.h
  interfaces/irendererstatusreceiver.h
  interfaces/imodelcontrolreceiver.h
  interfaces/ierrorreceiver.h
  interfaces/ienginecontrolreceiver.h
  interfaces/irenderercontrolreceiver.h
  interfaces/igraphnamesender.h
  interfaces/ierrorsender.h
  interfaces/irendererstatussender.h
  interfaces/imoduleclassinforeceiver.h
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

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  # PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
  RENAME ${PROJECT_NAME}-real
)

install(CODE "execute_process( \
	COMMAND ${CMAKE_COMMAND} -E create_symlink \
	${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}-real \
	${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME} \
	)"
)

