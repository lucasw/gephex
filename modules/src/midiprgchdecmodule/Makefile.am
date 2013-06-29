libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

midiprgchdecmodule_auto.c: midiprgchdecmodule.spec midiprgchdecmodule.h
	$(PLUC) c @srcdir@/midiprgchdecmodule.spec

midiprgchdecmodule.h: midiprgchdecmodule.spec
	$(PLUC) h @srcdir@/midiprgchdecmodule.spec

lib_LTLIBRARIES = midiprgchdecmodule.la

midiprgchdecmodule_la_SOURCES = \
        midiprgchdecmodule_auto.c \
        midiprgchdecmodule.cpp \
        midiprgchdecmodule.h \
        midiprgchdecmodule.spec \
        midiprgchdecmodule.xpm

midiprgchdecmodule_la_LIBADD = -lmidi -L@builddir@/../libmidi

midiprgchdecmodule_la_DEPENDENCIES = @builddir@/../libmidi/libmidi.a

midiprgchdecmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/miditype \
           -I@srcdir@/../../../types/src/numbertype \
	   -I @srcdir@/../libmidi

DISTCLEANFILES = midiprgchdecmodule.h midiprgchdecmodule_auto.c

#EXTRA_DIST = midinotedecmodule.dsp midinotedecmodule.mak midinotedecmodule.dep

