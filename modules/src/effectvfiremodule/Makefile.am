libdir = @libdir@/gephex/modules

PLUC=python $(top_srcdir)/modules/pluc.py

effectvfiremodule_auto.c: effectvfiremodule.spec effectvfiremodule.h
	$(PLUC) c $(srcdir)/effectvfiremodule.spec

effectvfiremodule.h: effectvfiremodule.spec
	$(PLUC) h $(srcdir)/effectvfiremodule.spec

if EFFECTV
effectvfiremodule.c: fire.c

fire.c: ${EFFECTV_SRC_DIR}/effects/fire.c
	cp ${EFFECTV_SRC_DIR}/effects/fire.c @srcdir@
endif

lib_LTLIBRARIES = effectvfiremodule.la

effectvfiremodule_la_SOURCES = \
	effectvfiremodule_auto.c \
	effectvfiremodule.c \
	effectvfiremodule.h \
	effectvfiremodule.spec \
	effectvfiremodule.xpm

effectvfiremodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvfiremodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvfiremodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../libeffectv \
           -I@srcdir@/../libeffectv/trick


DISTCLEANFILES=effectvfiremodule.h effectvfiremodule_auto.c fire.c
