libdir = @libdir@/gephex/modules

PLUC=python @top_srcdir@/modules/pluc.py

effectvagingmodule_auto.c: effectvagingmodule.spec effectvagingmodule.h
	$(PLUC) c @srcdir@/effectvagingmodule.spec

effectvagingmodule.h: effectvagingmodule.spec
	$(PLUC) h @srcdir@/effectvagingmodule.spec

if EFFECTV
effectvagingmodule.c: aging.c

aging.c: ${EFFECTV_SRC_DIR}/effects/aging.c
	cp ${EFFECTV_SRC_DIR}/effects/aging.c @srcdir@
endif 

lib_LTLIBRARIES = effectvagingmodule.la

effectvagingmodule_la_SOURCES = \
        effectvagingmodule_auto.c \
        effectvagingmodule.c \
        effectvagingmodule.h \
        effectvagingmodule.spec \
        effectvagingmodule.xpm

effectvagingmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvagingmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvagingmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv \
           -I@srcdir@/../libeffectv/trick

DISTCLEANFILES = effectvagingmodule.h effectvagingmodule_auto.c aging.c
