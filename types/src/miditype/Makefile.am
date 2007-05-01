EXTRA_DIST = miditype.vcproj miditype.dsp miditype.mak miditype.dep miditype.def

includedir = @includedir@/gephex/types
libdir = @gphx_type_lib_dir@
INCLUDES  =  	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include

lib_LTLIBRARIES = miditype.la

miditype_la_SOURCES = miditype.c
miditype_la_LDFLAGS = -module -avoid-version -no-undefined

include_HEADERS = miditype.h




