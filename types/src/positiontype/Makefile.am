EXTRA_DIST = positiontype.dsp positiontype.mak positiontype.dep \
	positiontype.def

includedir = @includedir@/gephex/types
libdir = @libdir@/gephex/types
INCLUDES  =  	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include

lib_LTLIBRARIES = positiontype.la

positiontype_la_SOURCES = positiontype.c
positiontype_la_LDFLAGS = -module -avoid-version

include_HEADERS = positiontype.h




