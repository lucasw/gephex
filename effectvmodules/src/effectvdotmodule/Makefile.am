libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

effectvdotmodule_auto.c: effectvdotmodule.spec effectvdotmodule.h
	$(PLUC) c $(srcdir)/effectvdotmodule.spec

effectvdotmodule.h: effectvdotmodule.spec
	$(PLUC) h $(srcdir)/effectvdotmodule.spec

lib_LTLIBRARIES = effectvdotmodule.la

effectvdotmodule_la_SOURCES = \
	effectvdotmodule_auto.c \
	effectvdotmodule.c \
	effectvdotmodule.h \
	effectvdotmodule.spec \
	effectvdotmodule.xpm

EXTRA_DIST = heart.inc dot.c  effectvdotmodule.dsp effectvdotmodule.mak effectvdotmodule.dep

effectvdotmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvdotmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvdotmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES=effectvdotmodule.h effectvdotmodule_auto.c
