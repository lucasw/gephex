libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

netcontrolmodule_auto.c: netcontrolmodule.spec netcontrolmodule.h
	$(PLUC) c @srcdir@/netcontrolmodule.spec

netcontrolmodule.h: netcontrolmodule.spec
	$(PLUC) h @srcdir@/netcontrolmodule.spec

lib_LTLIBRARIES = netcontrolmodule.la

netcontrolmodule_la_SOURCES = 	netcontrolmodule_auto.c \
				netcontrolmodule.c \
				netcontrolmodule.h \
				netcontrolmodule.spec \
				netcontrolmodule.xpm

netcontrolmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/miditype 

netcontrolmodule_la_LIBADD = $(LIB_SOCKET_FLAGS)

DISTCLEANFILES = netcontrolmodule.h netcontrolmodule_auto.c
EXTRA_DIST = netcontrolmodule.vcproj netcontrolmodule.dsp netcontrolmodule.mak netcontrolmodule.dep
