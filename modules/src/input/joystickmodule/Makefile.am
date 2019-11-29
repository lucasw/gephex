libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

joystickmodule_auto.c: joystickmodule.spec joystickmodule.h
	$(PLUC) c @srcdir@/joystickmodule.spec

joystickmodule.h: joystickmodule.spec
	$(PLUC) h @srcdir@/joystickmodule.spec

lib_LTLIBRARIES = joystickmodule.la

joystickmodule_la_SOURCES = \
	joystickmodule_auto.c \
	joystickmodule.cpp \
	joystickmodule.h \
	joystickmodule.spec \
	joystickmodule.xpm

joystickmodule_la_LIBADD = \
	-L@builddir@/../../../util/src/libjoystick \
	-ljoystick

joystickmodule_la_DEPENDENCIES = @builddir@/../../../util/src/libjoystick/.libs/libjoystick.a
joystickmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = \
	-I @srcdir@/../../../engine/src/engine \
	-I @srcdir@/../../../util/include \
	-I @srcdir@/../../../types/src/miditype \
	-I @srcdir@/../../../types/src/numbertype \
	-I @srcdir@/../../../types/src/stringtype \
	-I @srcdir@/../libmidi \
	-I @srcdir@/../../../util/src/libjoystick

DISTCLEANFILES = joystickmodule.h joystickmodule_auto.c
EXTRA_DIST = joystickmodule.vcproj joystickmodule.dsp joystickmodule.mak joystickmodule.dep
