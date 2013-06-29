libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvstreakmodule_auto.c: effectvstreakmodule.spec effectvstreakmodule.h
	$(PLUC) c @srcdir@/effectvstreakmodule.spec

effectvstreakmodule.h: effectvstreakmodule.spec
	$(PLUC) h @srcdir@/effectvstreakmodule.spec

lib_LTLIBRARIES = effectvstreakmodule.la

effectvstreakmodule_la_SOURCES = \
        effectvstreakmodule_auto.c \
        effectvstreakmodule.c \
        effectvstreakmodule.h \
        effectvstreakmodule.spec \
        effectvstreakmodule.xpm

EXTRA_DIST = streak.c  effectvstreakmodule.dsp effectvstreakmodule.mak effectvstreakmodule.dep

effectvstreakmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvstreakmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvstreakmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvstreakmodule.h effectvstreakmodule_auto.c
