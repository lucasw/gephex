libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvwarholmodule_auto.c: effectvwarholmodule.spec effectvwarholmodule.h
	$(PLUC) c @srcdir@/effectvwarholmodule.spec

effectvwarholmodule.h: effectvwarholmodule.spec
	$(PLUC) h @srcdir@/effectvwarholmodule.spec

lib_LTLIBRARIES = effectvwarholmodule.la

effectvwarholmodule_la_SOURCES = \
        effectvwarholmodule_auto.c \
        effectvwarholmodule.c \
        effectvwarholmodule.h \
        effectvwarholmodule.spec \
        effectvwarholmodule.xpm

EXTRA_DIST = warhol.c  effectvwarholmodule.dsp effectvwarholmodule.mak effectvwarholmodule.dep

effectvwarholmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvwarholmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvwarholmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvwarholmodule.h effectvwarholmodule_auto.c
