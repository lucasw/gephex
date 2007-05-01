libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvrndmmodule_auto.c: effectvrndmmodule.spec effectvrndmmodule.h
	$(PLUC) c @srcdir@/effectvrndmmodule.spec

effectvrndmmodule.h: effectvrndmmodule.spec
	$(PLUC) h @srcdir@/effectvrndmmodule.spec

lib_LTLIBRARIES = effectvrndmmodule.la

effectvrndmmodule_la_SOURCES = \
        effectvrndmmodule_auto.c \
        effectvrndmmodule.c \
        effectvrndmmodule.h \
        effectvrndmmodule.spec \
        effectvrndmmodule.xpm

EXTRA_DIST = rndm.c  effectvrndmmodule.dsp effectvrndmmodule.mak effectvrndmmodule.dep

effectvrndmmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvrndmmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvrndmmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvrndmmodule.h effectvrndmmodule_auto.c
