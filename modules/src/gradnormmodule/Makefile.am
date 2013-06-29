bindir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py


gradnormmodule_auto.c: gradnormmodule.spec gradnormmodule.h
	$(PLUC) c @srcdir@/gradnormmodule.spec

gradnormmodule.h: gradnormmodule.spec
	$(PLUC) h @srcdir@/gradnormmodule.spec

EXEEXT=.@SHAREDLIBEXT@

bin_PROGRAMS = gradnormmodule

gradnormmodule_CFLAGS = $(AM_CFLAGS) @SHARED_COMP_FLAGS@

@builddir@/roberts_cross_x86.o: @srcdir@/roberts_cross_x86.asm
	@NASM@ @NASM_FLAGS@ -o @builddir@/roberts_cross_x86.o @srcdir@/roberts_cross_x86.asm

if OPT_INCLUDE_MMX
gradnormmodule_LDADD = @builddir@/roberts_cross_x86.o\
	-lcpuinfo \
	-L@builddir@/../../../util/src/cpuinfo

gradnormmodule_DEPENDENCIES= \
	@builddir@/roberts_cross_x86.o \
	@builddir@/../../../util/src/cpuinfo/libcpuinfo.a

cpuinfoINCLUDES  = -I @srcdir@/../../../util/src/cpuinfo

endif

gradnormmodule_SOURCES = \
        gradnormmodule_auto.c \
        gradnormmodule.cpp \
        gradnormmodule.h \
        gradnormmodule.spec \
        gradnormmodule.xpm $(3DNOW_sOURCES)

gradnormmodule_LDFLAGS = @SHARED_LD_FLAGS@

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype $(cpuinfoINCLUDES)


DISTCLEANFILES = gradnormmodule.h gradnormmodule_auto.c
EXTRA_DIST = gradnormmodule.vcproj gradnormmodule.dsp gradnormmodule.mak gradnormmodule.dep roberts_cross_x86.asm
