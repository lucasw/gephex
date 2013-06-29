libdir = @gphx_module_lib_dir@
noinst_LIBRARIES = libcolorconv.a

@builddir@/libcolorconv_x86.o: @srcdir@/libcolorconv_x86.asm
	@NASM@ @NASM_FLAGS@ -o @builddir@/libcolorconv_x86.o @srcdir@/libcolorconv_x86.asm

if OPT_INCLUDE_MMX
libcolorconv_a_LIBADD = @builddir@/libcolorconv_x86.o

libcolorconv_a_DEPENDENCIES= @builddir@/libcolorconv_x86.o
endif

libcolorconv_a_SOURCES = libcolorconv.cpp libcolorconv.h

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include

EXTRA_DIST = libcolorconv_x86.asm libcolorconv.vcproj libcolorconv.dsp libcolorconv.mak libcolorconv.mak
