libdir = @libdir@/gephex/modules

PLUC=python @top_srcdir@/modules/pluc.py


gradnormmodule_auto.c: gradnormmodule.spec gradnormmodule.h
	$(PLUC) c @srcdir@/gradnormmodule.spec

gradnormmodule.h: gradnormmodule.spec
	$(PLUC) h @srcdir@/gradnormmodule.spec

lib_LTLIBRARIES = gradnormmodule.la


if OPT_INCLUDE_MMX
gradnormmodule_la_LIBADD = \
	-lcpuinfo \
	-L@builddir@/../../../util/src/cpuinfo

gradnormmodule_la_DEPENDENCIES= \
	@builddir@/../../../util/src/cpuinfo/libcpuinfo.a

cpuinfoINCLUDES  = -I @srcdir@/../../../util/src/cpuinfo

endif

gradnormmodule_la_SOURCES = \
        gradnormmodule_auto.c \
        gradnormmodule.cpp \
        gradnormmodule.h \
        gradnormmodule.spec \
        gradnormmodule.xpm $(3DNOW_sOURCES)

gradnormmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype $(cpuinfoINCLUDES)


DISTCLEANFILES = gradnormmodule.h gradnormmodule_auto.c
EXTRA_DIST = gradnormmodule.dsp gradnormmodule.mak gradnormmodule.dep roberts_cross_x86.asm
