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

# hier muss mal jemand gucken wegen HAVE_GL oder sowatt...:/
if HAVE_GLX
GLLIBS = -lGL
GL_sOURCES = \
        gloutput.h \
	gloutput.c \
	glutil.h \
	glxutil.c
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
	xshmoutput.c $(AALIB_sOURCES) $(SDL_sOURCES) $(GL_sOURCES)


frboutmodule_la_LDFLAGS = -module -avoid-version -no-undefined -L/usr/X11R6/lib -L@builddir@/../libscale
frboutmodule_la_LIBADD = -lscale -lX11 -lXext $(AALIB_lDFLAGS) @SDL_LD_FLAGS@ $(GLLIBS)

frboutmodule_la_DEPENDENCIES = @builddir@/../libscale/libscale.a

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
		   -I@srcdir@/../libscale \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype @SDL_CFLAGS@


DISTCLEANFILES = frboutmodule.h frboutmodule_auto.c
