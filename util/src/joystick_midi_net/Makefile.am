EXTRA_DIST = joystick_midi_net.vcproj joystick_midi_net.dsp joystick_midi_net.mak joystick_midi_net.dep

bin_PROGRAMS = joystick_midi_net

joystick_midi_net_SOURCES = joystick_midi_net.cpp

INCLUDES = -I @srcdir@/../libjoystick

joystick_midi_net_LDFLAGS = -L@builddir@/../libjoystick/ -ljoystick

#joystick_midi_net_LDADD = 

joystick_midi_net_DEPENDENCIES = @builddir@/../libjoystick/.libs/libjoystick.a

