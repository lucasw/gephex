libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvdiffmodule_auto.c: effectvdiffmodule.spec effectvdiffmodule.h
	$(PLUC) c @srcdir@/effectvdiffmodule.spec

effectvdiffmodule.h: effectvdiffmodule.spec
	$(PLUC) h @srcdir@/effectvdiffmodule.spec

lib_LTLIBRARIES = effectvdiffmodule.la

effectvdiffmodule_la_SOURCES = \
        effectvdiffmodule_auto.c \
        effectvdiffmodule.c \
        effectvdiffmodule.h \
        effectvdiffmodule.spec \
        effectvdiffmodule.xpm

EXTRA_DIST = diff.c  effectvdiffmodule.dsp effectvdiffmodule.mak effectvdiffmodule.dep

effectvdiffmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvdiffmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvdiffmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvdiffmodule.h effectvdiffmodule_auto.c
