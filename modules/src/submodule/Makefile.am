libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

submodule_auto.c: submodule.spec submodule.h
	$(PLUC) c @srcdir@/submodule.spec

submodule.h: submodule.spec
	$(PLUC) h @srcdir@/submodule.spec

lib_LTLIBRARIES = submodule.la
submodule_la_SOURCES = \
	submodule_auto.c \
	submodule.c \
	submodule.h \
	submodule.spec \
	submodule.xpm

submodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype 

 

DISTCLEANFILES = submodule.h submodule_auto.c
