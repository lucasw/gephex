noinst_LIBRARIES = libjoystick.a

if HAVE_SDL
SDL_sOURCES = \
	sdljoystickdriver.h \
	sdljoystickdriver.cpp
SDL_lIBADD = @SDL_PREFIX@/lib/libSDL.so /usr/lib/libpthread.so
endif

libjoystick_a_SOURCES = \
	libjoystick.cpp \
	joystickdriver.h \
	linuxjoystickdriver.h \
	linuxjoystickdriver.cpp $(SDL_sOURCES)

#libjoystick_a_LIBADD = /usr/lib/libSDL.so 
libjoystick_a_LIBADD = $(SDL_lIBADD)
noinst_HEADERS = libjoystick.h

INCLUDES = 	-I @srcdir@/.. \
		-I @srcdir@/../../include @SDL_CFLAGS@



