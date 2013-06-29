libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

isingnoizemodule_auto.c: isingnoizemodule.spec isingnoizemodule.h
	$(PLUC) c $(srcdir)/isingnoizemodule.spec

isingnoizemodule.h: isingnoizemodule.spec
	$(PLUC) h $(srcdir)/isingnoizemodule.spec

lib_LTLIBRARIES = isingnoizemodule.la

isingnoizemodule_la_SOURCES = isingnoizemodule_auto.c                           isingnoizemodule.c isingnoizemodule.h 			  isingnoizemodule.spec 			  isingnoizemodule.xpm

isingnoizemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../util/src/misc \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype 


 

DISTCLEANFILES = isingnoizemodule.h isingnoizemodule_auto.c
EXTRA_DIST = isingnoizemodule.vcproj isingnoizemodule.dsp isingnoizemodule.mak isingnoizemodule.dep
