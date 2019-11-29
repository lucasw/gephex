cmake_minimum_required(VERSION 2.8)
project(gephex)

add_definitions(-DHAVE_CONFIG_H)

###############################################################################
find_package(X11)
set(HAVE_X11 ${X11_FOUND})

if (UNIX AND NOT APPLE)
set(OS_LINUX true)
set(OS_POSIX true)
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
if(${SDL_FOUND})
else()
  check_include_files(strings.h HAVE_STRINGS_H)
endif()
check_include_files(string.h HAVE_STRING_H)
check_include_files(sys_stat.h HAVE_SYS_STAT_H)
check_include_files(sys_types.h HAVE_SYS_TYPES_H)
check_include_files(unistd.h HAVE_UNISTD_H)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config_cmake.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h
    @ONLY)
###############################################################################

include_directories(
  ${CMAKE_HOME_DIRECTORY}/engine/src
)

# Misc
add_subdirectory(data)

# Gui
add_subdirectory(qtgui/src/guimodel)
add_subdirectory(qtgui/src/gui)

# Engine
add_subdirectory(engine/src/dllloader)
add_subdirectory(engine/src/model)
add_subdirectory(engine/src/renderer)
add_subdirectory(base/src/netinterfaces)
add_subdirectory(base/src/net)  # gphxnetwork
add_subdirectory(base/src/utils)
add_subdirectory(engine/src/engine)

# Types
add_subdirectory(types/src/framebuffertype)
add_subdirectory(types/src/numbertype)
add_subdirectory(types/src/positiontype)
add_subdirectory(types/src/rgbtype)
add_subdirectory(types/src/stringtype)

# Module libs
add_subdirectory(modules/src/libgrid)
add_subdirectory(modules/src/libscale)
add_subdirectory(modules/src/libcolorconv)
add_subdirectory(util/src/libgeo)
add_subdirectory(util/src/misc)

# Modules
add_subdirectory(modules/src/blurmodule)
add_subdirectory(modules/src/bwmodule)
add_subdirectory(modules/src/centermodule)
add_subdirectory(modules/src/color2numbermodule)
add_subdirectory(modules/src/frbinmodule)
add_subdirectory(modules/src/frboutmodule)
add_subdirectory(modules/src/imagebuffermodule)
add_subdirectory(modules/src/imgarithmodule)
add_subdirectory(modules/src/isingnoizemodule)
add_subdirectory(modules/src/numarithmodule)
add_subdirectory(modules/src/number2colormodule)
add_subdirectory(modules/src/numbermodule)
add_subdirectory(modules/src/numposmodule)
add_subdirectory(modules/src/noisemodule)
add_subdirectory(modules/src/pixelizemodule)
add_subdirectory(modules/src/plasmamodule)
add_subdirectory(modules/src/posnummodule)
add_subdirectory(modules/src/signalgenmodule)
add_subdirectory(modules/src/planemodule)
add_subdirectory(modules/src/rangeconvertmodule)
add_subdirectory(modules/src/rotozoommodule)
add_subdirectory(modules/src/staticcolormodule)
add_subdirectory(modules/src/tunnelmodule)
