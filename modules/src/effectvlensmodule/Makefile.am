libdir = @libdir@/gephex/modules

PLUC=python $(top_srcdir)/modules/pluc.py

effectvlensmodule_auto.c: effectvlensmodule.spec effectvlensmodule.h
	$(PLUC) c $(srcdir)/effectvlensmodule.spec

effectvlensmodule.h: effectvlensmodule.spec
	$(PLUC) h $(srcdir)/effectvlensmodule.spec

if EFFECTV
effectvlensmodule.c: lens.c

lens.c: ${EFFECTV_SRC_DIR}/effects/lens.c
	cp ${EFFECTV_SRC_DIR}/effects/lens.c @srcdir@
endif

lib_LTLIBRARIES = effectvlensmodule.la

effectvlensmodule_la_SOURCES = \
	effectvlensmodule_auto.c \
	effectvlensmodule.c \
	effectvlensmodule.h \
	effectvlensmodule.spec \
	effectvlensmodule.xpm

effectvlensmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvlensmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvlensmodule_la_LDFLAGS = -module -avoid-version -no-undefined


INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/positiontype \
           -I@srcdir@/../libeffectv \
           -I@srcdir@/../libeffectv/trick


DISTCLEANFILES = effectvlensmodule.h effectvlensmodule_auto.c lens.c
