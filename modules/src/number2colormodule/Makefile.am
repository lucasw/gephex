libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

number2colormodule_auto.c: number2colormodule.spec number2colormodule.h
	$(PLUC) c $(srcdir)/number2colormodule.spec

number2colormodule.h: number2colormodule.spec
	$(PLUC) h $(srcdir)/number2colormodule.spec

lib_LTLIBRARIES = number2colormodule.la

number2colormodule_la_SOURCES = number2colormodule_auto.c                           number2colormodule.c number2colormodule.h 			  number2colormodule.spec 			  number2colormodule.xpm

number2colormodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/rgbtype 


 

DISTCLEANFILES = number2colormodule.h number2colormodule_auto.c
EXTRA_DIST = number2colormodule.vcproj number2colormodule.dsp number2colormodule.mak number2colormodule.dep
