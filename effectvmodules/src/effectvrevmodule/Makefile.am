libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvrevmodule_auto.c: effectvrevmodule.spec effectvrevmodule.h
	$(PLUC) c @srcdir@/effectvrevmodule.spec

effectvrevmodule.h: effectvrevmodule.spec
	$(PLUC) h @srcdir@/effectvrevmodule.spec

lib_LTLIBRARIES = effectvrevmodule.la

effectvrevmodule_la_SOURCES = \
        effectvrevmodule_auto.c \
        effectvrevmodule.c \
        effectvrevmodule.h \
        effectvrevmodule.spec \
        effectvrevmodule.xpm

EXTRA_DIST = rev.c  effectvrevmodule.dsp effectvrevmodule.mak effectvrevmodule.dep

effectvrevmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvrevmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvrevmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvrevmodule.h effectvrevmodule_auto.c
