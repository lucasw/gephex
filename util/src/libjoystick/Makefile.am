EXTRA_DIST = libjoystick.dsp libjoystick.mak libjoystick.dep \
	win32joystickdriver.cpp win32joystickdriver.h

noinst_LIBRARIES = libjoystick.a

if WITH_SDL
SDL_sOURCES = \
	sdljoystickdriver.h \
	sdljoystickdriver.cpp
SDL_lIBADD = @SDL_PREFIX@/lib/libSDL.so /usr/lib/libpthread.so
endif

if WITH_LINUX_JOYSTICK
LJ_sOURCES = \
	linuxjoystickdriver.h \
	linuxjoystickdriver.cpp
endif

libjoystick_a_SOURCES = \
	libjoystick.cpp \
	joystickdriver.h  $(LJ_sOURCES) $(SDL_sOURCES)

libjoystick_a_LIBADD = $(SDL_lIBADD)
noinst_HEADERS = libjoystick.h

INCLUDES = -I @srcdir@/.. \
	   -I @srcdir@/../../include @SDL_CFLAGS@



