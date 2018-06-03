cmake_minimum_required(VERSION 2.8)
project(gephex)

#include(base/src/interfaces/CMakeLists.txt)
include(engine/src/dllloader/CMakeLists.txt)

include(modules/src/frbinmodule/CMakeLists.txt)
include(modules/src/frboutmodule/CMakeLists.txt)
include(util/src/libgeo/CMakeLists.txt)
include(modules/src/rotozoommodule/CMakeLists.txt)
