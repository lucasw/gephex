libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvpupmodule_auto.c: effectvpupmodule.spec effectvpupmodule.h
	$(PLUC) c @srcdir@/effectvpupmodule.spec

effectvpupmodule.h: effectvpupmodule.spec
	$(PLUC) h @srcdir@/effectvpupmodule.spec

lib_LTLIBRARIES = effectvpupmodule.la

effectvpupmodule_la_SOURCES = \
        effectvpupmodule_auto.c \
        effectvpupmodule.c \
        effectvpupmodule.h \
        effectvpupmodule.spec \
        effectvpupmodule.xpm

EXTRA_DIST = pup.c  effectvpupmodule.dsp effectvpupmodule.mak effectvpupmodule.dep

effectvpupmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvpupmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvpupmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvpupmodule.h effectvpupmodule_auto.c
