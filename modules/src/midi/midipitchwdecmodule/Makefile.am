libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

midipitchwdecmodule_auto.c: midipitchwdecmodule.spec midipitchwdecmodule.h
	$(PLUC) c @srcdir@/midipitchwdecmodule.spec

midipitchwdecmodule.h: midipitchwdecmodule.spec
	$(PLUC) h @srcdir@/midipitchwdecmodule.spec

lib_LTLIBRARIES = midipitchwdecmodule.la

midipitchwdecmodule_la_SOURCES = \
        midipitchwdecmodule_auto.c \
        midipitchwdecmodule.cpp \
        midipitchwdecmodule.h \
        midipitchwdecmodule.spec \
        midipitchwdecmodule.xpm

midipitchwdecmodule_la_LIBADD = -lmidi -L@builddir@/../libmidi

midipitchwdecmodule_la_DEPENDENCIES = @builddir@/../libmidi/libmidi.a

midipitchwdecmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/miditype \
           -I@srcdir@/../../../types/src/numbertype \
	   -I @srcdir@/../libmidi

DISTCLEANFILES = midipitchwdecmodule.h midipitchwdecmodule_auto.c

#EXTRA_DIST = midipitchwdecmodule.dsp midipitchwdecmodule.mak midipitchwdecmodule.dep

