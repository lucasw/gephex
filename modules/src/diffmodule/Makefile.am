libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

diffmodule_auto.c: diffmodule.spec diffmodule.h
	$(PLUC) c $(srcdir)/diffmodule.spec

diffmodule.h: diffmodule.spec
	$(PLUC) h $(srcdir)/diffmodule.spec

lib_LTLIBRARIES = diffmodule.la

diffmodule_la_SOURCES = \
	diffmodule_auto.c \
	diffmodule.c \
	diffmodule.h \
	diffmodule.spec \
	diffmodule.xpm

diffmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = diffmodule.h diffmodule_auto.c
EXTRA_DIST = diffmodule.vcproj diffmodule.dsp diffmodule.mak diffmodule.dep
