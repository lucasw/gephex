libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

v4lmodule_auto.c: v4lmodule.spec v4lmodule.h
	$(PLUC) c @srcdir@/v4lmodule.spec

v4lmodule.h: v4lmodule.spec
	$(PLUC) h @srcdir@/v4lmodule.spec

lib_LTLIBRARIES = v4lmodule.la

v4lmodule_la_SOURCES = 	v4lmodule_auto.c \
			v4lmodule.cpp \
			videodevice.cpp \
			videodevice.h \
			colorconv.h \
			colorconv.cpp \
			v4lmodule.h \
			videodev.h \
			v4lmodule.spec \
			v4lmodule.xpm

v4lmodule_la_LDFLAGS = -module -avoid-version
v4lmodule_la_LIBADD = -lstdc++

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/stringtype \
		-I @srcdir@/../../../types/src/framebuffertype

DISTCLEANFILES = v4lmodule.h v4lmodule_auto.c
