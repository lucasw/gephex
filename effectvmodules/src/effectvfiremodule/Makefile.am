libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

effectvfiremodule_auto.c: effectvfiremodule.spec effectvfiremodule.h
	$(PLUC) c $(srcdir)/effectvfiremodule.spec

effectvfiremodule.h: effectvfiremodule.spec
	$(PLUC) h $(srcdir)/effectvfiremodule.spec

lib_LTLIBRARIES = effectvfiremodule.la

effectvfiremodule_la_SOURCES = \
	effectvfiremodule_auto.c \
	effectvfiremodule.c \
	effectvfiremodule.h \
	effectvfiremodule.spec \
	effectvfiremodule.xpm

EXTRA_DIST = fire.c  effectvfiremodule.dsp effectvfiremodule.mak effectvfiremodule.dep

effectvfiremodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvfiremodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvfiremodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES=effectvfiremodule.h effectvfiremodule_auto.c
