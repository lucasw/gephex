libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

joystickmodule_auto.c: joystickmodule.spec joystickmodule.h
	$(PLUC) c @srcdir@/joystickmodule.spec

joystickmodule.h: joystickmodule.spec
	$(PLUC) h @srcdir@/joystickmodule.spec

lib_LTLIBRARIES = joystickmodule.la

joystickmodule_la_SOURCES = 	joystickmodule_auto.c \
				joystickmodule.c \
				joystickmodule.h \
				joystickmodule.spec \
				joystickmodule.xpm

joystickmodule_la_LIBADD = $(SDL_LIBS) -ljoystick \
	-L@builddir@/../../../util/src/libjoystick

joystickmodule_la_DEPENDENCIES = @builddir@/../../../util/src/libjoystick/libjoystick.a
joystickmodule_la_LDFLAGS = -module -avoid-version 


INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/miditype \
		-I @srcdir@/../../../types/src/numbertype \
		`sdl-config --cflags` \
		-I @srcdir@/../libmidi \
		-I @srcdir@/../../../util/src/libjoystick



 

DISTCLEANFILES = joystickmodule.h joystickmodule_auto.c
