libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

chromakeymodule_auto.c: chromakeymodule.spec chromakeymodule.h
	$(PLUC) c @srcdir@/chromakeymodule.spec

chromakeymodule.h: chromakeymodule.spec
	$(PLUC) h @srcdir@/chromakeymodule.spec

lib_LTLIBRARIES = chromakeymodule.la

chromakeymodule_la_SOURCES = \
        chromakeymodule_auto.c \
        chromakeymodule.c \
        chromakeymodule.h \
        chromakeymodule.spec \
        chromakeymodule.xpm

@builddir@/chromakeymodule_x86.o: @srcdir@/chromakeymodule_x86.asm
	@NASM@ @NASM_FLAGS@ -o @builddir@/chromakeymodule_x86.o @srcdir@/chromakeymodule_x86.asm

if OPT_INCLUDE_MMX
chromakeymodule_la_LIBADD = \
	@builddir@/chromakeymodule_x86.o \
	-lcpuinfo -L@builddir@/../../../util/src/cpuinfo

chromakeymodule_la_DEPENDENCIES = \
	@builddir@/chromakeymodule_x86.o \
	@builddir@/../../../util/src/cpuinfo/libcpuinfo.a
cpuinfoINCLUDES = -I @srcdir@/../../../util/src/cpuinfo
endif

chromakeymodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/rgbtype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype \
	   $(cpuinfoINCLUDES)

DISTCLEANFILES = chromakeymodule.h chromakeymodule_auto.c
EXTRA_DIST = chromakeymodule.dsp chromakeymodule.mak chromakeymodule.dep chromakeymodule_x86.asm