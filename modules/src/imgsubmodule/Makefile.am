libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

imgsubmodule_auto.c: imgsubmodule.spec imgsubmodule.h
	$(PLUC) c @srcdir@/imgsubmodule.spec

imgsubmodule.h: imgsubmodule.spec
	$(PLUC) h @srcdir@/imgsubmodule.spec

lib_LTLIBRARIES = imgsubmodule.la
imgsubmodule_la_SOURCES = 	imgsubmodule_auto.c \
				imgsubmodule.c \
				imgsubmodule.h \
				imgsubmodule.spec \
				imgsubmodule.xpm


if OPT_INCLUDE_MMX
imgsubmodule_la_LIBADD = -lcpuinfo -L@builddir@/../../../util/src/cpuinfo
imgsubmodule_la_DEPENDENCIES= @builddir@/../../../util/src/cpuinfo/libcpuinfo.a
cpuinfoINCLUDES        = -I @srcdir@/../../../util/src/cpuinfo
endif

imgsubmodule_la_LDFLAGS = -module -avoid-version 

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/framebuffertype \
		-I @srcdir@/../../../types/src/stringtype \
		$(cpuinfoINCLUDES)

 

DISTCLEANFILES = imgsubmodule.h imgsubmodule_auto.c
