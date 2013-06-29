EXTRA_DIST = ifstype.vcproj ifstype.dsp ifstype.mak ifstype.dep ifstype.def

includedir = @includedir@/gephex/types
libdir = @gphx_type_lib_dir@
INCLUDES  =  	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include
lib_LTLIBRARIES = ifstype.la

ifstype_la_SOURCES = ifstype.c
ifstype_la_LDFLAGS = -module -avoid-version -no-undefined

include_HEADERS = ifstype.h
