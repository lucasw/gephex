baseincludedir = @includedir@/gephex
includedir = @includedir@/gephex/misc
libdir = @libdir@/gephex

check_PROGRAMS = crandgentest

noinst_LIBRARIES = libmisc.a

libmisc_a_SOURCES = #cpuinfo.cpp cpuspeed.cpp fastmemcpy.cpp timer.cpp

include_HEADERS = crandgen.h #cpuinfo.h cpuspeed.h fastmemcpy.h timer.h

INCLUDES = -I @top_srcdir@/util/include

crandgentest_SOURCES = crandgentest.c
