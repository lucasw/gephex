bindir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

xfademodule_auto.c: xfademodule.spec xfademodule.h
	$(PLUC) c @srcdir@/xfademodule.spec

xfademodule.h: xfademodule.spec
	$(PLUC) h @srcdir@/xfademodule.spec

EXEEXT=.@SHAREDLIBEXT@

bin_PROGRAMS = xfademodule

xfademodule_CFLAGS = $(AM_CFLAGS) @SHARED_COMP_FLAGS@

if SHARED_USE_DEF_FILE
DEFFILE=xfademodule.def
else
DEFFILE=
endif

xfademodule_SOURCES = xfademodule_auto.c \
		      xfademodule.c \
		      xfademodule.h \
		      xfademodule.spec \
		      xfademodule.xpm

@builddir@/xfademodule_x86.o: @srcdir@/xfademodule_x86.asm
	@NASM@ @NASM_FLAGS@ -o @builddir@/xfademodule_x86.o @srcdir@/xfademodule_x86.asm

if OPT_INCLUDE_MMX
xfademodule_LDADD = \
	@builddir@/xfademodule_x86.o \
	-lcpuinfo -L@builddir@/../../../util/src/cpuinfo
xfademodule_DEPENDENCIES = \
		@builddir@/xfademodule_x86.o \
		@builddir@/../../../util/src/cpuinfo/libcpuinfo.a
cpuinfoINCLUDES       = -I @srcdir@/../../../util/src/cpuinfo
endif

xfademodule_LDFLAGS = @SHARED_LD_FLAGS@

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/stringtype \
		-I @srcdir@/../../../types/src/framebuffertype \
		$(cpuinfoINCLUDES)

DISTCLEANFILES = xfademodule.h xfademodule_auto.c
EXTRA_DIST = xfademodule.vcproj xfademodule.dsp xfademodule.mak xfademodule.dep xfademodule_x86.asm
