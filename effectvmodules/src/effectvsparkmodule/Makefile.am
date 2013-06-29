libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

effectvsparkmodule_auto.c: effectvsparkmodule.spec effectvsparkmodule.h
	$(PLUC) c $(srcdir)/effectvsparkmodule.spec

effectvsparkmodule.h: effectvsparkmodule.spec
	$(PLUC) h $(srcdir)/effectvsparkmodule.spec

lib_LTLIBRARIES = effectvsparkmodule.la

effectvsparkmodule_la_SOURCES = \
	effectvsparkmodule_auto.c \
	effectvsparkmodule.c \
	effectvsparkmodule.h \
	effectvsparkmodule.spec \
	effectvsparkmodule.xpm

EXTRA_DIST = spark.c  effectvsparkmodule.dsp effectvsparkmodule.mak effectvsparkmodule.dep

effectvsparkmodule_la_LIBADD = -leffectv -L@builddir@/../libeffectv

effectvsparkmodule_la_DEPENDENCIES = @builddir@/../libeffectv/libeffectv.a

effectvsparkmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../libeffectv


DISTCLEANFILES=effectvsparkmodule.h effectvsparkmodule_auto.c
