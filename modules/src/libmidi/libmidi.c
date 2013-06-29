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

#include "libmidi.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "midiutil.h"

static const uint8_t NO_STATUS = 0;  // not a status byte

struct MidiParser
{
  midi_noteoffT noteoff;
  midi_noteonT noteon;
  midi_aftertouchT aftertouch;
  midi_controlchangeT controlchange;
  midi_programchangeT programchange;
  midi_channelaftertouchT channelaftertouch;
  midi_pitchbendT pitchbend;
  midi_systemexclusiveT systemexclusive;

  uint8_t running_status;
  void* user_data;
};


struct MidiParser* midi_create_parser(midi_noteoffT noteoff,
				      midi_noteonT noteon,
				      midi_aftertouchT aftertouch,
				      midi_controlchangeT controlchange,
				      midi_programchangeT programchange,
				      midi_channelaftertouchT channelaftert,
				      midi_pitchbendT pitchbend,
				      midi_systemexclusiveT systemexclusive,
				      void* user_data)
{
  struct MidiParser* self = (struct MidiParser* ) malloc(sizeof(*self));

  self->noteoff = noteoff;
  self->noteon = noteon;
  self->aftertouch = aftertouch;
  self->controlchange = controlchange;
  self->programchange = programchange;
  self->channelaftertouch = channelaftert;
  self->pitchbend = pitchbend;
  self->systemexclusive = systemexclusive;

  self->running_status = NO_STATUS;
  self->user_data = user_data;

  return self;
}

void midi_destroy_parser(struct MidiParser* self)
{
  free(self);
}

static __inline int is_system_realtime(uint8_t byte)
{
  return byte >= 0xf8;
}

static int parse_onebytemsg(const uint8_t* buf,
			    int len, int* overflow, uint8_t* b)
{
  int index = 0;

  if (len < 1)
    {
      *overflow = 1;
      return 0;
    }

  while (is_system_realtime(buf[index]))
    ++index; //TODO: ignore system realtime for now
  
  // no it must be a data byte, no status byte allowed here
  if (midi_is_status(buf[index]))
    return -1;
  
  *b = buf[index++];

  return index;
}

static int parse_twobytemsg(const uint8_t* buf, int len, int* overflow,
			    uint8_t* b1, uint8_t* b2)
{
  int index = 0;

  if (len < 2)
    {
      *overflow = 1;
      return 0;
    }

  while (index < len && is_system_realtime(buf[index]))
    ++index; //TODO: ignore system realtime for now
  
  if (index >= len)
    {
      *overflow = 1;
      return 0;
    }

  // no it must be a data byte, no status byte allowed here
  if (midi_is_status(buf[index]))
    return -1;
  
  *b1 = buf[index++];

  while (index < len && is_system_realtime(buf[index]))
    ++index; //TODO: ignore system realtime for now
  
  if (index >= len)
    {
      *overflow = 1;
      return 0;
    }

  // no it must be a data byte, no status byte allowed here
  if (midi_is_status(buf[index]))
    return -1;
  
  *b2 = buf[index++];

  return index;
}

static int parse_system(struct MidiParser* self, int lower_nibble,
			const uint8_t* buf, int len, int* overflow)
{
  int index = 0;

  if (lower_nibble == 7)
    return -1; // EOX is not allowed here

  if (lower_nibble > 4)
    return 0; // ignore the 0 byte messages

  if (lower_nibble == 3 || lower_nibble == 1)
    {
      if (len < 1) {
	*overflow = 1;
	return -1;
      }

      return 1; // ignore 1 byte messages
    }

  if (lower_nibble == 2)
    {
      if (len < 2) {
	*overflow = 1;
	return -1;
      }

      return 2; // ignore 2 byte message
    }

  // only 0 is left -> system exclusive message
  if (len == 0)
    {
      *overflow = 1;
    return -1;
    }

  while (buf[index] != MIDI_EOX)
    {
      ++index;

      if (index >= len) {
	*overflow = 1;
	return -1;
      }
    }

  assert(index <= len);
  if (self->systemexclusive)
    self->systemexclusive(buf, index);

  return index;
}

