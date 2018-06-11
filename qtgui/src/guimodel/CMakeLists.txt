cmake_minimum_required(VERSION 2.8)
project(guimodel)

include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_HOME_DIRECTORY}/base/src
  ${CMAKE_HOME_DIRECTORY}/util/include
  ${SDL_INCLUDE_DIR}
)

message(${CMAKE_CURRENT_BINARY_DIR}/../../..)

include(${CMAKE_HOME_DIRECTORY}/base/src/netinterfaces/interfaces.cmake)

link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(${PROJECT_NAME} STATIC
  ${CMAKE_CURRENT_LIST_DIR}/controlmodel.cpp
  ${CMAKE_CURRENT_LIST_DIR}/moduleinfo.cpp
  ${CMAKE_CURRENT_LIST_DIR}/moduleclassmodel.cpp
  ${CMAKE_CURRENT_LIST_DIR}/point.cpp
  ${CMAKE_CURRENT_LIST_DIR}/graphmodel.cpp
  ${CMAKE_CURRENT_LIST_DIR}/xpm.cpp
  ${CMAKE_CURRENT_LIST_DIR}/controlvaluedispatcher.cpp
  ${CMAKE_CURRENT_LIST_DIR}/moduledatadispatcher.cpp
  ${CMAKE_CURRENT_LIST_DIR}/enginewrapper.cpp
  ${CMAKE_CURRENT_LIST_DIR}/controlmodel.h
  ${CMAKE_CURRENT_LIST_DIR}/controlvaluedispatcher.h
  ${CMAKE_CURRENT_LIST_DIR}/enginewrapper.h
  ${CMAKE_CURRENT_LIST_DIR}/graphmodel.h
  ${CMAKE_CURRENT_LIST_DIR}/icontrolconnectview.h
  ${CMAKE_CURRENT_LIST_DIR}/icontrolview.h
  ${CMAKE_CURRENT_LIST_DIR}/igraphview.h
  ${CMAKE_CURRENT_LIST_DIR}/imoduleclassview.h
  ${CMAKE_CURRENT_LIST_DIR}/moduleclassmodel.h
  ${CMAKE_CURRENT_LIST_DIR}/moduledatadispatcher.h
  ${CMAKE_CURRENT_LIST_DIR}/moduleinfo.h
  ${CMAKE_CURRENT_LIST_DIR}/pluginfo.h
  ${CMAKE_CURRENT_LIST_DIR}/point.h
  ${CMAKE_CURRENT_LIST_DIR}/xpm.h
  interfaces/imoduledatareceiver.h
  interfaces/igraphdatareceiver.h
  interfaces/imodelcontrolreceiver.h
  interfaces/ierrorreceiver.h
  interfaces/imoduleclassinforeceiver.h
  interfaces/imoduleconstructiondumbreceiver.h
  interfaces/icontrolvaluereceiver.h
  netinterfaces/controlvaluesendernet.h
  netinterfaces/modulestatisticssendernet.h
  netinterfaces/moduleclassinfosendernet.h
  netinterfaces/moduledatasendernet.h
  netinterfaces/graphdatasendernet.h
  netinterfaces/moduleconstructiondumbsendernet.h
  netinterfaces/graphnamesendernet.h
  netinterfaces/rendererstatussendernet.h
  netinterfaces/errorsendernet.h
  netinterfaces/modelstatussendernet.h
  netinterfaces/modelcontrolreceivernet.h
  netinterfaces/renderercontrolreceivernet.h
  netinterfaces/enginecontrolreceivernet.h
)

target_link_libraries(${PROJECT_NAME}
  gphxnetwork
)

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# install(TARGETS ${PROJECT_NAME}
#   DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/modules
#   PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
# )
