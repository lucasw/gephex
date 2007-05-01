libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

ifsmodule_auto.c: ifsmodule.spec ifsmodule.h
	$(PLUC) c $(srcdir)/ifsmodule.spec

ifsmodule.h: ifsmodule.spec
	$(PLUC) h $(srcdir)/ifsmodule.spec

lib_LTLIBRARIES = ifsmodule.la

ifsmodule_la_SOURCES =	ifsmodule_auto.c \
			ifsmodule.cpp \
			ifsmodule.h \
			ifsmodule.spec \
			ifsmodule.xpm

ifsmodule_la_LDFLAGS = -module -avoid-version -no-undefined
ifsmodule_la_LIBADD = -lstdc++

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../util/src/misc \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/ifstype \
           -I@srcdir@/../../../types/src/numbertype 


 

DISTCLEANFILES = ifsmodule.h ifsmodule_auto.c
EXTRA_DIST = ifsmodule.vcproj ifsmodule.dsp ifsmodule.mak ifsmodule.dep
