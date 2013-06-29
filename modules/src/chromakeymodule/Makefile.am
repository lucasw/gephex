bindir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

chromakeymodule_auto.c: chromakeymodule.spec chromakeymodule.h
	$(PLUC) c @srcdir@/chromakeymodule.spec

chromakeymodule.h: chromakeymodule.spec
	$(PLUC) h @srcdir@/chromakeymodule.spec

chromakeymodule.def: chromakeymodule.spec
	$(PLUC) def @srcdir@/chromakeymodule.spec

EXEEXT=.@SHAREDLIBEXT@

bin_PROGRAMS = chromakeymodule

chromakeymodule_CFLAGS = $(AM_CFLAGS) @SHARED_COMP_FLAGS@

if SHARED_USE_DEF_FILE
DEFFILE=chromakeymodule.def
else
DEFFILE=
endif

chromakeymodule_SOURCES = \
        chromakeymodule_auto.c \
        chromakeymodule.c \
        chromakeymodule.h \
        chromakeymodule.spec \
        chromakeymodule.xpm

@builddir@/chromakeymodule_x86.o: @srcdir@/chromakeymodule_x86.asm
	@NASM@ @NASM_FLAGS@ -o @builddir@/chromakeymodule_x86.o @srcdir@/chromakeymodule_x86.asm

if OPT_INCLUDE_MMX

chromakeymodule_LDADD = \
       $(DEFFILE) \
	@builddir@/chromakeymodule_x86.o \
	-lcpuinfo -L@builddir@/../../../util/src/cpuinfo

chromakeymodule_DEPENDENCIES = \
	chromakeymodule.def \
	@builddir@/chromakeymodule_x86.o \
	@builddir@/../../../util/src/cpuinfo/libcpuinfo.a
cpuinfoINCLUDES = -I @srcdir@/../../../util/src/cpuinfo
endif

chromakeymodule_LDFLAGS = @SHARED_LD_FLAGS@

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/rgbtype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype \
	   $(cpuinfoINCLUDES)

DISTCLEANFILES = chromakeymodule.h chromakeymodule_auto.c chromakeymodule.def
EXTRA_DIST = chromakeymodule.vcproj chromakeymodule.dsp chromakeymodule.mak chromakeymodule.dep chromakeymodule_x86.asm
