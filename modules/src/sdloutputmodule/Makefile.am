libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

sdloutputmodule_auto.c: sdloutputmodule.spec sdloutputmodule.h
	$(PLUC) c @srcdir@/sdloutputmodule.spec

sdloutputmodule.h: sdloutputmodule.spec
	$(PLUC) h @srcdir@/sdloutputmodule.spec

lib_LTLIBRARIES = sdloutputmodule.la

sdloutputmodule_la_SOURCES = 	sdloutputmodule_auto.c \
				sdloutputmodule.c \
				sdloutputmodule.h \
				sdloutputmodule.spec \
				sdloutputmodule.xpm

sdloutputmodule_la_LIBADD =  $(SDL_LIBS)

sdloutputmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = 	-I /usr/include/SDL \
		-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/framebuffertype 

 

DISTCLEANFILES = sdloutputmodule.h sdloutputmodule_auto.c