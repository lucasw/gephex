#include "midiutil.h"

#include <stdio.h>

int midi_length_of_message(unsigned char status)
{
  int upper_nibble = status & 0xf0;
  switch (upper_nibble)
    {
    case MIDI_NOTE_OFF:
    case MIDI_NOTE_ON:
    case MIDI_AFTERTOUCH:
    case MIDI_CTRLCHANGE:
    case MIDI_PITCHBEND:
      return 2;
    case MIDI_PROGCHANGE:
    case MIDI_CHANNEL_AFTERTOUCH:
      return 1;
    case MIDI_SYSTEM:
      {
	int lower_nibble = status & 0x0f;
	switch (lower_nibble)
	  {
	  case 0:
	    return -1; //variable length system exclusive message
	  case 1:
	  case 3:
	    return 1;
	  case 2:
	    return 2;
	  default:
	    return 0;
	  }
      }
    default:
      fprintf(stderr, "Unknown midi status: %i\n", status);
      return -2;
    }
}

int midi_is_status(unsigned char byte)
{
  if (byte >= 0x80)
    return 1;

  return 0;
}
