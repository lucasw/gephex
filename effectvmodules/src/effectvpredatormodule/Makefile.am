libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvpredatormodule_auto.c: effectvpredatormodule.spec effectvpredatormodule.h
	$(PLUC) c @srcdir@/effectvpredatormodule.spec

effectvpredatormodule.h: effectvpredatormodule.spec
	$(PLUC) h @srcdir@/effectvpredatormodule.spec

lib_LTLIBRARIES = effectvpredatormodule.la

effectvpredatormodule_la_SOURCES = \
        effectvpredatormodule_auto.c \
        effectvpredatormodule.c \
        effectvpredatormodule.h \
        effectvpredatormodule.spec \
        effectvpredatormodule.xpm

EXTRA_DIST = predator.c  effectvpredatormodule.dsp effectvpredatormodule.mak effectvpredatormodule.dep

effectvpredatormodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvpredatormodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvpredatormodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvpredatormodule.h effectvpredatormodule_auto.c
