avifilemodule_auto.c: avifilemodule.spec avifilemodule.h
	python $(top_builddir)/pluc.py c avifilemodule.spec

avifilemodule.h: avifilemodule.spec
	python $(top_builddir)/pluc.py h avifilemodule.spec

lib_LTLIBRARIES = avifilemodule.la
avifilemodule_la_SOURCES = avifilemodule_auto.c avifilemodule.c avifilemodule.h avifilemodule.spec avifilemodule.xpm

avifilemodule_la_LDFLAGS = -module -avoid-version -no-undefined

#INCLUDES  =  -I$(top_builddir)/../engine/src/engine 
INCLUDES  =  -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

.PHONY: clean
clean:
	rm -f avifilemodule.h avifilemodule_auto.c
