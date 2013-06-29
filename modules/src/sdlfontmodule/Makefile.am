libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

sdlfontmodule_auto.c: sdlfontmodule.spec sdlfontmodule.h
	$(PLUC) c @srcdir@/sdlfontmodule.spec

sdlfontmodule.h: sdlfontmodule.spec
	$(PLUC) h @srcdir@/sdlfontmodule.spec

lib_LTLIBRARIES = sdlfontmodule.la

SDL_TTF_lDFLAGS =  @SDL_LD_FLAGS@ @SDL_TTF_LDFLAGS@
SDL_TTF_cFLAGS  =  @SDL_CFLAGS@ 


sdlfontmodule_la_SOURCES = \
        sdlfontmodule_auto.c \
        sdlfontmodule.cpp \
        sdlfontmodule.h \
        sdlfontmodule.spec \
        sdlfontmodule.xpm


sdlfontmodule_la_LDFLAGS = -module -avoid-version -no-undefined $(SDL_TTF_lDFLAGS)

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/rgbtype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/positiontype \
           -I@srcdir@/../../../types/src/numbertype \
           $(SDL_TTF_cFLAGS)
           
DISTCLEANFILES = sdlfontmodule.h sdlfontmodule_auto.c

EXTRA_DIST = sdlfontmodule.vcproj sdlfontmodule.dsp sdlfontmodule.mak sdlfontmodule.dep
