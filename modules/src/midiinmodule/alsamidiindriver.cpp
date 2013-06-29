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

#include "alsamidiindriver.h"

#include <sstream>
#include <stdexcept>

#include <alsa/asoundlib.h>

struct AlsaMidiInDriver::Impl
{
  Impl() : handle_in(0) {}

  snd_rawmidi_t* handle_in;
};

AlsaMidiInDriver::AlsaMidiInDriver()
  : m_impl(new Impl())
{
}

AlsaMidiInDriver::~AlsaMidiInDriver()
{
  if (this->is_open())
    close();
}

void AlsaMidiInDriver::open(device_id_t device)
{
  if (this->is_open())
    throw std::logic_error("Device already open");

  //TODO:
  std::ostringstream os;
  os << "hw:" << device << ",0";
  std::string device_name = os.str();


  int err = snd_rawmidi_open(&m_impl->handle_in, NULL, device_name.c_str(), 
                             SND_RAWMIDI_NONBLOCK);
  if (err)
    {
      std::ostringstream error_msg;
      error_msg << "snd_rawmidi_open '" << device_name << "' failed: "
                << err;
      m_impl->handle_in=0;
      throw std::runtime_error(error_msg.str().c_str());
    }
}

void AlsaMidiInDriver::close()
{
  if (!this->is_open())
    throw std::logic_error("Device not open");

  snd_rawmidi_drain(m_impl->handle_in);
  snd_rawmidi_close(m_impl->handle_in);

  m_impl->handle_in = 0;
}

int AlsaMidiInDriver::read(unsigned char* data, int data_size)
{
  if (!this->is_open())
    throw std::logic_error("Device not open");
  
  int read = snd_rawmidi_read(m_impl->handle_in, data, data_size);
  
  if (read < 0)
    {
      if (read == -EAGAIN)
        return 0;

      throw std::runtime_error("Error at AlsaMidiInDriver::"
                               "snd_raw_midi_read()");
    }
  else
    return read;
}

bool AlsaMidiInDriver::is_open() const
{
  return m_impl->handle_in != 0;
}

//------------------------------------------------------------------

