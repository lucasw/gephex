libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

avifilemodule_auto.c: avifilemodule.spec avifilemodule.h
	$(PLUC) c @srcdir@/avifilemodule.spec

avifilemodule.h: avifilemodule.spec
	$(PLUC) h @srcdir@/avifilemodule.spec

lib_LTLIBRARIES = avifilemodule.la

avifilemodule_la_SOURCES = 	avifilemodule_auto.c \
				avifilemodule.cpp \
				avifilemodule.h \
				avifilemodule.spec \
				avifilemodule.xpm

avifilemodule_la_LDFLAGS = -module -avoid-version -no-undefined
avifilemodule_la_LIBADD = -laviplay -lstdc++

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/stringtype \
		-I @srcdir@/../../../types/src/framebuffertype

DISTCLEANFILES = avifilemodule.h avifilemodule_auto.c
