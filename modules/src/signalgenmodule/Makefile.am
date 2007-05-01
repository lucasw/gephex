libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

signalgenmodule_auto.c: signalgenmodule.spec signalgenmodule.h
	$(PLUC) c @srcdir@/signalgenmodule.spec

signalgenmodule.h: signalgenmodule.spec
	$(PLUC) h @srcdir@/signalgenmodule.spec

lib_LTLIBRARIES = signalgenmodule.la
signalgenmodule_la_SOURCES = signalgenmodule_auto.c \
			     signalgenmodule.cpp \
			     signalgenmodule.h \
			     signalgenmodule.spec \
			     signalgenmodule.xpm \
			     signals.cpp signals.h

signalgenmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I @srcdir@/../../../engine/src/engine \
	   -I @srcdir@/../../../util/include \
	   -I @srcdir@/../../../util/src/misc \
	   -I @srcdir@/../../../types/src/numbertype \
	   -I @srcdir@/../../../types/src/stringtype

DISTCLEANFILES = signalgenmodule.h signalgenmodule_auto.c
EXTRA_DIST = signalgenmodule.vcproj signalgenmodule.dsp signalgenmodule.mak signalgenmodule.dep
