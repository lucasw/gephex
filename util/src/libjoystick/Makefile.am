noinst_LIBRARIES = libjoystick.a

libjoystick_a_SOURCES = libjoystick.c

#libjoystick_a_LIBADD = /usr/lib/libSDL.so 
libjoystick_a_LIBADD = @SDL_PREFIX@/lib/libSDL.so /usr/lib/libpthread.so
noinst_HEADERS = libjoystick.h

INCLUDES = 	-I @srcdir@/.. \
		-I @srcdir@/../../include \
                -I /usr/include/SDL @SDL_CFLAGS@



