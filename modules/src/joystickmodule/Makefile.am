joystickmodule_auto.c: joystickmodule.spec joystickmodule.h
	python $(top_builddir)/pluc.py c joystickmodule.spec

joystickmodule.h: joystickmodule.spec
	python $(top_builddir)/pluc.py h joystickmodule.spec

lib_LTLIBRARIES = joystickmodule.la
joystickmodule_la_SOURCES = joystickmodule_auto.c joystickmodule.c joystickmodule.h joystickmodule.spec joystickmodule.xpm

joystickmodule_la_LIBADD = -L/usr/lib -lSDL -lpthread

joystickmodule_la_LDFLAGS = -module -avoid-version

INCLUDES  =  -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine `sdl-config --cflags`

.PHONY: clean
clean:
	rm -f joystickmodule.h joystickmodule_auto.c
