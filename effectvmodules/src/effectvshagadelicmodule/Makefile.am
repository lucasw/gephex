libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvshagadelicmodule_auto.c: effectvshagadelicmodule.spec effectvshagadelicmodule.h
	$(PLUC) c @srcdir@/effectvshagadelicmodule.spec

effectvshagadelicmodule.h: effectvshagadelicmodule.spec
	$(PLUC) h @srcdir@/effectvshagadelicmodule.spec

lib_LTLIBRARIES = effectvshagadelicmodule.la

effectvshagadelicmodule_la_SOURCES = \
        effectvshagadelicmodule_auto.c \
        effectvshagadelicmodule.c \
        effectvshagadelicmodule.h \
        effectvshagadelicmodule.spec \
        effectvshagadelicmodule.xpm

EXTRA_DIST = shagadelic.c  effectvshagadelicmodule.dsp effectvshagadelicmodule.mak effectvshagadelicmodule.dep

effectvshagadelicmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvshagadelicmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvshagadelicmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvshagadelicmodule.h effectvshagadelicmodule_auto.c
