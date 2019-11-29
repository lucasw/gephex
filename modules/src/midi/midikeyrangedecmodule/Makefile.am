libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

midikeyrangedecmodule_auto.c: midikeyrangedecmodule.spec midikeyrangedecmodule.h
	$(PLUC) c @srcdir@/midikeyrangedecmodule.spec

midikeyrangedecmodule.h: midikeyrangedecmodule.spec
	$(PLUC) h @srcdir@/midikeyrangedecmodule.spec

lib_LTLIBRARIES = midikeyrangedecmodule.la

midikeyrangedecmodule_la_SOURCES = \
        midikeyrangedecmodule_auto.c \
        midikeyrangedecmodule.cpp \
        midikeyrangedecmodule.h \
        midikeyrangedecmodule.spec \
        midikeyrangedecmodule.xpm

midikeyrangedecmodule_la_LIBADD = -lmidi -L@builddir@/../libmidi

midikeyrangedecmodule_la_DEPENDENCIES = @builddir@/../libmidi/libmidi.a

midikeyrangedecmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/miditype \
           -I@srcdir@/../../../types/src/numbertype \
	   -I @srcdir@/../libmidi

DISTCLEANFILES = midikeyrangedecmodule.h midikeyrangedecmodule_auto.c

#EXTRA_DIST = midikeyrangedecmodule.dsp midikeyrangedecmodule.mak midikeyrangedecmodule.dep

