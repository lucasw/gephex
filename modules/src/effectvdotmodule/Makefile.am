libdir = @libdir@/gephex/modules

PLUC=python $(top_srcdir)/modules/pluc.py

effectvdotmodule_auto.c: effectvdotmodule.spec effectvdotmodule.h
	$(PLUC) c $(srcdir)/effectvdotmodule.spec

effectvdotmodule.h: effectvdotmodule.spec
	$(PLUC) h $(srcdir)/effectvdotmodule.spec

if EFFECTV
effectvdotmodule.c: dot.c

dot.c: ${EFFECTV_SRC_DIR}/effects/dot.c heart.inc
	cp ${EFFECTV_SRC_DIR}/effects/dot.c @srcdir@

heart.inc: ${EFFECTV_SRC_DIR}/effects/heart.inc
	cp ${EFFECTV_SRC_DIR}/effects/heart.inc @srcdir@
endif

lib_LTLIBRARIES = effectvdotmodule.la

effectvdotmodule_la_SOURCES = \
	effectvdotmodule_auto.c \
	effectvdotmodule.c \
	effectvdotmodule.h \
	effectvdotmodule.spec \
	effectvdotmodule.xpm

effectvdotmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvdotmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvdotmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../libeffectv \
           -I@srcdir@/../libeffectv/trick


DISTCLEANFILES=effectvdotmodule.h effectvdotmodule_auto.c dot.c heart.inc
