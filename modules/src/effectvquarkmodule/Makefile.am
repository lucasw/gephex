libdir = @libdir@/gephex/modules

PLUC=python @top_srcdir@/modules/pluc.py

effectvquarkmodule_auto.c: effectvquarkmodule.spec effectvquarkmodule.h
	$(PLUC) c @srcdir@/effectvquarkmodule.spec

effectvquarkmodule.h: effectvquarkmodule.spec
	$(PLUC) h @srcdir@/effectvquarkmodule.spec

if EFFECTV
effectvquarkmodule.c: quark.c

quark.c: ${EFFECTV_SRC_DIR}/effects/quark.c
	cp ${EFFECTV_SRC_DIR}/effects/quark.c @srcdir@
endif 

lib_LTLIBRARIES = effectvquarkmodule.la

effectvquarkmodule_la_SOURCES = \
        effectvquarkmodule_auto.c \
        effectvquarkmodule.c \
        effectvquarkmodule.h \
        effectvquarkmodule.spec \
        effectvquarkmodule.xpm

effectvquarkmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvquarkmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvquarkmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv \
           -I@srcdir@/../libeffectv/trick

DISTCLEANFILES = effectvquarkmodule.h effectvquarkmodule_auto.c quark.c
