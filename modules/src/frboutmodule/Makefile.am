libdir = @libdir@/gephex/modules

PLUC=python @top_srcdir@/modules/pluc.py

frboutmodule_auto.c: frboutmodule.spec frboutmodule.h
	$(PLUC) c @srcdir@/frboutmodule.spec

frboutmodule.h: frboutmodule.spec
	$(PLUC) h @srcdir@/frboutmodule.spec

lib_LTLIBRARIES = frboutmodule.la

if HAVE_AALIB
AALIB_sOURCES = \
	aaoutput.c \
	aaoutput.h
AALIB_lDFLAGS = -laa
endif

if HAVE_SDL
SDL_sOURCES = \
	sdloutput.c \
	sdloutput.h
endif

frboutmodule_la_SOURCES = \
        frboutmodule_auto.c \
        frboutmodule.c \
        frboutmodule.h \
        frboutmodule.spec \
        frboutmodule.xpm \
        outputdriver.h \
	ximageoutput.h \
	ximageoutput.c \
	adjustutil.h \
	adjustutil.c \
	xshmoutput.h \
	xshmoutput.c $(AALIB_sOURCES) $(SDL_sOURCES)


frboutmodule_la_LDFLAGS = -module -avoid-version -no-undefined -L/usr/X11R6/lib
frboutmodule_la_LIBADD = -lX11 -lXext $(AALIB_lDFLAGS) @SDL_LIBS@

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype @SDL_CFLAGS@


DISTCLEANFILES = frboutmodule.h frboutmodule_auto.c
