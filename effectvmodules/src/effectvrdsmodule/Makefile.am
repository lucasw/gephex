libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvrdsmodule_auto.c: effectvrdsmodule.spec effectvrdsmodule.h
	$(PLUC) c @srcdir@/effectvrdsmodule.spec

effectvrdsmodule.h: effectvrdsmodule.spec
	$(PLUC) h @srcdir@/effectvrdsmodule.spec

lib_LTLIBRARIES = effectvrdsmodule.la

effectvrdsmodule_la_SOURCES = \
        effectvrdsmodule_auto.c \
        effectvrdsmodule.c \
        effectvrdsmodule.h \
        effectvrdsmodule.spec \
        effectvrdsmodule.xpm

EXTRA_DIST = rds.c  effectvrdsmodule.dsp effectvrdsmodule.mak effectvrdsmodule.dep

effectvrdsmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvrdsmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvrdsmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvrdsmodule.h effectvrdsmodule_auto.c
