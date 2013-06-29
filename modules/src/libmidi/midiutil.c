/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2005

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#include "midiutil.h"

#include <stdio.h>

int midi_length_of_message(uint8_t status)
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

int midi_is_status(uint8_t byte)
{
  if (byte >= 0x80)
    return 1;

  return 0;
}
