netcontrol_auto.c: netcontrol.spec netcontrol.h
	python $(top_builddir)/pluc.py c netcontrol.spec

netcontrol.h: netcontrol.spec
	python $(top_builddir)/pluc.py h netcontrol.spec

lib_LTLIBRARIES = netcontrol.la
netcontrol_la_SOURCES = netcontrol_auto.c netcontrol.c netcontrol.h netcontrol.spec netcontrol.xpm

netcontrol_la_LDFLAGS = -module -avoid-version -no-undefined

#INCLUDES  =  -I$(top_builddir)/../engine/src/engine 
INCLUDES  =  -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

.PHONY: clean
clean:
	rm -f netcontrol.h netcontrol_auto.c
