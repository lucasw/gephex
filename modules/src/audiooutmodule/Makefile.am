libdir = @libdir@/gephex/modules

PLUC=python @top_srcdir@/modules/pluc.py

audiooutmodule_auto.c: audiooutmodule.spec audiooutmodule.h
	$(PLUC) c @srcdir@/audiooutmodule.spec

audiooutmodule.h: audiooutmodule.spec
	$(PLUC) h @srcdir@/audiooutmodule.spec

lib_LTLIBRARIES = audiooutmodule.la


if HAVE_ASOUNDLIB
ALSALIB_sOURCES = \
        alsaoutdriver.cpp \
	alsaoutdriver.h
ALSALIB_lDFLAGS = -lasound
endif

if HAVE_OSS
OSS_sOURCES = \
	ossoutdriver.cpp \
	ossoutdriver.h
endif


audiooutmodule_la_SOURCES = \
        audiooutmodule_auto.c \
        audiooutmodule.cpp \
        audiooutmodule.h \
        audiooutmodule.spec \
        audiooutmodule.xpm \
	audiooutdriver.h $(OSS_sOURCES) $(ALSALIB_sOURCES)

audiooutmodule_la_LDFLAGS = -module -avoid-version -no-undefined
audiooutmodule_la_LIBADD = $(ALSALIB_lDFLAGS)

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/audiotype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype 


DISTCLEANFILES = audiooutmodule.h audiooutmodule_auto.c
