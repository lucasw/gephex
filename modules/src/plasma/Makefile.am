plasmamodule_auto.c: plasmamodule.spec plasmamodule.h
	python $(top_builddir)/pluc.py c plasmamodule.spec

plasmamodule.h: plasmamodule.spec
	python $(top_builddir)/pluc.py h plasmamodule.spec

lib_LTLIBRARIES = plasmamodule.la
plasmamodule_la_SOURCES = plasmamodule_auto.c plasmamodule.c plasmamodule.h plasmamodule.spec plasmamodule.xpm

plasmamodule_la_LDFLAGS = -module -avoid-version -no-undefined -L../libgrid

plasmamodule_la_LIBADD=-lgrid

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

