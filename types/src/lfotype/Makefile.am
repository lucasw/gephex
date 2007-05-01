EXTRA_DIST = lfotype.vcproj lfotype.dsp lfotype.mak lfotype.dep lfotype.def

includedir = @includedir@/gephex/types
libdir = @gphx_type_lib_dir@
INCLUDES  =  	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include

lib_LTLIBRARIES = lfotype.la

lfotype_la_SOURCES = lfotype.c
lfotype_la_LDFLAGS = -module -avoid-version -no-undefined

include_HEADERS = lfotype.h
