libdir = @libdir@/gephex/modules

PLUC=python $(top_srcdir)/modules/pluc.py

effectvpuzzlemodule_auto.c: effectvpuzzlemodule.spec effectvpuzzlemodule.h
	$(PLUC) c $(srcdir)/effectvpuzzlemodule.spec

effectvpuzzlemodule.h: effectvpuzzlemodule.spec
	$(PLUC) h $(srcdir)/effectvpuzzlemodule.spec

if EFFECTV
effectvpuzzlemodule.c: puzzle.c

puzzle.c: ${EFFECTV_SRC_DIR}/effects/puzzle.c
	cp ${EFFECTV_SRC_DIR}/effects/puzzle.c @srcdir@
endif

lib_LTLIBRARIES = effectvpuzzlemodule.la

effectvpuzzlemodule_la_SOURCES = \
	effectvpuzzlemodule_auto.c \
	effectvpuzzlemodule.c \
	effectvpuzzlemodule.h \
	effectvpuzzlemodule.spec \
	effectvpuzzlemodule.xpm

effectvpuzzlemodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvpuzzlemodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvpuzzlemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../libeffectv \
           -I@srcdir@/../libeffectv/trick

DISTCLEANFILES = effectvpuzzlemodule.h effectvpuzzlemodule_auto.c puzzle.c
