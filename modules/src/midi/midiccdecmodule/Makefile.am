libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

midiccdecmodule_auto.c: midiccdecmodule.spec midiccdecmodule.h
	$(PLUC) c @srcdir@/midiccdecmodule.spec

midiccdecmodule.h: midiccdecmodule.spec
	$(PLUC) h @srcdir@/midiccdecmodule.spec

lib_LTLIBRARIES = midiccdecmodule.la

midiccdecmodule_la_SOURCES = \
        midiccdecmodule_auto.c \
        midiccdecmodule.cpp \
        midiccdecmodule.h \
        midiccdecmodule.spec \
        midiccdecmodule.xpm

midiccdecmodule_la_LIBADD = -lmidi -L@builddir@/../libmidi

midiccdecmodule_la_DEPENDENCIES = @builddir@/../libmidi/libmidi.a

midiccdecmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/miditype \
           -I@srcdir@/../../../types/src/numbertype \
	   -I @srcdir@/../libmidi

DISTCLEANFILES = midiccdecmodule.h midiccdecmodule_auto.c

#EXTRA_DIST = midiccdecmodule.vcproj midiccdecmodule.dsp midiccdecmodule.mak midiccdecmodule.dep

