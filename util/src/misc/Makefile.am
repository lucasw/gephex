baseincludedir = @includedir@/gephex
includedir = @includedir@/gephex/misc
libdir = @libdir@/gephex

lib_LIBRARIES = libmisc.a

libmisc_a_SOURCES = cpuinfo.cpp cpuspeed.cpp fastmemcpy.cpp timer.cpp

include_HEADERS = cpuinfo.h cpuspeed.h fastmemcpy.h timer.h

INCLUDES = -I .. #-I $(baseincludedir) 
