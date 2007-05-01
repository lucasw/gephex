libdir = @gphx_module_lib_dir@

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

if OS_DARWIN
MAC_sOURCES = \
	coreaudiodriver.cpp \
	coreaudiodriver.h \
	coreaudioconvert.cpp \
	coreaudioconvert.h \
	coreaudiohelpers.cpp \
	coreaudiohelpers.h

MAC_lDFLAGS = -framework CoreAudio -framework AudioToolBox
endif

if OS_WINDOWS
W32_sOURCES = \
	audiobuffer.c \
	audiobuffer.h \
	waveindriver.cpp \
	waveindriver.h
endif

audioinmodule_la_SOURCES = \
        audioinmodule_auto.c \
        audioinmodule.cpp \
        audioinmodule.h \
	a_cvt.cpp \
	a_cvt.h \
        audioinmodule.spec \
        audioinmodule.xpm \
	audioindriver.h $(OSS_sOURCES) $(ALSALIB_sOURCES) $(MAC_sOURCES) $(W32_sOURCES)

audioinmodule_la_LDFLAGS = -module -avoid-version -no-undefined $(MAC_lDFLAGS)
audioinmodule_la_LIBADD = $(ALSALIB_lDFLAGS)

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/audiotype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype 

DISTCLEANFILES = audioinmodule.h audioinmodule_auto.c
EXTRA_DIST = audioinmodule.vcproj audioinmodule.dsp audioinmodule.mak audioinmodule.dep
