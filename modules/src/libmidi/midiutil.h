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

#ifndef INCLUDED_MIDIUTIL_H
#define INCLUDED_MIDIUTIL_H

#include "basic_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MIDI_NOTE_OFF    0x80
#define MIDI_NOTE_ON     0x90
#define MIDI_AFTERTOUCH  0xa0
#define MIDI_CTRLCHANGE  0xb0
#define MIDI_PROGCHANGE  0xc0
#define MIDI_CHANNEL_AFTERTOUCH  0xd0
#define MIDI_PITCHBEND   0xe0
#define MIDI_SYSTEM      0xf0
#define MIDI_EOX         0xf7  /* end of SYSEX message */ 

  /**
   * Returns the number of data bytes of a midi message.
   * If status is a system exclusive message, -1 is returned.
   * Please note that any midi message might be interleaved by
   * one byte system realtime messages.
   * @param status the status byte of a midi message
   * @return the number of data bytes following the status byte,
   *           or -1 for a variable length message. If status
   *           is invalid, -2 is returned
   */
  int midi_length_of_message(uint8_t status);

  /**
   * Returns wether a byte is a midi status byte.
   * @param the byte that is tested
   * @return 1 if byte is a status byte, 0 if it is a data byte
   */
  int midi_is_status(uint8_t byte);

#ifdef __cplusplus
}
#endif
#endif
