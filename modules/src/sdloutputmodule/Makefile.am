sdloutputmodule_auto.c: sdloutputmodule.spec sdloutputmodule.h
	python $(top_builddir)/pluc.py c sdloutputmodule.spec

sdloutputmodule.h: sdloutputmodule.spec
	python $(top_builddir)/pluc.py h sdloutputmodule.spec

lib_LTLIBRARIES = sdloutputmodule.la
sdloutputmodule_la_SOURCES = sdloutputmodule_auto.c sdloutputmodule.c sdloutputmodule.h sdloutputmodule.spec sdloutputmodule.xpm

sdloutputmodule_la_LIBADD = -L/usr/lib -lSDL -lpthread

sdloutputmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = `sdl-config --cflags` -I $(baseincludedir) -I $(baseincludedir)/types  -I $(baseincludedir)/engine

.PHONY: clean
clean:
	rm -f sdloutputmodule.h sdloutputmodule_auto.c