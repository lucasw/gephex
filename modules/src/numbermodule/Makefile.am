numbermodule_auto.c: numbermodule.spec numbermodule.h
	python $(top_builddir)/pluc.py c numbermodule.spec

numbermodule.h: numbermodule.spec
	python $(top_builddir)/pluc.py h numbermodule.spec

lib_LTLIBRARIES = numbermodule.la
numbermodule_la_SOURCES = numbermodule_auto.c numbermodule.c numbermodule.h numbermodule.spec  numbermodule_icon.xpm

numbermodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types  -I $(baseincludedir)/engine
