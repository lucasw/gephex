midiinmodule_auto.c: midiinmodule.spec midiinmodule.h
	python $(top_builddir)/pluc.py c midiinmodule.spec

midiinmodule.h: midiinmodule.spec
	python $(top_builddir)/pluc.py h midiinmodule.spec

lib_LTLIBRARIES = midiinmodule.la
midiinmodule_la_SOURCES = midiinmodule_auto.c midiinmodule.c midiinmodule.h midiinmodule.spec midiinmodule.xpm

midiinmodule_la_LDFLAGS = -module -avoid-version -no-undefined

#INCLUDES  =  -I$(top_builddir)/../engine/src/engine 
INCLUDES  =  -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

.PHONY: clean
clean:
	rm -f midiinmodule.h midiinmodule_auto.c
