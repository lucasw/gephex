libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvsimuramodule_auto.c: effectvsimuramodule.spec effectvsimuramodule.h
	$(PLUC) c @srcdir@/effectvsimuramodule.spec

effectvsimuramodule.h: effectvsimuramodule.spec
	$(PLUC) h @srcdir@/effectvsimuramodule.spec

lib_LTLIBRARIES = effectvsimuramodule.la

effectvsimuramodule_la_SOURCES = \
        effectvsimuramodule_auto.c \
        effectvsimuramodule.c \
        effectvsimuramodule.h \
        effectvsimuramodule.spec \
        effectvsimuramodule.xpm

EXTRA_DIST = simura.c  effectvsimuramodule.dsp effectvsimuramodule.mak effectvsimuramodule.dep

effectvsimuramodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvsimuramodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvsimuramodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvsimuramodule.h effectvsimuramodule_auto.c
