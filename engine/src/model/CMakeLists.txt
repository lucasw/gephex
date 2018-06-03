cmake_minimum_required(VERSION 2.8)
project(model)

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
)

include(${CMAKE_HOME_DIRECTORY}/base/src/interfaces/CMakeLists.txt)

link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(${PROJECT_NAME} STATIC
  ${CMAKE_CURRENT_LIST_DIR}/model.cpp
  ${CMAKE_CURRENT_LIST_DIR}/model.h
  ${CMAKE_CURRENT_LIST_DIR}/graph.cpp
  ${CMAKE_CURRENT_LIST_DIR}/graphnode.cpp
  ${CMAKE_CURRENT_LIST_DIR}/graphconnection.cpp
  ${CMAKE_CURRENT_LIST_DIR}/controlvalueset.cpp
  ${CMAKE_CURRENT_LIST_DIR}/graphfilesystem.cpp
  ${CMAKE_CURRENT_LIST_DIR}/graphserial.cpp
  ${CMAKE_CURRENT_LIST_DIR}/graphparser.cpp
  ${CMAKE_CURRENT_LIST_DIR}/controlvalueset.h
  ${CMAKE_CURRENT_LIST_DIR}/graphconnection.h
  ${CMAKE_CURRENT_LIST_DIR}/graphfilesystem.h
  ${CMAKE_CURRENT_LIST_DIR}/graph.h
  ${CMAKE_CURRENT_LIST_DIR}/graphnode.h
  ${CMAKE_CURRENT_LIST_DIR}/graphserial.h
  ${CMAKE_CURRENT_LIST_DIR}/specmap.h
  ${CMAKE_CURRENT_LIST_DIR}/graphparser.h
  interfaces/imoduleconstructiondumbsender.h
  interfaces/igraphnamesender.h
  interfaces/imodelcontrolreceiver.h
  interfaces/imoduleconstructionsmartsender.h
  interfaces/imoduledatasender.h
  interfaces/igraphdatasender.h
  interfaces/iserializedgraphsender.h
  interfaces/ismartcontrolvaluereceiver.h
  interfaces/icontrolvaluesender.h
  interfaces/irenderercontrolsender.h
  interfaces/imodulestatisticssender.h
  interfaces/imodulestatisticssmartreceiver.h
  interfaces/imodelstatussender.h
  interfaces/igraphnamereceiver.h
  interfaces/imoduleconstructionsmartreceiver.h
  interfaces/imoduleconstructiondumbreceiver.h
  interfaces/imoduledatareceiver.h
  interfaces/igraphdatareceiver.h
  interfaces/iserializedgraphreceiver.h
  interfaces/irenderercontrolreceiver.h
  interfaces/icontrolvaluereceiver.h
  interfaces/imodulestatisticsreceiver.h
  interfaces/imodelstatusreceiver.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  PREFIX ""
)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

