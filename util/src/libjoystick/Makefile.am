EXTRA_DIST = libjoystick.vcproj libjoystick.dsp libjoystick.mak libjoystick.dep \
	win32joystickdriver.cpp win32joystickdriver.h

noinst_LTLIBRARIES = libjoystick.la

if WITH_SDL
SDL_sOURCES = \
	sdljoystickdriver.h \
	sdljoystickdriver.cpp
SDL_lIBADD = @SDL_LD_FLAGS@
endif

if WITH_LINUX_JOYSTICK
LJ_sOURCES = \
	linuxjoystickdriver.h \
	linuxjoystickdriver.cpp
endif

libjoystick_la_SOURCES = \
	libjoystick.cpp \
	joystickdriver.h  $(LJ_sOURCES) $(SDL_sOURCES)

if OS_DARWIN
ADDITIONAL_LIBS = -lobjc
endif

libjoystick_la_LIBADD = $(SDL_lIBADD) $(ADDITIONAL_LIBS)

noinst_HEADERS = libjoystick.h

INCLUDES = -I @srcdir@/.. \
	   -I @srcdir@/../../include @SDL_CFLAGS@

