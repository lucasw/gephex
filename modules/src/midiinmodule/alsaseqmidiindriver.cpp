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

#include "alsaseqmidiindriver.h"

#include <sstream>
#include <stdexcept>

#include <alsa/asoundlib.h>

struct AlsaSeqMidiInDriver::Impl
{
  Impl() : seq(0),decoder(0) {}

  snd_seq_t *seq;
  snd_midi_event_t *decoder;
  snd_seq_event_t SEv;
  int portid;
};

AlsaSeqMidiInDriver::AlsaSeqMidiInDriver()
  : m_impl(new Impl())
{
}

AlsaSeqMidiInDriver::~AlsaSeqMidiInDriver()
{
  if (this->is_open())
    close();
}

void AlsaSeqMidiInDriver::open(device_id_t device)
{
  if (this->is_open())
    throw std::logic_error("Device already open");

  int err;

  err = snd_seq_open(&m_impl->seq, "default", SND_SEQ_OPEN_INPUT,
		     SND_SEQ_NONBLOCK);
  
  if ( err < 0)
    {
      throw std::runtime_error("Error opening ALSA sequencer.");
    }

  std::ostringstream os;
  os << "gephex input " << device;
  std::string device_name = os.str();
  
  err = snd_seq_set_client_name(m_impl->seq, device_name.c_str());


  err = snd_seq_create_simple_port(m_impl->seq, device_name.c_str(),
				   SND_SEQ_PORT_CAP_WRITE|
				   SND_SEQ_PORT_CAP_SUBS_WRITE,
				   SND_SEQ_PORT_TYPE_APPLICATION);

  if (err < 0)
    {
      snd_seq_close (m_impl->seq);
      throw std::runtime_error("Error creating sequencer port.");
    }
  else
    {
      m_impl->portid =  err;
      snd_seq_ev_clear (&m_impl->SEv);
      snd_seq_ev_set_source (&m_impl->SEv, m_impl->portid);
      snd_seq_ev_set_subs (&m_impl->SEv);
      snd_seq_ev_set_direct (&m_impl->SEv);
    }

  if( snd_midi_event_new (32, &m_impl->decoder) )
    throw std::runtime_error ("Error creating midi event parser");

  snd_midi_event_init(m_impl->decoder);
  snd_midi_event_no_status (m_impl->decoder,1);
}

void AlsaSeqMidiInDriver::close()
{
  if (!this->is_open())
    throw std::logic_error("Device not open");

  if (m_impl->decoder)
    snd_midi_event_free (m_impl->decoder);
  
  snd_seq_close(m_impl->seq);
  m_impl->seq=0;
}

int AlsaSeqMidiInDriver::read(unsigned char* buf, int max)
{
  if (!this->is_open())
    throw std::logic_error("Device not open");

  int bytes_read= 0;
  int err;
  snd_seq_event_t *ev;

  do
    {
      if (snd_seq_event_input(m_impl->seq, &ev) > 0 )
	{
	  err = snd_midi_event_decode (m_impl->decoder, buf, max, ev);
	  //snd_seq_free_event( ev );
	  
	  if (err > 0)
	    {
	      buf += err;
	      bytes_read += err;
	      max -= err;
	    }
	  else
	    {
	      // error or buffer full -> drop midi event
	    }
	}
    }
  while (snd_seq_event_input_pending(m_impl->seq, 0) > 0);

  return bytes_read;
}
  
bool AlsaSeqMidiInDriver::is_open() const
{
  return m_impl->seq != 0;
}

//------------------------------------------------------------------

