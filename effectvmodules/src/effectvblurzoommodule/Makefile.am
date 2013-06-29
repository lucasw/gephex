libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvblurzoommodule_auto.c: effectvblurzoommodule.spec effectvblurzoommodule.h
	$(PLUC) c @srcdir@/effectvblurzoommodule.spec

effectvblurzoommodule.h: effectvblurzoommodule.spec
	$(PLUC) h @srcdir@/effectvblurzoommodule.spec

lib_LTLIBRARIES = effectvblurzoommodule.la

effectvblurzoommodule_la_SOURCES = \
        effectvblurzoommodule_auto.c \
        effectvblurzoommodule.c \
        effectvblurzoommodule.h \
        effectvblurzoommodule.spec \
        effectvblurzoommodule.xpm

EXTRA_DIST = blurzoom.c  effectvblurzoommodule.dsp effectvblurzoommodule.mak effectvblurzoommodule.dep

effectvblurzoommodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvblurzoommodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvblurzoommodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvblurzoommodule.h effectvblurzoommodule_auto.c
