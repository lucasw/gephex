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

#include "linuxjoystickdriver.h"

#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>

#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/joystick.h>

class LinuxJoystickImpl : public JoystickImpl
{
public:
  LinuxJoystickImpl(LinuxJoystickDriverImpl* driver, int fd)
    : m_driver(driver), m_handle(fd)
  {
    static const int NAME_LENGTH = 64;
    char name[NAME_LENGTH] = "";
    unsigned char axes    = 2;
    unsigned char buttons = 2;

    ioctl(m_handle, JSIOCGVERSION, &m_version);
    ioctl(m_handle, JSIOCGAXES,    &axes);
    ioctl(m_handle, JSIOCGBUTTONS, &buttons);
    ioctl(m_handle, JSIOCGNAME(NAME_LENGTH), name);

    m_name        = std::string(name, NAME_LENGTH);
    m_num_axes    = std::min(32, static_cast<int>(axes));
    m_num_buttons = std::min(32, static_cast<int>(buttons));

    m_state.axes    = std::vector<int>(m_num_axes, 0);
    m_state.buttons = std::vector<bool>(m_num_buttons, false);
  }

  virtual ~LinuxJoystickImpl()
  {
    close(m_handle);
  }

  JoystickDriverImpl* driver() const
  {
    return m_driver;
  }

  int num_axes() const
  {
    return m_num_axes;
  }
	
  int num_buttons() const
  {
    return m_num_buttons;
  }

  JoystickState poll()
  {
    int max_count = 10;
    while (--max_count) 
      {
        struct timeval tv;
        fd_set readfds;
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        FD_ZERO(&readfds);
        FD_SET(m_handle,&readfds);
        select(m_handle+1,&readfds,0,0,&tv);
        //TODO: handle EINTR

        if (!(FD_ISSET(m_handle, &readfds)))
          return m_state;

        if (m_version < 0x010000) // old version 0.x interface
          {
            struct JS_DATA_TYPE js;

            int len = read(m_handle, &js, JS_RETURN);
            if (len != JS_RETURN)
              {
                throw std::runtime_error("Error while reading");
              }
            m_state.axes[0]    = js.x;
            m_state.axes[1]    = js.y;
            m_state.buttons[0] = js.buttons & 1;
            m_state.buttons[1] = js.buttons & 2;
          }
        else // new event interface
          {
            struct js_event js;

            int len = read(m_handle, &js, sizeof(struct js_event));
            if (len != sizeof(struct js_event))
              {
                throw std::runtime_error("Error while reading");
              }
        
            int index = js.number;
            switch(js.type & ~JS_EVENT_INIT)
              {
              case JS_EVENT_AXIS:
                if (index >= 0 && index < m_num_axes)
                  m_state.axes[index] = js.value;
                break;
              case JS_EVENT_BUTTON:
                if (index >= 0 && index < m_num_buttons)
                  m_state.buttons[index] = js.value;
                break;
              }
          }
      }
    return m_state;
  }

private:
  LinuxJoystickDriverImpl* m_driver;
  int m_handle;
  int m_num_axes;
  int m_num_buttons;
  int m_version;
  std::string m_name;
  JoystickState m_state;
};


LinuxJoystickDriverImpl::LinuxJoystickDriverImpl()
{
  const std::string prfx1 = "/dev/input/";
  const std::string prfx2 = "/dev/";
  int fd;
  fd = open((prfx1+"js0").c_str(), O_RDONLY);
  
  if (fd < 0)
    {
      fd = open((prfx2+"js0").c_str(), O_RDONLY);
      if (fd < 0)
        {
          std::cerr << ("Could not find joystick device");
          m_prefix = prfx1;
        }
      else
        m_prefix = prfx2;
    }
  else
    {
      m_prefix = prfx1;
    }

  if (fd < 0)
    {
      m_version = 0x010000;
    }
  else
    {
      ioctl(fd, JSIOCGVERSION, &m_version);
      close(fd);
    }
}

LinuxJoystickDriverImpl::~LinuxJoystickDriverImpl()
{
}

JoystickDriverImpl::CenterMode LinuxJoystickDriverImpl::center_mode() const
{
  if (m_version >= 0x010000)
    return ZERO_CENTER;
  else
    return FLOATING_CENTER;
}

int LinuxJoystickDriverImpl::num_joysticks() const
{
  for (int i = 0; i < 4; ++i)
    {
      std::ostringstream os;
      os << m_prefix << "js" << i;
      os.flush();

      int fd = open(os.str().c_str(), O_RDONLY);
      if (fd < 0)
        return i;

      close(fd);
    }

  return 4;
}

std::string LinuxJoystickDriverImpl::joystick_name(int id) const
{
  std::ostringstream os;
  os << m_prefix << "js" << id;
  os.flush();

  int fd = open(os.str().c_str(), O_RDONLY);  
  if (fd < 0)
    return "";

  static const int NAME_LENGTH = 64;
  char name[NAME_LENGTH] = "";
  ioctl(fd, JSIOCGNAME(NAME_LENGTH), name);

  close(fd);

  return std::string(name);
}

JoystickImpl* LinuxJoystickDriverImpl::open_joystick(int id)
{
  std::ostringstream os;
  os << m_prefix << "js" << id;
  os.flush();

  int fd = open(os.str().c_str(), O_RDONLY);  
  if (fd < 0)
    throw std::runtime_error("Could not open joystick");
  else
    return new LinuxJoystickImpl(this, fd);
}
