bindir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

frbinmodule_auto.c: frbinmodule.spec frbinmodule.h
	$(PLUC) c @srcdir@/frbinmodule.spec

frbinmodule.h: frbinmodule.spec
	$(PLUC) h @srcdir@/frbinmodule.spec

EXEEXT=.@SHAREDLIBEXT@

bin_PROGRAMS = frbinmodule

frbinmodule_CFLAGS = $(AM_CFLAGS) @SHARED_COMP_FLAGS@
frbinmodule_CXXFLAGS = $(AM_CXXFLAGS) @SHARED_COMP_FLAGS@

if SHARED_USE_DEF_FILE
DEFFILE=frbinmodule.def
else
DEFFILE=
endif

if WITH_AVIFILE
AVIFILE_sOURCES = avifiledriver.h avifiledriver.cpp
endif

if WITH_MPEG3
MPEG3_sOURCES = mpeg3driver.h mpeg3driver.cpp
MPEG3_lDFLAGS = @MPEG3_LDFLAGS@
endif

if WITH_SDL_IMAGE
SDL_IMAGE_sOURCES = sdlimagedriver.h sdlimagedriver.cpp

SDL_IMAGE_lDFLAGS = @SDL_LD_FLAGS@ @SDL_IMAGE_LDFLAGS@
SDL_IMAGE_cFLAGS  = @SDL_CFLAGS@
endif

if WITH_FFMPEG
FFMPEG_sOURCES = ffmpegdriver.h ffmpegdriver.cpp
endif

if OS_WINDOWS
PLT_sOURCES = \
        vfwdriver.cpp \
	vfwdriver.h \
	timer.cpp \
	timer.h

# TODO: directx with cygwin disabled for now
#if HAVE_DX
#DX_sOURCES = \
#	dshowdriver.cpp \
#	dshowdriver.h
#endif

WIN32_LIBS = -lvfw32 -lgdi32

endif

frbinmodule_SOURCES = \
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
	framecache.cpp $(AVIFILE_sOURCES) $(MPEG3_sOURCES) $(SDL_IMAGE_sOURCES) $(FFMPEG_sOURCES) $(PLT_sOURCES) $(DX_sOURCES)

frbinmodule_LDFLAGS = @SHARED_LD_FLAGS@ \
        -L@builddir@/../libscale $(AVIFILE_LDFLAGS) $(SDL_IMAGE_lDFLAGS) $(MPEG3_lDFLAGS) @FFMPEG_LDFLAGS@ $(DX_LIBS) $(WIN32_LIBS)

frbinmodule_LDADD = -lstdc++ -lscale

frbinmodule_DEPENDENCIES = @builddir@/../libscale/libscale.a

INCLUDES = \
	-I @srcdir@/../../../engine/src/engine \
	-I @srcdir@/../../../util/include \
	-I @srcdir@/../libscale \
	-I @srcdir@/../../../types/src/numbertype \
	-I @srcdir@/../../../types/src/stringtype \
	-I @srcdir@/../../../types/src/framebuffertype \
	$(AVIFILE_CXXFLAGS) $(SDL_IMAGE_cFLAGS) @FFMPEG_CFLAGS@ $(DX_CXXFLAGS)

DISTCLEANFILES = frbinmodule.h frbinmodule_auto.c
EXTRA_DIST = frbinmodule.vcproj frbinmodule.dsp frbinmodule.mak frbinmodule.dep
