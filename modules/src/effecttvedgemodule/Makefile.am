libdir = @libdir@/gephex/modules

PLUC=python $(top_srcdir)/modules/pluc.py

effectvedgemodule_auto.c: effectvedgemodule.spec effectvedgemodule.h
	$(PLUC) c $(srcdir)/effectvedgemodule.spec

effectvedgemodule.h: effectvedgemodule.spec
	$(PLUC) h $(srcdir)/effectvedgemodule.spec


if EFFECTV
effectvedgemodule.c: edge.c

edge.c: ${EFFECTV_SRC_DIR}/effects/edge.c
	cp ${EFFECTV_SRC_DIR}/effects/edge.c @srcdir@
endif 

lib_LTLIBRARIES = effectvedgemodule.la

effectvedgemodule_la_SOURCES = \
	effectvedgemodule_auto.c \
	effectvedgemodule.c \
	effectvedgemodule.h \
	effectvedgemodule.spec \
	effectvedgemodule.xpm

effectvedgemodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvedgemodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvedgemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv \
           -I@srcdir@/../libeffectv/trick


DISTCLEANFILES = effectvedgemodule.h effectvedgemodule_auto.c edge.c
