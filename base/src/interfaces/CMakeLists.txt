cmake_minimum_required(VERSION 2.8)
project(interfaces)

set(IF_SOURCES
	controlvalue.if
	enginecontrol.if
	error.if
	graphname.if
	modelcontrol.if
	modelstatus.if
	moduleclass.if
	moduleclassinfo.if
	moduleclassname.if
	moduleclassspec.if
	moduleconstructiondumb.if
	moduleconstructionsmart.if
	moduledata.if
	graphdata.if
	modulestatistics.if
	modulestatisticssmart.if
	renderercontrol.if
	rendererstatus.if
	serializedgraph.if
	smartcontrolvalue.if
	typeclass.if
	typeclassinfo.if
)

# TODO(lucasw) need to make these dependencies so when they change the
# other files will get rebuilt, also all the receiver/sender headers
# imoduleclass.h imoduleplugin.h imoduleclassspec.h imodule.h itask.h
# itypeclass.h itypefactory.h itype.h

foreach(T_NAME ${IF_SOURCES})
add_custom_command(OUTPUT interfaces/i${T_NAME}receiver.h
    COMMAND python ${CMAKE_CURRENT_LIST_DIR}/../../nic.py ir ${CMAKE_CURRENT_LIST_DIR}/${T_NAME}.if
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/interfaces
    # DEPENDS ${CMAKE_HOME_DIRECTORY}/base/src/interfaces/${T_NAME}.if
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/${T_NAME}.if
    COMMENT "generating ${T_NAME} receiver"
)

add_custom_command(OUTPUT interfaces/i${T_NAME}sender.h
    COMMAND python ${CMAKE_CURRENT_LIST_DIR}/../../nic.py is ${CMAKE_CURRENT_LIST_DIR}/${T_NAME}.if
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/interfaces
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/${T_NAME}.if
    COMMENT "generating ${T_NAME} sender"
)

endforeach()

# install(TARGETS ${PROJECT_NAME}
#   DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/modules
#   PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
# )
