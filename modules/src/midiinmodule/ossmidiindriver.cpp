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

#include "ossmidiindriver.h"

#include <sstream>
#include <stdexcept>

#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

struct OSSMidiInDriver::Impl
{
  Impl() : fd(-1) {}

  int fd;
};

OSSMidiInDriver::OSSMidiInDriver()
  : m_impl(new Impl())
{
}

OSSMidiInDriver::~OSSMidiInDriver()
{
  if (this->is_open())
    close();
}

void OSSMidiInDriver::open(device_id_t device)
{
  if (this->is_open())
    throw std::logic_error("Device already open");

  std::ostringstream os;
  //TODO
  os << "/dev/midi0" << device;
  std::string device_name = os.str();

  // open the OSS device for reading
  int fd = ::open(device_name.c_str(), O_RDONLY, 0);
  if (fd < 0)
    {
      std::ostringstream os;
      os << "Error: cannot open '" << device_name << "'";
      throw std::runtime_error(os.str().c_str());
    }

  m_impl->fd = fd;
}

void OSSMidiInDriver::close()
{
  if (!this->is_open())
    throw std::logic_error("Device not open");

  ::close(m_impl->fd);
  m_impl->fd = -1;
}

int OSSMidiInDriver::read(unsigned char* data, int data_size)
{
  if (!this->is_open())
    throw std::logic_error("Device not open");
  
  // TODO: only oss under linux seems to support select!
  fd_set readfds;
  struct timeval tv;
  int fd = m_impl->fd;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&readfds);
  FD_SET(fd,&readfds);
  select(fd+1,&readfds,0,0,&tv);
  //TODO: handle EINTR!
  
  if (FD_ISSET(fd, &readfds))
    {
      errno = 0;      
      int len = ::read(fd, data, data_size);
      if (len < 0 && errno != EINTR)
        {
          std::ostringstream os;
          os << "Error at midiinmodule::read -> errno = " << errno;
          throw std::runtime_error(os.str().c_str());
        }
      return len;
    }

  return 0;
}

bool OSSMidiInDriver::is_open() const
{
  return m_impl->fd != -1;
}

//------------------------------------------------------------------

