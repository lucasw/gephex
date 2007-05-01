libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvspiralmodule_auto.c: effectvspiralmodule.spec effectvspiralmodule.h
	$(PLUC) c @srcdir@/effectvspiralmodule.spec

effectvspiralmodule.h: effectvspiralmodule.spec
	$(PLUC) h @srcdir@/effectvspiralmodule.spec

lib_LTLIBRARIES = effectvspiralmodule.la

effectvspiralmodule_la_SOURCES = \
        effectvspiralmodule_auto.c \
        effectvspiralmodule.c \
        effectvspiralmodule.h \
        effectvspiralmodule.spec \
        effectvspiralmodule.xpm

EXTRA_DIST = spiral.c  effectvspiralmodule.dsp effectvspiralmodule.mak effectvspiralmodule.dep

effectvspiralmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvspiralmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvspiralmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/positiontype \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvspiralmodule.h effectvspiralmodule_auto.c
