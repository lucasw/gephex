libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvnervousmodule_auto.c: effectvnervousmodule.spec effectvnervousmodule.h
	$(PLUC) c @srcdir@/effectvnervousmodule.spec

effectvnervousmodule.h: effectvnervousmodule.spec
	$(PLUC) h @srcdir@/effectvnervousmodule.spec

lib_LTLIBRARIES = effectvnervousmodule.la

effectvnervousmodule_la_SOURCES = \
        effectvnervousmodule_auto.c \
        effectvnervousmodule.c \
        effectvnervousmodule.h \
        effectvnervousmodule.spec \
        effectvnervousmodule.xpm

EXTRA_DIST = nervous.c  effectvnervousmodule.dsp effectvnervousmodule.mak effectvnervousmodule.dep

effectvnervousmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvnervousmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvnervousmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvnervousmodule.h effectvnervousmodule_auto.c
