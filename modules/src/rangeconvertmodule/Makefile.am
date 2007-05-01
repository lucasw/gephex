libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

rangeconvertmodule_auto.c: rangeconvertmodule.spec rangeconvertmodule.h
	$(PLUC) c $(srcdir)/rangeconvertmodule.spec

rangeconvertmodule.h: rangeconvertmodule.spec
	$(PLUC) h $(srcdir)/rangeconvertmodule.spec

lib_LTLIBRARIES = rangeconvertmodule.la

rangeconvertmodule_la_SOURCES = \
	rangeconvertmodule_auto.c \
	rangeconvertmodule.c \
	rangeconvertmodule.h \
	rangeconvertmodule.spec \
	rangeconvertmodule.xpm

rangeconvertmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype 


 

DISTCLEANFILES = rangeconvertmodule.h rangeconvertmodule_auto.c
EXTRA_DIST = rangeconvertmodule.vcproj rangeconvertmodule.dsp rangeconvertmodule.mak rangeconvertmodule.dep
