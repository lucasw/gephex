libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

effectvedgemodule_auto.c: effectvedgemodule.spec effectvedgemodule.h
	$(PLUC) c $(srcdir)/effectvedgemodule.spec

effectvedgemodule.h: effectvedgemodule.spec
	$(PLUC) h $(srcdir)/effectvedgemodule.spec


lib_LTLIBRARIES = effectvedgemodule.la

effectvedgemodule_la_SOURCES = \
	effectvedgemodule_auto.c \
	effectvedgemodule.c \
	effectvedgemodule.h \
	effectvedgemodule.spec \
	effectvedgemodule.xpm

EXTRA_DIST = edge.c  effectvedgemodule.dsp effectvedgemodule.mak effectvedgemodule.dep

effectvedgemodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvedgemodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvedgemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvedgemodule.h effectvedgemodule_auto.c
