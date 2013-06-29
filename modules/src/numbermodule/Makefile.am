libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

numbermodule_auto.c: numbermodule.spec numbermodule.h
	$(PLUC) c @srcdir@/numbermodule.spec

numbermodule.h: numbermodule.spec
	$(PLUC) h @srcdir@/numbermodule.spec

lib_LTLIBRARIES = numbermodule.la
numbermodule_la_SOURCES = \
	numbermodule_auto.c \
	numbermodule.c \
	numbermodule.h \
	numbermodule.spec \
	numbermodule_icon.xpm

numbermodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = \
	-I @srcdir@/../../../engine/src/engine \
	-I @srcdir@/../../../util/include \
	-I @srcdir@/../../../util/src/misc \
	-I @srcdir@/../../../types/src/numbertype 

DISTCLEANFILES = numbermodule.h numbermodule_auto.c
EXTRA_DIST = numbermodule.vcproj numbermodule.dsp numbermodule.mak numbermodule.dep
