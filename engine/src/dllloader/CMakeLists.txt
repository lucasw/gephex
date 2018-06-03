cmake_minimum_required(VERSION 2.8)
project(dllloader)

include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../../../base/src
  ${CMAKE_CURRENT_LIST_DIR}/../../../engine/src/engine
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/framebuffertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/numbertype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/positiontype
  ${CMAKE_CURRENT_LIST_DIR}/../../../types/src/stringtype
  ${CMAKE_CURRENT_LIST_DIR}/../../../util/include
  ${CMAKE_CURRENT_LIST_DIR}/../../../util/src/libgeo
  ${CMAKE_CURRENT_LIST_DIR}/../libscale
  ${CMAKE_CURRENT_LIST_DIR}/../libcolorconv
  ${CMAKE_CURRENT_BINARY_DIR}
)

include(${CMAKE_HOME_DIRECTORY}/base/src/interfaces/CMakeLists.txt)

link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(${PROJECT_NAME} STATIC
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.cpp
  ${CMAKE_CURRENT_LIST_DIR}/gephex_type_plugin.cpp
  ${CMAKE_CURRENT_LIST_DIR}/gephex_module_class.cpp
  ${CMAKE_CURRENT_LIST_DIR}/gephex_module_plugin.cpp
  ${CMAKE_CURRENT_LIST_DIR}/gephex_module_plugin.h
  ${CMAKE_CURRENT_LIST_DIR}/frei0r_module_class.cpp
  ${CMAKE_CURRENT_LIST_DIR}/dllloader.cpp
  ${CMAKE_CURRENT_LIST_DIR}/nameresolver.cpp
  ${CMAKE_CURRENT_LIST_DIR}/gephex_module.cpp
  ${CMAKE_CURRENT_LIST_DIR}/frei0r_module.cpp
  ${CMAKE_CURRENT_LIST_DIR}/frei0r_module.h
  ${CMAKE_CURRENT_LIST_DIR}/c_input.cpp
  ${CMAKE_CURRENT_LIST_DIR}/c_output.cpp
  ${CMAKE_CURRENT_LIST_DIR}/c_typeclass.cpp
  ${CMAKE_CURRENT_LIST_DIR}/moduleclassspec.cpp
  ${CMAKE_CURRENT_LIST_DIR}/c_outputplug.cpp
  ${CMAKE_CURRENT_LIST_DIR}/c_type.cpp
  ${CMAKE_CURRENT_LIST_DIR}/moduleinfoutils.cpp
  ${CMAKE_CURRENT_LIST_DIR}/gephex_type_plugin.h
  ${CMAKE_CURRENT_LIST_DIR}/c_functiontypes.h
  ${CMAKE_CURRENT_LIST_DIR}/c_input.h
  ${CMAKE_CURRENT_LIST_DIR}/gephex_module_class.h
  ${CMAKE_CURRENT_LIST_DIR}/frei0r_module_class.h
  ${CMAKE_CURRENT_LIST_DIR}/gephex_module.h
  ${CMAKE_CURRENT_LIST_DIR}/c_moduletables.h
  ${CMAKE_CURRENT_LIST_DIR}/c_output.h
  ${CMAKE_CURRENT_LIST_DIR}/c_outputplug.h
  ${CMAKE_CURRENT_LIST_DIR}/c_typeclass.h
  ${CMAKE_CURRENT_LIST_DIR}/c_type.h
  ${CMAKE_CURRENT_LIST_DIR}/c_typetables.h
  ${CMAKE_CURRENT_LIST_DIR}/moduleclassspec.h
  ${CMAKE_CURRENT_LIST_DIR}/moduleinfoutils.h
  ${CMAKE_CURRENT_LIST_DIR}/nameresolver.h
  ${CMAKE_CURRENT_LIST_DIR}/module.h
  ${CMAKE_CURRENT_LIST_DIR}/frei0r_module_plugin.cpp
  ${CMAKE_CURRENT_LIST_DIR}/frei0r_module_plugin.h
  ${CMAKE_CURRENT_LIST_DIR}/frei0r.h
  ${CMAKE_CURRENT_LIST_DIR}/frei0r.xpm
  interfaces/imoduleclassinforeceiver.h
  interfaces/imoduleclassinfosender.h
  interfaces/imoduleclassnamereceiver.h
  interfaces/imoduleclassreceiver.h
  interfaces/imoduleclasssender.h
  interfaces/imoduleclassspecreceiver.h
  interfaces/imoduleclassspecsender.h
  interfaces/itypeclassinforeceiver.h
  interfaces/itypeclassinfosender.h
  interfaces/itypeclassreceiver.h
  interfaces/itypeclasssender.h
)

# target_link_libraries(${PROJECT_NAME} geo)
set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# add_dependencies(${PROJECT_NAME} build_all_interfaces)
# install(TARGETS ${PROJECT_NAME}
#   DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/modules
#   PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
# )
