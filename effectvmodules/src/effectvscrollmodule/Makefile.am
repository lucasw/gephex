libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvscrollmodule_auto.c: effectvscrollmodule.spec effectvscrollmodule.h
	$(PLUC) c @srcdir@/effectvscrollmodule.spec

effectvscrollmodule.h: effectvscrollmodule.spec
	$(PLUC) h @srcdir@/effectvscrollmodule.spec

lib_LTLIBRARIES = effectvscrollmodule.la

effectvscrollmodule_la_SOURCES = \
        effectvscrollmodule_auto.c \
        effectvscrollmodule.c \
        effectvscrollmodule.h \
        effectvscrollmodule.spec \
        effectvscrollmodule.xpm

EXTRA_DIST = scroll.c  effectvscrollmodule.dsp effectvscrollmodule.mak effectvscrollmodule.dep

effectvscrollmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvscrollmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvscrollmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvscrollmodule.h effectvscrollmodule_auto.c
