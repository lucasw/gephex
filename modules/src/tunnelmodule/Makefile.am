libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

tunnelmodule_auto.c: tunnelmodule.spec tunnelmodule.h
	$(PLUC) c @srcdir@/tunnelmodule.spec

tunnelmodule.h: tunnelmodule.spec
	$(PLUC) h @srcdir@/tunnelmodule.spec

lib_LTLIBRARIES = tunnelmodule.la

tunnelmodule_la_SOURCES = 	tunnelmodule_auto.c \
				tunnelmodule.c \
				tunnelmodule.h \
				tunnelmodule.spec \
				tunnelmodule.xpm

tunnelmodule_la_LDFLAGS = -module -avoid-version -no-undefined

tunnelmodule_la_LIBADD = -lgrid -L@builddir@/../libgrid

tunnelmodule_la_DEPENDENCIES = @builddir@/../libgrid/libgrid.a

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/positiontype \
		-I @srcdir@/../../../types/src/framebuffertype

 

DISTCLEANFILES = tunnelmodule.h tunnelmodule_auto.c
