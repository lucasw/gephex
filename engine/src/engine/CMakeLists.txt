cmake_minimum_required(VERSION 2.8)
project(gephex-engine)

include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_BINARY_DIR}
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
  ${CMAKE_HOME_DIRECTORY}/base/src/interfaces
  ${CMAKE_HOME_DIRECTORY}/base/src/net
  ${CMAKE_HOME_DIRECTORY}/base/src/utils
  ${CMAKE_HOME_DIRECTORY}/util/include
)

include(${CMAKE_HOME_DIRECTORY}/base/src/netinterfaces/interfaces.cmake)

link_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/scheduler.cpp
  ${CMAKE_CURRENT_LIST_DIR}/netlogger.cpp
  ${CMAKE_CURRENT_LIST_DIR}/netlogger.h
  ${CMAKE_CURRENT_LIST_DIR}/scheduler.h
  ${CMAKE_CURRENT_LIST_DIR}/controller.h
  ${CMAKE_CURRENT_LIST_DIR}/controller.cpp
  ${CMAKE_CURRENT_LIST_DIR}/bufferedsender.h
  ${CMAKE_CURRENT_LIST_DIR}/bufferedsender.cpp
  ${CMAKE_CURRENT_LIST_DIR}/synced_tasks.h
  interfaces/ienginecontrolreceiver.h
  interfaces/imoduleconstructiondumbsender.h
  interfaces/imoduleclassspecreceiver.h
  interfaces/igraphnamesender.h
  interfaces/imodelcontrolreceiver.h
  interfaces/imoduleconstructionsmartsender.h
  interfaces/imoduledatasender.h
  interfaces/igraphdatasender.h
  interfaces/iserializedgraphsender.h
  interfaces/ismartcontrolvaluereceiver.h
  interfaces/icontrolvaluesender.h
  interfaces/imodulestatisticssender.h
  interfaces/imodulestatisticssmartreceiver.h
  interfaces/imodelstatussender.h
  interfaces/irenderercontrolreceiver.h
  interfaces/imoduleclassreceiver.h
  interfaces/itypeclassreceiver.h
  interfaces/imoduleconstructionsmartreceiver.h
  interfaces/ismartcontrolvaluesender.h
  interfaces/imodulestatisticssmartsender.h
  interfaces/irendererstatussender.h
  interfaces/imoduleclassinfosender.h
  interfaces/imoduleclasssender.h
  interfaces/imoduleclassspecsender.h
  interfaces/itypeclasssender.h
  netinterfaces/controlvaluereceivernet.h
  netinterfaces/errorreceivernet.h
  netinterfaces/graphdatareceivernet.h
  netinterfaces/graphnamereceivernet.h
  netinterfaces/modelcontrolsendernet.h
  netinterfaces/modelstatusreceivernet.h
  netinterfaces/moduleclassinforeceivernet.h
  netinterfaces/moduleconstructiondumbreceivernet.h
  netinterfaces/moduledatareceivernet.h
  netinterfaces/modulestatisticsreceivernet.h
  netinterfaces/rendererstatusreceivernet.h
  netinterfaces/renderercontrolsendernet.h
  netinterfaces/enginecontrolsendernet.h
)
target_link_libraries(${PROJECT_NAME}
  dllloader
  model
  renderer
  gphxnetwork
  netinterfaces
  utils
)

# set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  # PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
  RENAME ${PROJECT_NAME}-real
)

# install(CODE "execute_process( \
#     COMMAND ${CMAKE_COMMAND} -E create_symlink \
#     ${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}-real \
#     ${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME} \
#     )"
# )
