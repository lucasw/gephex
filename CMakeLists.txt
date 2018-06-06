cmake_minimum_required(VERSION 2.8)
project(gephex)

add_definitions(-DOS_POSIX)

include(CheckIncludeFiles)
check_include_files(dlfcn.h HAVE_DLFCN_H)
check_include_files(inttypes.h HAVE_INTTYPES_H)
check_include_files(memory.h HAVE_MEMORY_H)
check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(stdlib.h HAVE_STDLIB_H)
check_include_files(strings.h HAVE_STRINGS_H)
check_include_files(string.h HAVE_STRING_H)
check_include_files(sys_stat.h HAVE_SYS_STAT_H)
check_include_files(sys_types.h HAVE_SYS_TYPES_H)
check_include_files(unistd.h HAVE_UNISTD_H)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config_cmake.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

include_directories(
  ${CMAKE_HOME_DIRECTORY}/engine/src
)

# include(base/src/interfaces/CMakeLists.txt)
include(engine/src/dllloader/CMakeLists.txt)
include(engine/src/model/CMakeLists.txt)
include(engine/src/renderer/CMakeLists.txt)
include(base/src/netinterfaces/CMakeLists.txt)
include(base/src/net/CMakeLists.txt)
include(base/src/utils/CMakeLists.txt)

include(modules/src/frbinmodule/CMakeLists.txt)
include(modules/src/frboutmodule/CMakeLists.txt)
include(util/src/libgeo/CMakeLists.txt)
include(modules/src/rotozoommodule/CMakeLists.txt)
