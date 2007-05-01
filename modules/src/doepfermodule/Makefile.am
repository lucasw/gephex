libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

doepfermodule_auto.c: doepfermodule.spec doepfermodule.h
	$(PLUC) c @srcdir@/doepfermodule.spec

doepfermodule.h: doepfermodule.spec
	$(PLUC) h @srcdir@/doepfermodule.spec

lib_LTLIBRARIES = doepfermodule.la

doepfermodule_la_SOURCES = 	doepfermodule_auto.c \
				doepfermodule.c \
				doepfermodule.h \
				doepfermodule.spec \
				doepfermodule.xpm

doepfermodule_la_LIBADD = -lmidi -L@builddir@/../libmidi

doepfermodule_la_DEPENDENCIES = @builddir@/../libmidi/libmidi.a

doepfermodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/miditype \
		-I @srcdir@/../libmidi

DISTCLEANFILES = doepfermodule.h doepfermodule_auto.c
EXTRA_DIST = doepfermodule.vcproj doepfermodule.dsp doepfermodule.mak doepfermodule.dep
