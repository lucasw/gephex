libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvmosaicmodule_auto.c: effectvmosaicmodule.spec effectvmosaicmodule.h
	$(PLUC) c @srcdir@/effectvmosaicmodule.spec

effectvmosaicmodule.h: effectvmosaicmodule.spec
	$(PLUC) h @srcdir@/effectvmosaicmodule.spec

lib_LTLIBRARIES = effectvmosaicmodule.la

effectvmosaicmodule_la_SOURCES = \
        effectvmosaicmodule_auto.c \
        effectvmosaicmodule.c \
        effectvmosaicmodule.h \
        effectvmosaicmodule.spec \
        effectvmosaicmodule.xpm

EXTRA_DIST = mosaic.c  effectvmosaicmodule.dsp effectvmosaicmodule.mak effectvmosaicmodule.dep

effectvmosaicmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvmosaicmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvmosaicmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvmosaicmodule.h effectvmosaicmodule_auto.c
