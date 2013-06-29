libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvagingmodule_auto.c: effectvagingmodule.spec effectvagingmodule.h
	$(PLUC) c @srcdir@/effectvagingmodule.spec

effectvagingmodule.h: effectvagingmodule.spec
	$(PLUC) h @srcdir@/effectvagingmodule.spec

lib_LTLIBRARIES = effectvagingmodule.la

effectvagingmodule_la_SOURCES = \
        effectvagingmodule_auto.c \
        effectvagingmodule.c \
        effectvagingmodule.h \
        effectvagingmodule.spec \
        effectvagingmodule.xpm

EXTRA_DIST = aging.c  effectvagingmodule.dsp effectvagingmodule.mak effectvagingmodule.dep

effectvagingmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvagingmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvagingmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv

DISTCLEANFILES = effectvagingmodule.h effectvagingmodule_auto.c
