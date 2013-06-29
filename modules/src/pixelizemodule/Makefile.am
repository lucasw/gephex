libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

pixelizemodule_auto.c: pixelizemodule.spec pixelizemodule.h
	$(PLUC) c @srcdir@/pixelizemodule.spec

pixelizemodule.h: pixelizemodule.spec
	$(PLUC) h @srcdir@/pixelizemodule.spec

lib_LTLIBRARIES = pixelizemodule.la

pixelizemodule_la_SOURCES = \
        pixelizemodule_auto.c \
        pixelizemodule.c \
        pixelizemodule.h \
        pixelizemodule.spec \
        pixelizemodule.xpm

pixelizemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = pixelizemodule.h pixelizemodule_auto.c
EXTRA_DIST = pixelizemodule.vcproj pixelizemodule.dsp pixelizemodule.mak pixelizemodule.dep
