libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvchameleonmodule_auto.c: effectvchameleonmodule.spec effectvchameleonmodule.h
	$(PLUC) c @srcdir@/effectvchameleonmodule.spec

effectvchameleonmodule.h: effectvchameleonmodule.spec
	$(PLUC) h @srcdir@/effectvchameleonmodule.spec

lib_LTLIBRARIES = effectvchameleonmodule.la

effectvchameleonmodule_la_SOURCES = \
        effectvchameleonmodule_auto.c \
        effectvchameleonmodule.c \
        effectvchameleonmodule.h \
        effectvchameleonmodule.spec \
        effectvchameleonmodule.xpm

EXTRA_DIST = chameleon.c  effectvchameleonmodule.dsp effectvchameleonmodule.mak effectvchameleonmodule.dep

effectvchameleonmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvchameleonmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvchameleonmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvchameleonmodule.h effectvchameleonmodule_auto.c
