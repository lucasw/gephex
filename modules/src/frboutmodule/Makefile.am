libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

frboutmodule_auto.c: frboutmodule.spec frboutmodule.h
	$(PLUC) c @srcdir@/frboutmodule.spec

frboutmodule.h: frboutmodule.spec
	$(PLUC) h @srcdir@/frboutmodule.spec

lib_LTLIBRARIES = frboutmodule.la

if HAVE_X11
X11_sOURCES = \
	x11output.c \
	x11output.h \
	x11stuff.h \
	x11stuff.c \
	vloopbackoutput.h \
	vloopbackoutput.c
endif

if WITH_AALIB
AALIB_sOURCES = \
	aaoutput.c \
	aaoutput.h
AALIB_lDFLAGS = -laa
endif

if WITH_SDL
SDL_sOURCES = \
	sdloutput.c \
	sdloutput.h
SDL_cFLAGS=@SDL_CFLAGS@
SDL_lD_FLAGS=@SDL_LD_FLAGS@
endif

if WITH_GL
GLLIBS = -lGL
GL_sOURCES = \
        gloutput.h \
	gloutput.cpp \
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
	slist.h \
	slist.c $(X11_sOURCES) $(AALIB_sOURCES) $(SDL_sOURCES) $(GL_sOURCES)


frboutmodule_la_LDFLAGS = -module -avoid-version -no-undefined -L/usr/X11R6/lib -L@builddir@/../libscale -L/usr/X11R6/lib -L@builddir@/../libcolorconv
frboutmodule_la_LIBADD = -lscale -lcolorconv -lX11 -lXext -lXv $(AALIB_lDFLAGS) $(SDL_lD_FLAGS) $(GLLIBS)

frboutmodule_la_DEPENDENCIES = @builddir@/../libscale/libscale.a \
			       @builddir@/../libcolorconv/libcolorconv.a

INCLUDES = -I@srcdir@/../../../engine/src/engine \
	   -I@srcdir@/../../../util/include \
	   -I@srcdir@/../libscale \
	   -I@srcdir@/../libcolorconv \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype $(SDL_cFLAGS)


DISTCLEANFILES = frboutmodule.h frboutmodule_auto.c
EXTRA_DIST = frboutmodule.dsp frboutmodule.mak frboutmodule.dep \
	gdioutput.c gdioutput.h \
	multimonitor.c multimonitor.h
