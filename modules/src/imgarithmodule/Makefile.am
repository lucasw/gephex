bindir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

imgarithmodule_auto.c: imgarithmodule.spec imgarithmodule.h
	$(PLUC) c @srcdir@/imgarithmodule.spec

imgarithmodule.h: imgarithmodule.spec
	$(PLUC) h @srcdir@/imgarithmodule.spec

EXEEXT=.@SHAREDLIBEXT@

bin_PROGRAMS = imgarithmodule

imgarithmodule_CFLAGS = $(AM_CFLAGS) @SHARED_COMP_FLAGS@

@builddir@/imgarithmodule_x86.o: @srcdir@/imgarithmodule_x86.asm
	@NASM@ @NASM_FLAGS@ -o @builddir@/imgarithmodule_x86.o @srcdir@/imgarithmodule_x86.asm


if OPT_INCLUDE_MMX
imgarithmodule_LDADD = \
	@builddir@/imgarithmodule_x86.o \
	-lcpuinfo -L@builddir@/../../../util/src/cpuinfo 


imgarithmodule_DEPENDENCIES= \
	@builddir@/imgarithmodule_x86.o \
	@builddir@/../../../util/src/cpuinfo/libcpuinfo.a

cpuinfoINCLUDES = -I @srcdir@/../../../util/src/cpuinfo
endif


imgarithmodule_SOURCES = \
	imgarithmodule_auto.c \
	imgarithmodule.c \
	imgarithmodule.h \
	imgarithmodule.spec \
	imgarithmodule.xpm


imgarithmodule_LDFLAGS = @SHARED_LD_FLAGS@

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/framebuffertype \
		-I @srcdir@/../../../types/src/stringtype \
		$(cpuinfoINCLUDES)

DISTCLEANFILES = imgarithmodule.h imgarithmodule_auto.c

EXTRA_DIST = imgarithmodule.vcproj imgarithmodule.dsp imgarithmodule.mak imgarithmodule.dep imgarithmodule_x86.asm
