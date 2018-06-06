cmake_minimum_required(VERSION 2.8)
project(gephex)

add_definitions(-DOS_POSIX)

find_package(X11)
set(HAVE_X11 ${X11_FOUND})

if (UNIX AND NOT APPLE)
set(OS_LINUX true)
endif()

# TODO(lucasw) this isn't working with the @PACKAGE@ in the config.h
# set(PACKAGE "gephex")
add_definitions(-DPACKAGE="gephex" -DVERSION="0.4.6")

# TODO(lucasw) need to make this decision between linux or sdl
set(WITH_LINUX_JOYSTICK true)

# TODO(lucasw)
# find_package(OSS)
# set(WITH_OSS ${OSS_FOUND})
set(WITH_OSS true)

find_package(SDL)
set(WITH_SDL ${SDL_FOUND})

find_package(SDL_image)
set(WITH_SDL_IMAGE ${SDL_image_FOUND})

find_package(SDL_ttf)
set(WITH_SDL_TTF ${SDL_ttf_FOUND})

# TODO(lucasw)
# find_package(V4L)
# set(WITH_V4L ${V4L_FOUND})
set(WITH_V4L true)

find_package(PNG)
set(WITH_LIBPNG ${PNG_FOUND})

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
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config_cmake.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h
    @ONLY)

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
