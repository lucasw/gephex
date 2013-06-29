libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

flipflopmodule_auto.c: flipflopmodule.spec flipflopmodule.h
	$(PLUC) c $(srcdir)/flipflopmodule.spec

flipflopmodule.h: flipflopmodule.spec
	$(PLUC) h $(srcdir)/flipflopmodule.spec

lib_LTLIBRARIES = flipflopmodule.la

flipflopmodule_la_SOURCES = flipflopmodule_auto.c                           flipflopmodule.c flipflopmodule.h 			  flipflopmodule.spec 			  flipflopmodule.xpm

flipflopmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype 


 

DISTCLEANFILES = flipflopmodule.h flipflopmodule_auto.c
EXTRA_DIST = flipflopmodule.vcproj flipflopmodule.dsp flipflopmodule.mak flipflopmodule.dep
