libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

ifsxfadermodule_auto.c: ifsxfadermodule.spec ifsxfadermodule.h
	$(PLUC) c $(srcdir)/ifsxfadermodule.spec

ifsxfadermodule.h: ifsxfadermodule.spec
	$(PLUC) h $(srcdir)/ifsxfadermodule.spec

lib_LTLIBRARIES = ifsxfadermodule.la

ifsxfadermodule_la_SOURCES = ifsxfadermodule_auto.c                           ifsxfadermodule.cpp ifsxfadermodule.h 			  ifsxfadermodule.spec 			  ifsxfadermodule.xpm

ifsxfadermodule_la_LDFLAGS = -module -avoid-version -no-undefined
ifsxfadermodule_la_LIBADD = -lstdc++

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/ifstype \
           -I@srcdir@/../../../types/src/numbertype 


 

DISTCLEANFILES = ifsxfadermodule.h ifsxfadermodule_auto.c
EXTRA_DIST = ifsxfadermodule.vcproj ifsxfadermodule.dsp ifsxfadermodule.mak ifsxfadermodule.dep
