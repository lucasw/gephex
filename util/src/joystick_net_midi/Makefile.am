bin_PROGRAMS = joystick_midi_net

joystick_midi_net_SOURCES = joystick_midi_net.c

INCLUDES = -I @srcdir@/../libjoystick

joystick_midi_net_LDFLAGS =

joystick_midi_net_LDADD = -ljoystick $(SDL_LIBS) -L@builddir@/../libjoystick/ 

joystick_midi_net_DEPENDENCIES = @builddir@/../libjoystick/libjoystick.a

