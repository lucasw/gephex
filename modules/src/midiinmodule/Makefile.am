libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

midiinmodule_auto.c: midiinmodule.spec midiinmodule.h
	$(PLUC) c @srcdir@/midiinmodule.spec

midiinmodule.h: midiinmodule.spec
	$(PLUC) h @srcdir@/midiinmodule.spec

lib_LTLIBRARIES = midiinmodule.la

midiinmodule_la_SOURCES = 	midiinmodule_auto.c \
				midiinmodule.c \
				midiinmodule.h \
				midiinmodule.spec \
				midiinmodule.xpm

midiinmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/stringtype \
		-I @srcdir@/../../../types/src/miditype 

 

DISTCLEANFILES = midiinmodule.h midiinmodule_auto.c
