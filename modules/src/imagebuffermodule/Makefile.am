libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

imagebuffermodule_auto.c: imagebuffermodule.spec imagebuffermodule.h
	$(PLUC) c $(srcdir)/imagebuffermodule.spec

imagebuffermodule.h: imagebuffermodule.spec
	$(PLUC) h $(srcdir)/imagebuffermodule.spec

lib_LTLIBRARIES = imagebuffermodule.la

imagebuffermodule_la_SOURCES = imagebuffermodule_auto.c                           imagebuffermodule.c imagebuffermodule.h 			  imagebuffermodule.spec 			  imagebuffermodule.xpm

imagebuffermodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype 


 

DISTCLEANFILES = imagebuffermodule.h imagebuffermodule_auto.c
EXTRA_DIST = imagebuffermodule.vcproj imagebuffermodule.dsp imagebuffermodule.mak imagebuffermodule.dep
