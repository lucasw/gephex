libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvdicemodule_auto.c: effectvdicemodule.spec effectvdicemodule.h
	$(PLUC) c @srcdir@/effectvdicemodule.spec

effectvdicemodule.h: effectvdicemodule.spec
	$(PLUC) h @srcdir@/effectvdicemodule.spec

lib_LTLIBRARIES = effectvdicemodule.la

effectvdicemodule_la_SOURCES = \
        effectvdicemodule_auto.c \
        effectvdicemodule.c \
        effectvdicemodule.h \
        effectvdicemodule.spec \
        effectvdicemodule.xpm

EXTRA_DIST = dice.c  effectvdicemodule.dsp effectvdicemodule.mak effectvdicemodule.dep

effectvdicemodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvdicemodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvdicemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvdicemodule.h effectvdicemodule_auto.c
