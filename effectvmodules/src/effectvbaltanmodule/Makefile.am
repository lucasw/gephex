libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvbaltanmodule_auto.c: effectvbaltanmodule.spec effectvbaltanmodule.h
	$(PLUC) c @srcdir@/effectvbaltanmodule.spec

effectvbaltanmodule.h: effectvbaltanmodule.spec
	$(PLUC) h @srcdir@/effectvbaltanmodule.spec

lib_LTLIBRARIES = effectvbaltanmodule.la

effectvbaltanmodule_la_SOURCES = \
        effectvbaltanmodule_auto.c \
        effectvbaltanmodule.c \
        effectvbaltanmodule.h \
        effectvbaltanmodule.spec \
        effectvbaltanmodule.xpm

EXTRA_DIST = baltan.c  effectvbaltanmodule.dsp effectvbaltanmodule.mak effectvbaltanmodule.dep

effectvbaltanmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvbaltanmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvbaltanmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvbaltanmodule.h effectvbaltanmodule_auto.c
