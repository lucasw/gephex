libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

imgarithmodule_auto.c: imgarithmodule.spec imgarithmodule.h
	$(PLUC) c @srcdir@/imgarithmodule.spec

imgarithmodule.h: imgarithmodule.spec
	$(PLUC) h @srcdir@/imgarithmodule.spec

lib_LTLIBRARIES = imgarithmodule.la

@builddir@/imgarithmodule_x86.o: @srcdir@/imgarithmodule_x86.asm
	@NASM@ @NASM_FLAGS@ -o @builddir@/imgarithmodule_x86.o @srcdir@/imgarithmodule_x86.asm


if OPT_INCLUDE_MMX
imgarithmodule_la_LIBADD = \
	@builddir@/imgarithmodule_x86.o \
	-lcpuinfo -L@builddir@/../../../util/src/cpuinfo 


imgarithmodule_la_DEPENDENCIES= \
	@builddir@/imgarithmodule_x86.o \
	@builddir@/../../../util/src/cpuinfo/libcpuinfo.a

cpuinfoINCLUDES = -I @srcdir@/../../../util/src/cpuinfo
endif


imgarithmodule_la_SOURCES = \
	imgarithmodule_auto.c \
	imgarithmodule.c \
	imgarithmodule.h \
	imgarithmodule.spec \
	imgarithmodule.xpm


imgarithmodule_la_LDFLAGS = -module -avoid-version 

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/framebuffertype \
		-I @srcdir@/../../../types/src/stringtype \
		$(cpuinfoINCLUDES)

DISTCLEANFILES = imgarithmodule.h imgarithmodule_auto.c

EXTRA_DIST = imgarithmodule.dsp imgarithmodule.mak imgarithmodule.dep imgarithmodule_x86.asm
