libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

resultmodule_auto.c: resultmodule.spec resultmodule.h
	$(PLUC) c @srcdir@/resultmodule.spec

resultmodule.h: resultmodule.spec
	$(PLUC) h @srcdir@/resultmodule.spec

lib_LTLIBRARIES = resultmodule.la
resultmodule_la_SOURCES = 	resultmodule_auto.c \
				resultmodule.c \
				resultmodule.h \
				resultmodule.spec \
				resultmodule_icon.xpm

resultmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype 

 

DISTCLEANFILES = resultmodule.h resultmodule_auto.c
EXTRA_DIST = resultmodule.dsp resultmodule.mak resultmodule.dep
