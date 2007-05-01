libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvtransformmodule_auto.c: effectvtransformmodule.spec effectvtransformmodule.h
	$(PLUC) c @srcdir@/effectvtransformmodule.spec

effectvtransformmodule.h: effectvtransformmodule.spec
	$(PLUC) h @srcdir@/effectvtransformmodule.spec

lib_LTLIBRARIES = effectvtransformmodule.la

effectvtransformmodule_la_SOURCES = \
        effectvtransformmodule_auto.c \
        effectvtransformmodule.c \
        effectvtransformmodule.h \
        effectvtransformmodule.spec \
        effectvtransformmodule.xpm

EXTRA_DIST = transform.c  effectvtransformmodule.dsp effectvtransformmodule.mak effectvtransformmodule.dep

effectvtransformmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvtransformmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvtransformmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvtransformmodule.h effectvtransformmodule_auto.c
