libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

staticcolormodule_auto.c: staticcolormodule.spec staticcolormodule.h
	$(PLUC) c @srcdir@/staticcolormodule.spec

staticcolormodule.h: staticcolormodule.spec
	$(PLUC) h @srcdir@/staticcolormodule.spec

lib_LTLIBRARIES = staticcolormodule.la

if OPT_INCLUDE_MMX
staticcolormodule_la_LIBADD = -lcpuinfo -L@builddir@/../../../util/src/cpuinfo
staticcolormodule_la_DEPENDENCIES= @builddir@/../../../util/src/cpuinfo/libcpuinfo.a
cpuinfoINCLUDES             = -I @srcdir@/../../../util/src/cpuinfo
endif

staticcolormodule_la_SOURCES = 	staticcolormodule_auto.c \
				staticcolormodule.c \
				staticcolormodule.h \
				staticcolormodule.spec \
				staticcolormodule.xpm

staticcolormodule_la_LDFLAGS = -module -avoid-version

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/rgbtype \
		-I @srcdir@/../../../types/src/framebuffertype \
		$(cpuinfoINCLUDES)

 

DISTCLEANFILES = staticcolormodule.h staticcolormodule_auto.c
EXTRA_DIST = staticcolormodule.dsp staticcolormodule.mak staticcolormodule.dep
