staticcolormodule_auto.c: staticcolormodule.spec staticcolormodule.h
	python $(top_builddir)/pluc.py c staticcolormodule.spec

staticcolormodule.h: staticcolormodule.spec
	python $(top_builddir)/pluc.py h staticcolormodule.spec

lib_LTLIBRARIES = staticcolormodule.la
staticcolormodule_la_SOURCES = staticcolormodule_auto.c staticcolormodule.c staticcolormodule.h staticcolormodule.spec staticcolormodule.xpm

staticcolormodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

