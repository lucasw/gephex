cmake_minimum_required(VERSION 2.8)
project(data)

add_custom_command(OUTPUT gephex.conf.default
  # ';' doesn't work for multiple sed s/// commands like it does on command line
  COMMAND sed -e 's~@prefix@~${CMAKE_INSTALL_PREFIX}~' -e 's~@gphx_type_lib_dir@~${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/types~' -e 's~@gphx_module_lib_dir@~${CMAKE_INSTALL_PREFIX}/lib/gephex-0.4/modules~' < ${CMAKE_CURRENT_LIST_DIR}/gephex.conf.default.in > gephex.conf.default
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(OUTPUT gephex-wrapper
  # ';' doesn't work for multiple sed s/// commands like it does on command line
  COMMAND sed -e 's~@prefix@~${CMAKE_INSTALL_PREFIX}~' < ${CMAKE_CURRENT_LIST_DIR}/gephex-wrapper.in > gephex-wrapper
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(run ALL
  DEPENDS gephex.conf.default gephex-wrapper)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/gephex.conf.default
  DESTINATION ${CMAKE_INSTALL_PREFIX}/share/gephex
)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/gephex-wrapper
  DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

install(PROGRAMS run_in_terminal.sh
  DESTINATION ${CMAKE_INSTALL_PREFIX}/share/gephex
)

install(FILES gephex-gui.xpm gephex-engine.xpm
  DESTINATION ${CMAKE_INSTALL_PREFIX}/share/gephex/icon
)


install(CODE "execute_process( \
  COMMAND ${CMAKE_COMMAND} -E create_symlink \
  ${CMAKE_INSTALL_PREFIX}/bin/gephex-wrapper \
  ${CMAKE_INSTALL_PREFIX}/bin/gephex-engine \
  )"
)

install(CODE "execute_process( \
  COMMAND ${CMAKE_COMMAND} -E create_symlink \
  ${CMAKE_INSTALL_PREFIX}/bin/gephex-wrapper \
  ${CMAKE_INSTALL_PREFIX}/bin/gephex-gui \
  )"
)

install(CODE "execute_process( \
  COMMAND ${CMAKE_COMMAND} -E create_symlink \
  ${CMAKE_INSTALL_PREFIX}/bin/gephex-wrapper \
  ${CMAKE_INSTALL_PREFIX}/bin/gephex \
  )"
)
