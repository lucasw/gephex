libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

frbinmodule_auto.c: frbinmodule.spec frbinmodule.h
	$(PLUC) c @srcdir@/frbinmodule.spec

frbinmodule.h: frbinmodule.spec
	$(PLUC) h @srcdir@/frbinmodule.spec

lib_LTLIBRARIES = frbinmodule.la

if HAVE_AVIFILE
AVIFILE_sOURCES = \
	avifiledriver.h \
	avifiledriver.cpp
endif

if HAVE_MPEG3
MPEG3_sOURCES = \
	mpeg3driver.h \
	mpeg3driver.cpp
MPEG3_lDFLAGS =  @MPEG3_LDFLAGS@
endif

if HAVE_SDL_IMAGE
SDL_IMAGE_sOURCES = \
	sdlimagedriver.h \
	sdlimagedriver.cpp

SDL_IMAGE_lDFLAGS =  @SDL_LD_FLAGS@ @SDL_IMAGE_LDFLAGS@
SDL_IMAGE_cFLAGS  =  @SDL_CFLAGS@
endif

frbinmodule_la_SOURCES = \
	frbinmodule_auto.c \
	frbinmodule.cpp \
	frbinmodule.h \
	frbinmodule.spec \
	frbinmodule.xpm \
	videofiledriver.h \
	bmpdriver.h \
	bmpdriver.cpp \
	driverfactory.h \
	framecache.h \
	framecache.cpp $(AVIFILE_sOURCES) $(MPEG3_sOURCES) $(SDL_IMAGE_sOURCES)

frbinmodule_la_LDFLAGS = \
        -module -avoid-version -no-undefined \
        -L@builddir@/../libscale $(AVIFILE_LDFLAGS) $(SDL_IMAGE_lDFLAGS) $(MPEG3_lDFLAGS)

frbinmodule_la_LIBADD = -lstdc++ -lscale

frbinmodule_la_DEPENDENCIES = @builddir@/../libscale/libscale.a

INCLUDES = 	\
		-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../libscale \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/stringtype \
		-I @srcdir@/../../../types/src/framebuffertype \
		$(AVIFILE_CXXFLAGS) $(SDL_IMAGE_cFLAGS)

DISTCLEANFILES = frbinmodule.h frbinmodule_auto.c
