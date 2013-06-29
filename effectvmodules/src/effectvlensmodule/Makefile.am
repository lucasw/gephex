libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

effectvlensmodule_auto.c: effectvlensmodule.spec effectvlensmodule.h
	$(PLUC) c $(srcdir)/effectvlensmodule.spec

effectvlensmodule.h: effectvlensmodule.spec
	$(PLUC) h $(srcdir)/effectvlensmodule.spec

lib_LTLIBRARIES = effectvlensmodule.la

effectvlensmodule_la_SOURCES = \
	effectvlensmodule_auto.c \
	effectvlensmodule.c \
	effectvlensmodule.h \
	effectvlensmodule.spec \
	effectvlensmodule.xpm

EXTRA_DIST = lens.c  effectvlensmodule.dsp effectvlensmodule.mak effectvlensmodule.dep

effectvlensmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvlensmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvlensmodule_la_LDFLAGS = -module -avoid-version -no-undefined


INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/positiontype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvlensmodule.h effectvlensmodule_auto.c
