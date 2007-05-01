libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

plasmamodule_auto.c: plasmamodule.spec plasmamodule.h
	$(PLUC) c @srcdir@/plasmamodule.spec

plasmamodule.h: plasmamodule.spec
	$(PLUC) h @srcdir@/plasmamodule.spec

lib_LTLIBRARIES = plasmamodule.la

plasmamodule_la_SOURCES = 	plasmamodule_auto.c \
				plasmamodule.c \
				plasmamodule.h \
				plasmamodule.spec \
				plasmamodule.xpm

plasmamodule_la_LDFLAGS = -module -avoid-version -no-undefined

plasmamodule_la_LIBADD = -lgrid -L@builddir@/../libgrid

plasmamodule_la_DEPENDENCIES = @builddir@/../libgrid/libgrid.a

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/framebuffertype

 

DISTCLEANFILES = plasmamodule.h plasmamodule_auto.c
EXTRA_DIST = plasmamodule.vcproj plasmamodule.dsp plasmamodule.mak plasmamodule.dep
