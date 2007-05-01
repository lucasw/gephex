bindir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

tunnelmodule_auto.c: tunnelmodule.spec tunnelmodule.h
	$(PLUC) c @srcdir@/tunnelmodule.spec

tunnelmodule.h: tunnelmodule.spec
	$(PLUC) h @srcdir@/tunnelmodule.spec

EXEEXT=.@SHAREDLIBEXT@

bin_PROGRAMS = tunnelmodule

tunnelmodule_CFLAGS = $(AM_CFLAGS) @SHARED_COMP_FLAGS@

if SHARED_USE_DEF_FILE
DEFFILE=tunnelmodule.def
else
DEFFILE=
endif

tunnelmodule_SOURCES = 	tunnelmodule_auto.c \
				tunnelmodule.c \
				tunnelmodule.h \
				tunnelmodule.spec \
				tunnelmodule.xpm

tunnelmodule_LDFLAGS = @SHARED_LD_FLAGS@

tunnelmodule_LDADD = -lgrid -L@builddir@/../libgrid

tunnelmodule_DEPENDENCIES = @builddir@/../libgrid/libgrid.a

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/positiontype \
		-I @srcdir@/../../../types/src/stringtype \
		-I @srcdir@/../../../types/src/framebuffertype


DISTCLEANFILES = tunnelmodule.h tunnelmodule_auto.c
EXTRA_DIST = tunnelmodule.vcproj tunnelmodule.dsp tunnelmodule.mak tunnelmodule.dep
