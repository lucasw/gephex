xfademodule_auto.c: xfademodule.spec xfademodule.h
	python $(top_builddir)/pluc.py c xfademodule.spec

xfademodule.h: xfademodule.spec
	python $(top_builddir)/pluc.py h xfademodule.spec

lib_LTLIBRARIES = xfademodule.la
xfademodule_la_SOURCES = xfademodule_auto.c xfademodule.c xfademodule.h xfademodule.spec xfademodule.xpm

xfademodule_la_LDFLAGS = -module -avoid-version

INCLUDES  =  -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

.PHONY: clean
clean:
	rm -f xfademodule.h xfademodule_auto.c
