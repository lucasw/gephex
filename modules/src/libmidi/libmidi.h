/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

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

#ifndef INCLUDED_LIBMIDI_H
#define INCLUDED_LIBMIDI_H

#ifdef __cplusplus
extern "C"
{
#endif

  typedef void (*midi_noteoffT)(unsigned char channel, unsigned char key,
				unsigned char velocity,
				void* self);

  typedef void (*midi_noteonT)(unsigned char channel, unsigned char key,
			       unsigned char velocity, void* self);

  typedef void (*midi_aftertouchT)(unsigned char channel, unsigned char key,
				   unsigned char pressure,
				   void* self); 

  typedef void (*midi_controlchangeT)(unsigned char channel,
				      unsigned char control,
				      unsigned char value,
				      void* self);

  typedef void (*midi_programchangeT)(unsigned char channel,
				      unsigned char program, void* self);

  typedef void (*midi_channelaftertouchT)(unsigned char channel,
					  unsigned char pressure,
					  void* self); 

  typedef void (*midi_pitchbendT)(unsigned char channel, int value,
				  void* self);

  typedef void (*midi_systemexclusiveT)(const unsigned char* data, int len);


  struct MidiParser;


  /**
   * Creates a new midiparser with handlers that are called at specific
   * midi messages.
   * If a handler is 0, the message of the corresponding type is ignored.
   */
  struct MidiParser* midi_create_parser(midi_noteoffT noteoff,
					midi_noteonT noteon,
					midi_aftertouchT aftertouch,
					midi_controlchangeT controlchange,
					midi_programchangeT programchange,
					midi_channelaftertouchT channelaftert,
					midi_pitchbendT pitchbend,
					midi_systemexclusiveT systemexclusive,
					void* data);

  /**
   * Destroys a midi parser.
   */
  void midi_destroy_parser(struct MidiParser* self);
  
  /**
   * Parses the raw midi data in buf.
   * The buffer must start with a valid midi command.
   * If registered with self, the appropriate callbacks will be called.
   * @param self the MidiParser
   * @param buf a buffer with raw midi data
   * @param len the length of the buffer in bytes
   * @return the number of bytes parsed. If there is an incomplete
   *   midi command at the end of the buffer, the return value can be
   *   smaller than len.
   */
  int midi_parse_data(struct MidiParser* self, const unsigned char* buf,
		      int len);

  /**
   * Register a handler that is called at every noteOff message.
   * @param self the MidiParser
   * @param handler the handler function
   */
  void midi_set_noteoff_handler(struct MidiParser* self,
				midi_noteoffT handler);

  /**
   * Register a handler that is called at every noteOn message.
   * @param self the MidiParser
   * @param handler the handler function
   */
  void midi_set_noteon_handler(struct MidiParser* self,
			       midi_noteonT handler);

  /**
   * Register a handler that is called at every polyphonic aftertouch message.
   * @param self the MidiParser
   * @param handler the handler function
   */
  void midi_set_aftertouch_handler(struct MidiParser* self,
				   midi_aftertouchT handler);


  /**
   * Register a handler that is called at every control change message.
   * @param self the MidiParser
   * @param handler the handler function
   */
  void midi_set_controlchange_handler(struct MidiParser* self,
				      midi_controlchangeT handler);

  /**
   * Register a handler that is called at every program change message.
   * @param self the MidiParser
   * @param handler the handler function
   */
  void midi_set_programchange_handler(struct MidiParser* self,
				      midi_programchangeT handler);

  /**
   * Register a handler that is called at every channel aftertouch message.
   * @param self the MidiParser
   * @param handler the handler function
   */
  void midi_set_channelaftertouch_handler(struct MidiParser* self,
					  midi_channelaftertouchT handler);

  /**
   * Register a handler that is called at every pitch bend message.
   * @param self the MidiParser
   * @param handler the handler function
   */
  void midi_set_pitchbend_handler(struct MidiParser* self,
				  midi_pitchbendT handler);

  /**
   * Register a handler that is called at every system exclusive message.
   * @param self the MidiParser
   * @param handler the handler function
   */
  void midi_set_systemexclusive_handler(struct MidiParser* self,
					midi_systemexclusiveT handler);
#ifdef __cplusplus
}
#endif
#endif
