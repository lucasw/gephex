libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

invertmodule_auto.c: invertmodule.spec invertmodule.h
	$(PLUC) c @srcdir@/invertmodule.spec

invertmodule.h: invertmodule.spec
	$(PLUC) h @srcdir@/invertmodule.spec

lib_LTLIBRARIES = invertmodule.la

invertmodule_la_SOURCES = 	invertmodule_auto.c \
				invertmodule.c \
				invertmodule.h \
				invertmodule.spec \
				invertmodule.xpm

if OPT_INCLUDE_MMX
invertmodule_la_LIBADD = -lcpuinfo -L@builddir@/../../../util/src/cpuinfo
invertmodule_la_DEPENDENCIES= @builddir@/../../../util/src/cpuinfo/libcpuinfo.a
cpuinfoINCLUDES        = -I @srcdir@/../../../util/src/cpuinfo
endif

invertmodule_la_LDFLAGS = -module -avoid-version


INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/framebuffertype \
		-I @srcdir@/../../../types/src/stringtype \
		$(cpuinfoINCLUDES)

 

DISTCLEANFILES = invertmodule.h invertmodule_auto.c
