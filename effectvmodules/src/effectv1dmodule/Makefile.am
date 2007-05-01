libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectv1dmodule_auto.c: effectv1dmodule.spec effectv1dmodule.h
	$(PLUC) c @srcdir@/effectv1dmodule.spec

effectv1dmodule.h: effectv1dmodule.spec
	$(PLUC) h @srcdir@/effectv1dmodule.spec

lib_LTLIBRARIES = effectv1dmodule.la

effectv1dmodule_la_SOURCES = \
        effectv1dmodule_auto.c \
        effectv1dmodule.c \
        effectv1dmodule.h \
        effectv1dmodule.spec \
        effectv1dmodule.xpm

EXTRA_DIST = 1d.c  effectv1dmodule.dsp effectv1dmodule.mak effectv1dmodule.dep

effectv1dmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectv1dmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectv1dmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../libeffectv

DISTCLEANFILES = effectv1dmodule.h effectv1dmodule_auto.c
