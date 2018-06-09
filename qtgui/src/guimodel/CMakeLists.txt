cmake_minimum_required(VERSION 2.8)
project(guimodel)

include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_HOME_DIRECTORY}/base/src
  ${CMAKE_HOME_DIRECTORY}/util/include
  ${SDL_INCLUDE_DIR}
)

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
)

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# install(TARGETS ${PROJECT_NAME}
#   DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/modules
#   PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
# )
