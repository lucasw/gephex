libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvmatrixmodule_auto.c: effectvmatrixmodule.spec effectvmatrixmodule.h
	$(PLUC) c @srcdir@/effectvmatrixmodule.spec

effectvmatrixmodule.h: effectvmatrixmodule.spec
	$(PLUC) h @srcdir@/effectvmatrixmodule.spec

lib_LTLIBRARIES = effectvmatrixmodule.la

effectvmatrixmodule_la_SOURCES = \
        effectvmatrixmodule_auto.c \
        effectvmatrixmodule.c \
        effectvmatrixmodule.h \
        effectvmatrixmodule.spec \
        effectvmatrixmodule.xpm

EXTRA_DIST = matrix.c matrixFont.xpm  effectvmatrixmodule.dsp effectvmatrixmodule.mak effectvmatrixmodule.dep

effectvmatrixmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvmatrixmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvmatrixmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvmatrixmodule.h effectvmatrixmodule_auto.c
