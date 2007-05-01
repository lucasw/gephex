libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvnoisemodule_auto.c: effectvnoisemodule.spec effectvnoisemodule.h
	$(PLUC) c @srcdir@/effectvnoisemodule.spec

effectvnoisemodule.h: effectvnoisemodule.spec
	$(PLUC) h @srcdir@/effectvnoisemodule.spec

lib_LTLIBRARIES = effectvnoisemodule.la

effectvnoisemodule_la_SOURCES = \
        effectvnoisemodule_auto.c \
        effectvnoisemodule.c \
        effectvnoisemodule.h \
        effectvnoisemodule.spec \
        effectvnoisemodule.xpm

EXTRA_DIST = noise.c  effectvnoisemodule.dsp effectvnoisemodule.mak effectvnoisemodule.dep

effectvnoisemodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvnoisemodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvnoisemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvnoisemodule.h effectvnoisemodule_auto.c
