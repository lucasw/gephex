libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

xfademodule_auto.c: xfademodule.spec xfademodule.h
	$(PLUC) c @srcdir@/xfademodule.spec

xfademodule.h: xfademodule.spec
	$(PLUC) h @srcdir@/xfademodule.spec

lib_LTLIBRARIES = xfademodule.la
xfademodule_la_SOURCES = 	xfademodule_auto.c \
				xfademodule.c \
				xfademodule.h \
				xfademodule.spec \
				xfademodule.xpm

@builddir@/xfademodule_x86.o: @srcdir@/xfademodule_x86.asm
	@NASM@ @NASM_FLAGS@ -o @builddir@/xfademodule_x86.o @srcdir@/xfademodule_x86.asm

if OPT_INCLUDE_MMX
xfademodule_la_LIBADD = \
	@builddir@/xfademodule_x86.o \
	-lcpuinfo -L@builddir@/../../../util/src/cpuinfo
xfademodule_la_DEPENDENCIES = \
		@builddir@/xfademodule_x86.o \
		@builddir@/../../../util/src/cpuinfo/libcpuinfo.a
cpuinfoINCLUDES       = -I @srcdir@/../../../util/src/cpuinfo
endif

xfademodule_la_LDFLAGS = -module -avoid-version

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/stringtype \
		-I @srcdir@/../../../types/src/framebuffertype \
		$(cpuinfoINCLUDES)

DISTCLEANFILES = xfademodule.h xfademodule_auto.c
EXTRA_DIST = xfademodule.dsp xfademodule.mak xfademodule.dep xfademodule_x86.asm
