EXTRA_DIST = ifstype.dsp ifstype.mak ifstype.dep ifstype.def

includedir = @includedir@/gephex/types
libdir = @libdir@/gephex/types
INCLUDES  =  	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include
lib_LTLIBRARIES = ifstype.la

ifstype_la_SOURCES = ifstype.c
ifstype_la_LDFLAGS = -module -avoid-version

include_HEADERS = ifstype.h
