libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvquarkmodule_auto.c: effectvquarkmodule.spec effectvquarkmodule.h
	$(PLUC) c @srcdir@/effectvquarkmodule.spec

effectvquarkmodule.h: effectvquarkmodule.spec
	$(PLUC) h @srcdir@/effectvquarkmodule.spec

lib_LTLIBRARIES = effectvquarkmodule.la

effectvquarkmodule_la_SOURCES = \
        effectvquarkmodule_auto.c \
        effectvquarkmodule.c \
        effectvquarkmodule.h \
        effectvquarkmodule.spec \
        effectvquarkmodule.xpm

EXTRA_DIST = quark.c  effectvquarkmodule.dsp effectvquarkmodule.mak effectvquarkmodule.dep

effectvquarkmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvquarkmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvquarkmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvquarkmodule.h effectvquarkmodule_auto.c
