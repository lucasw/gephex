libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

imgarithmodule_auto.c: imgarithmodule.spec imgarithmodule.h
	$(PLUC) c @srcdir@/imgarithmodule.spec

imgarithmodule.h: imgarithmodule.spec
	$(PLUC) h @srcdir@/imgarithmodule.spec

lib_LTLIBRARIES = imgarithmodule.la

if OPT_INCLUDE_MMX
imgarithmodule_la_LIBADD = \
	-lcpuinfo \
	-L@builddir@/../../../util/src/cpuinfo 
#	imgarithmodule_x86_mmx.o

imgarithmodule_la_DEPENDENCIES= \
	@builddir@/../../../util/src/cpuinfo/libcpuinfo.a
#	imgarithmodule_x86_mmx.o

cpuinfoINCLUDES          = -I @srcdir@/../../../util/src/cpuinfo
#MMX_sOURCES              = imgarithmodule_x86_mmx.asm

#imgarithmodule_x86_mmx.o: imgarithmodule_x86_mmx.asm
#	nasm -o imgarithmodule_x86_mmx.o -f elf imgarithmodule_x86_mmx.asm
endif


imgarithmodule_la_SOURCES = \
	imgarithmodule_auto.c \
	imgarithmodule.c \
	imgarithmodule.h \
	imgarithmodule.spec \
	imgarithmodule.xpm #$(MMX_sOURCES)


imgarithmodule_la_LDFLAGS = -module -avoid-version 

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/framebuffertype \
		-I @srcdir@/../../../types/src/stringtype \
		$(cpuinfoINCLUDES)

 

DISTCLEANFILES = imgarithmodule.h imgarithmodule_auto.c

EXTRA_DIST = imgarithmodule.dsp imgarithmodule.mak imgarithmodule.dep
