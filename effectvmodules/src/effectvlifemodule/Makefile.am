libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvlifemodule_auto.c: effectvlifemodule.spec effectvlifemodule.h
	$(PLUC) c @srcdir@/effectvlifemodule.spec

effectvlifemodule.h: effectvlifemodule.spec
	$(PLUC) h @srcdir@/effectvlifemodule.spec

lib_LTLIBRARIES = effectvlifemodule.la

effectvlifemodule_la_SOURCES = \
        effectvlifemodule_auto.c \
        effectvlifemodule.c \
        effectvlifemodule.h \
        effectvlifemodule.spec \
        effectvlifemodule.xpm

EXTRA_DIST = life.c  effectvlifemodule.dsp effectvlifemodule.mak effectvlifemodule.dep

effectvlifemodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvlifemodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvlifemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvlifemodule.h effectvlifemodule_auto.c
