libdir = @libdir@/gephex/modules

PLUC=python @top_srcdir@/modules/pluc.py

audioinmodule_auto.c: audioinmodule.spec audioinmodule.h
	$(PLUC) c @srcdir@/audioinmodule.spec

audioinmodule.h: audioinmodule.spec
	$(PLUC) h @srcdir@/audioinmodule.spec

lib_LTLIBRARIES = audioinmodule.la

if WITH_ASOUNDLIB
ALSALIB_sOURCES = \
        alsadriver.cpp \
	alsadriver.h
ALSALIB_lDFLAGS = -lasound
endif

if WITH_OSS
OSS_sOURCES = \
	ossdriver.cpp \
	ossdriver.h
endif

audioinmodule_la_SOURCES = \
        audioinmodule_auto.c \
        audioinmodule.cpp \
        audioinmodule.h \
        audioinmodule.spec \
        audioinmodule.xpm \
	audioindriver.h $(OSS_sOURCES) $(ALSALIB_sOURCES)

audioinmodule_la_LDFLAGS = -module -avoid-version -no-undefined
audioinmodule_la_LIBADD = $(ALSALIB_lDFLAGS)

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/audiotype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype 

DISTCLEANFILES = audioinmodule.h audioinmodule_auto.c
EXTRA_DIST = audioinmodule.dsp audioinmodule.mak audioinmodule.dep \
	waveindriver.cpp waveindriver.h \
	audiobuffer.c audiobuffer.h
