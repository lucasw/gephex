tunnelmodule_auto.c: tunnelmodule.spec tunnelmodule.h
	python $(top_builddir)/pluc.py c tunnelmodule.spec

tunnelmodule.h: tunnelmodule.spec
	python $(top_builddir)/pluc.py h tunnelmodule.spec

lib_LTLIBRARIES = tunnelmodule.la
tunnelmodule_la_SOURCES = tunnelmodule_auto.c tunnelmodule.c tunnelmodule.h  tunnelmodule.spec  tunnelmodule.xpm

tunnelmodule_la_LDFLAGS = -module -avoid-version -no-undefined -L../libgrid

tunnelmodule_la_LIBADD = -lgrid

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types  -I $(baseincludedir)/engine
