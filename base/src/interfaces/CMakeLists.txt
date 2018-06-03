# cmake_minimum_required(VERSION 2.8)
# project(interfaces)

set(IF_SOURCES
	controlvalue
	enginecontrol
	error
	graphname
	modelcontrol
	modelstatus
	moduleclass
	moduleclassinfo
	moduleclassname
	moduleclassspec
	moduleconstructiondumb
	moduleconstructionsmart
	moduledata
	graphdata
	modulestatistics
	modulestatisticssmart
	renderercontrol
	rendererstatus
	serializedgraph
	smartcontrolvalue
	typeclass
	typeclassinfo
)

# TODO(lucasw) need to make these dependencies so when they change the
# other files will get rebuilt, also all the receiver/sender headers
# imoduleclass.h imoduleplugin.h imoduleclassspec.h imodule.h itask.h
# itypeclass.h itypefactory.h itype.h

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/interfaces)

foreach(T_NAME ${IF_SOURCES})
# message("'" ${T_NAME} "'")
add_custom_command(OUTPUT interfaces/i${T_NAME}receiver.h
    PRE_BUILD
    COMMAND python ${CMAKE_HOME_DIRECTORY}/base/nic.py ir ${CMAKE_CURRENT_BINARY_DIR}/interfaces ${CMAKE_HOME_DIRECTORY}/base/src/interfaces/${T_NAME}.if
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}  # /interfaces
    DEPENDS ${CMAKE_HOME_DIRECTORY}/base/src/interfaces/${T_NAME}.if
    COMMENT "generating i${T_NAME}receiver.h"
)
# list(APPEND all_interfaces "interfaces/i${T_NAME}receiver.h")

# add_custom_target(i${T_NAME}receiver_h interfaces/i${T_NAME}receiver.h)

add_custom_command(OUTPUT interfaces/i${T_NAME}sender.h
    PRE_BUILD
    COMMAND python ${CMAKE_HOME_DIRECTORY}/base/nic.py is ${CMAKE_CURRENT_BINARY_DIR}/interfaces ${CMAKE_HOME_DIRECTORY}/base/src/interfaces/${T_NAME}.if
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}  # /interfaces
    DEPENDS ${CMAKE_HOME_DIRECTORY}/base/src/interfaces/${T_NAME}.if
    COMMENT "generating i${T_NAME}sender.h"
)
# list(APPEND all_interfaces "interfaces/i${T_NAME}sender.h")

# add_custom_target(i${T_NAME}sender_h interfaces/i${T_NAME}sender.h)

endforeach()

# add_custom_target(build_all_interfaces ALL
#     DEPENDS ${all_interfaces})

# install(TARGETS ${PROJECT_NAME}
#   DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/modules
#   PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
# )
