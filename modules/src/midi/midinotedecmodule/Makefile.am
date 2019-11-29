libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

midinotedecmodule_auto.c: midinotedecmodule.spec midinotedecmodule.h
	$(PLUC) c @srcdir@/midinotedecmodule.spec

midinotedecmodule.h: midinotedecmodule.spec
	$(PLUC) h @srcdir@/midinotedecmodule.spec

lib_LTLIBRARIES = midinotedecmodule.la

midinotedecmodule_la_SOURCES = \
        midinotedecmodule_auto.c \
        midinotedecmodule.cpp \
        midinotedecmodule.h \
        midinotedecmodule.spec \
        midinotedecmodule.xpm

midinotedecmodule_la_LIBADD = -lmidi -L@builddir@/../libmidi

midinotedecmodule_la_DEPENDENCIES = @builddir@/../libmidi/libmidi.a

midinotedecmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/miditype \
           -I@srcdir@/../../../types/src/numbertype \
	   -I @srcdir@/../libmidi

DISTCLEANFILES = midinotedecmodule.h midinotedecmodule_auto.c

#EXTRA_DIST = midinotedecmodule.dsp midinotedecmodule.mak midinotedecmodule.dep

