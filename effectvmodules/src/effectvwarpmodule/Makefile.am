libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvwarpmodule_auto.c: effectvwarpmodule.spec effectvwarpmodule.h
	$(PLUC) c @srcdir@/effectvwarpmodule.spec

effectvwarpmodule.h: effectvwarpmodule.spec
	$(PLUC) h @srcdir@/effectvwarpmodule.spec

lib_LTLIBRARIES = effectvwarpmodule.la

effectvwarpmodule_la_SOURCES = \
        effectvwarpmodule_auto.c \
        effectvwarpmodule.c \
        effectvwarpmodule.h \
        effectvwarpmodule.spec \
        effectvwarpmodule.xpm

EXTRA_DIST = warp.c  effectvwarpmodule.dsp effectvwarpmodule.mak effectvwarpmodule.dep

effectvwarpmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvwarpmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvwarpmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvwarpmodule.h effectvwarpmodule_auto.c
