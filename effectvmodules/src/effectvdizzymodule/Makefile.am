libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvdizzymodule_auto.c: effectvdizzymodule.spec effectvdizzymodule.h
	$(PLUC) c @srcdir@/effectvdizzymodule.spec

effectvdizzymodule.h: effectvdizzymodule.spec
	$(PLUC) h @srcdir@/effectvdizzymodule.spec

lib_LTLIBRARIES = effectvdizzymodule.la

effectvdizzymodule_la_SOURCES = \
        effectvdizzymodule_auto.c \
        effectvdizzymodule.c \
        effectvdizzymodule.h \
        effectvdizzymodule.spec \
        effectvdizzymodule.xpm

EXTRA_DIST = dizzy.c  effectvdizzymodule.dsp effectvdizzymodule.mak effectvdizzymodule.dep

effectvdizzymodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvdizzymodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvdizzymodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvdizzymodule.h effectvdizzymodule_auto.c
