flashmodule_auto.c: flashmodule.spec flashmodule.h
	python $(top_builddir)/pluc.py c flashmodule.spec

flashmodule.h: flashmodule.spec
	python $(top_builddir)/pluc.py h flashmodule.spec

lib_LTLIBRARIES = flashmodule.la
flashmodule_la_SOURCES = flashmodule_auto.c flashmodule.c flashmodule.h flashmodule.spec flashmodule.xpm

flashmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES  =  -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

.PHONY: clean
clean:
	rm -f flashmodule.h flashmodule_auto.c
