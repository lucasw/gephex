libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

rotozoommodule_auto.c: rotozoommodule.spec rotozoommodule.h
	$(PLUC) c @srcdir@/rotozoommodule.spec

rotozoommodule.h: rotozoommodule.spec
	$(PLUC) h @srcdir@/rotozoommodule.spec

lib_LTLIBRARIES = rotozoommodule.la

rotozoommodule_la_SOURCES = rotozoommodule_auto.c \
			    rotozoommodule.c \
			    rotozoommodule.h \
			    rotozoommodule.spec \
			    rotozoommodule.xpm

rotozoommodule_la_LIBADD = -lgeo -L@builddir@/../../../util/src/libgeo

rotozoommodule_la_DEPENDENCIES = @builddir@/../../../util/src/libgeo/libgeo.a

rotozoommodule_la_LDFLAGS = -module -avoid-version


INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
	   -I@srcdir@/../../../util/src/libgeo \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/positiontype 


 

DISTCLEANFILES = rotozoommodule.h rotozoommodule_auto.c
EXTRA_DIST = rotozoommodule.vcproj rotozoommodule.dsp rotozoommodule.mak rotozoommodule.dep
