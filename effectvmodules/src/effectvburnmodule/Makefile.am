libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvburnmodule_auto.c: effectvburnmodule.spec effectvburnmodule.h
	$(PLUC) c @srcdir@/effectvburnmodule.spec

effectvburnmodule.h: effectvburnmodule.spec
	$(PLUC) h @srcdir@/effectvburnmodule.spec

lib_LTLIBRARIES = effectvburnmodule.la

effectvburnmodule_la_SOURCES = \
        effectvburnmodule_auto.c \
        effectvburnmodule.c \
        effectvburnmodule.h \
        effectvburnmodule.spec \
        effectvburnmodule.xpm

EXTRA_DIST = burn.c  effectvburnmodule.dsp effectvburnmodule.mak effectvburnmodule.dep

effectvburnmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvburnmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvburnmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvburnmodule.h effectvburnmodule_auto.c
