EXTRA_DIST = misc.vcproj misc.dsp misc.mak misc.dep

baseincludedir = @includedir@/gephex
libdir = @libdir@/gephex

check_PROGRAMS = crandgentest

noinst_LIBRARIES = libmisc.a

libmisc_a_SOURCES = libmisc.c #cpuinfo.cpp cpuspeed.cpp fastmemcpy.cpp timer.cpp

noinst_HEADERS = crandgen.h #cpuinfo.h cpuspeed.h fastmemcpy.h timer.h

INCLUDES = -I @top_srcdir@/util/include

crandgentest_SOURCES = crandgentest.c