int midi_parse_data(struct MidiParser* self, const uint8_t* buf, int len)
{
  int status = 0;
  int index = 0;
  int overflow = 0;

  while (index < len)
    {
      int length;
      uint8_t status_upper_nibble;
      uint8_t status_lower_nibble;

      status = buf[index];

      if (!midi_is_status((uint8_t) status))
	{
	  if (midi_is_status(self->running_status))
	    status = self->running_status;
	}
      else
	{
	  self->running_status = (uint8_t) status;
	  ++index; // go to first data byte
	}

      status_upper_nibble = status & 0xf0;
      status_lower_nibble = status & 0x0f;
      overflow = 0;

      switch(status_upper_nibble)
	{
	  uint8_t b1, b2;

	  case MIDI_NOTE_OFF:
	  length = parse_twobytemsg(buf + index, len-index, &overflow,
				    &b1, &b2);
	  if (length != -1 && self->noteoff)
	    {
	      self->noteoff(status_lower_nibble, b1, b2, self->user_data);
	    }
	  break;
	case MIDI_NOTE_ON:
	  length = parse_twobytemsg(buf + index, len-index, &overflow,
				    &b1, &b2);
	  if (length != -1 && self->noteon)
	    {
	      self->noteon(status_lower_nibble, b1, b2, self->user_data);
	    }
	  break;
	case MIDI_AFTERTOUCH:
	  length = parse_twobytemsg(buf + index, len-index, &overflow,
				    &b1, &b2);
	  if (length != -1 && self->aftertouch)
	    {
	      self->aftertouch(status_lower_nibble, b1, b2, self->user_data);
	    }
	  break;
	case MIDI_CTRLCHANGE:
	  length = parse_twobytemsg(buf + index, len-index, &overflow,
				    &b1, &b2);
	  if (length != -1 && self->controlchange)
	    {
	      self->controlchange(status_lower_nibble, b1, b2, self->user_data);
	    }
	  break;
	case MIDI_PROGCHANGE:
	  length = parse_onebytemsg(buf + index, len-index, &overflow, &b1);
	  if (length != -1 && self->programchange)
	    {
	      self->programchange(status_lower_nibble, b1, self->user_data);
	    }
	  break;
	case MIDI_CHANNEL_AFTERTOUCH:
	  length = parse_onebytemsg(buf + index, len-index, &overflow, &b1);
	  if (length != -1 && self->channelaftertouch)
	    {
	      self->channelaftertouch(status_lower_nibble, b1, self->user_data);
	    }
	  break;
	case MIDI_PITCHBEND:
	  length = parse_twobytemsg(buf + index, len-index, &overflow,
				    &b1, &b2);
	  if (length != -1 && self->pitchbend)
	    {
	      self->pitchbend(status_lower_nibble, b1 + (b2 << 7), self->user_data);
	    }
	  break;
	case MIDI_SYSTEM:
	  length = parse_system(self, status_lower_nibble,
				buf + index, len-index, &overflow);
	  break;
	default:
	  fprintf(stderr, "Unknown midi status: %i (midi_parse_data)",
		  status);
	  length = 1; // try the next byte
	}

      if (overflow == 1)
	{
	  fprintf(stderr,
		  "Unfinished command at buffer-end (midi_parse_data)\n");
	  //unfinished command at the end of buf
	  return index-1;
	}

      if (length == -1)
	{
	  fprintf(stderr, "Parse error (midi_parse_data)\n");
	  //advance to next byte if not at a statusbyte
	  if (!midi_is_status(buf[index]))
	    ++index;
	}
      else
	index += length;	
    }

  return index-1;
}

void midi_reset(struct MidiParser* self)
{
  self->running_status = NO_STATUS;
}

void midi_set_noteoff_handler(struct MidiParser* self,
			      midi_noteoffT handler)
{
  self->noteoff = handler;
}


void midi_set_noteon_handler(struct MidiParser* self,
			     midi_noteonT handler)
{
  self->noteon = handler;
}


void midi_set_aftertouch_handler(struct MidiParser* self,
				 midi_aftertouchT handler)
{
  self->aftertouch = handler;
}


void midi_set_controlchange_handler(struct MidiParser* self,
				    midi_controlchangeT handler)
{
  self->controlchange = handler;
}

void midi_set_programchange_handler(struct MidiParser* self,
				    midi_programchangeT handler)
{
  self->programchange = handler;
}

void midi_set_channelaftertouch_handler(struct MidiParser* self,
					midi_channelaftertouchT handler)
{
  self->channelaftertouch = handler;
}

void midi_set_pitchbend_handler(struct MidiParser* self,
				midi_pitchbendT handler)
{
  self->pitchbend = handler;
}

void midi_set_systemexclusive_handler(struct MidiParser* self,
				      midi_systemexclusiveT handler)
{
  self->systemexclusive = handler;
}
