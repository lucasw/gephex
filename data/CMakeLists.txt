cmake_minimum_required(VERSION 2.8)
project(data)

add_custom_command(OUTPUT gephex.conf.default
  # ';' doesn't work for multiple sed s/// commands like it does on command line
  COMMAND sed -e 's~@prefix@~${CMAKE_INSTALL_PREFIX}~' -e 's~@gphx_type_lib_dir@~${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/types~' -e 's~@gphx_module_lib_dir@~${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/modules~' < ${CMAKE_CURRENT_LIST_DIR}/gephex.conf.default.in > gephex.conf.default
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(run ALL
  DEPENDS gephex.conf.default)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/gephex.conf.default
  DESTINATION ${CMAKE_INSTALL_PREFIX}/share/gephex
)

install(PROGRAMS run_in_terminal.sh
  DESTINATION ${CMAKE_INSTALL_PREFIX}/share/gephex
)

install(FILES gephex-gui.xpm gephex-engine.xpm
  DESTINATION ${CMAKE_INSTALL_PREFIX}/share/gephex/icon
)
