libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvripplemodule_auto.c: effectvripplemodule.spec effectvripplemodule.h
	$(PLUC) c @srcdir@/effectvripplemodule.spec

effectvripplemodule.h: effectvripplemodule.spec
	$(PLUC) h @srcdir@/effectvripplemodule.spec

lib_LTLIBRARIES = effectvripplemodule.la

effectvripplemodule_la_SOURCES = \
        effectvripplemodule_auto.c \
        effectvripplemodule.c \
        effectvripplemodule.h \
        effectvripplemodule.spec \
        effectvripplemodule.xpm

EXTRA_DIST = ripple.c  effectvripplemodule.dsp effectvripplemodule.mak effectvripplemodule.dep

effectvripplemodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvripplemodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvripplemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvripplemodule.h effectvripplemodule_auto.c
