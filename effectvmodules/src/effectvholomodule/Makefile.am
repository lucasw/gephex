libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

effectvholomodule_auto.c: effectvholomodule.spec effectvholomodule.h
	$(PLUC) c @srcdir@/effectvholomodule.spec

effectvholomodule.h: effectvholomodule.spec
	$(PLUC) h @srcdir@/effectvholomodule.spec

lib_LTLIBRARIES = effectvholomodule.la

effectvholomodule_la_SOURCES = \
        effectvholomodule_auto.c \
        effectvholomodule.c \
	        effectvholomodule.h \
        effectvholomodule.spec \
        effectvholomodule.xpm

EXTRA_DIST = holo.c
#	effectvholomodule.dsp effectvholomodule.mak effectvholomodule.dep

effectvholomodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvholomodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvholomodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES = effectvholomodule.h effectvholomodule_auto.c
