EXTRA_DIST = miditype.dsp miditype.mak miditype.dep miditype.def

includedir = @includedir@/gephex/types
libdir = @libdir@/gephex/types
INCLUDES  =  	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include

lib_LTLIBRARIES = miditype.la

miditype_la_SOURCES = miditype.c
miditype_la_LDFLAGS = -module -avoid-version

include_HEADERS = miditype.h




