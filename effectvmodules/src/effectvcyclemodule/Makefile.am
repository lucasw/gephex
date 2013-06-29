libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvcyclemodule_auto.c: effectvcyclemodule.spec effectvcyclemodule.h
	$(PLUC) c @srcdir@/effectvcyclemodule.spec

effectvcyclemodule.h: effectvcyclemodule.spec
	$(PLUC) h @srcdir@/effectvcyclemodule.spec

lib_LTLIBRARIES = effectvcyclemodule.la

effectvcyclemodule_la_SOURCES = \
        effectvcyclemodule_auto.c \
        effectvcyclemodule.c \
        effectvcyclemodule.h \
        effectvcyclemodule.spec \
        effectvcyclemodule.xpm

EXTRA_DIST = cycle.c  effectvcyclemodule.dsp effectvcyclemodule.mak effectvcyclemodule.dep

effectvcyclemodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvcyclemodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvcyclemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv

DISTCLEANFILES = effectvcyclemodule.h effectvcyclemodule_auto.c
