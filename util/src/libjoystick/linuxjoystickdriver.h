/* Joystick wrapper library.
  Copyright (C) 2003 Georg Seidel
  This file is part of GePhex.

  GePhex is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.
  
  GePhex is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.
    
  You should have received a copy of the GNU General Public
  License along with GePhex; if not, write to the Free
  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  02111-1307 USA.  
      
  You can reach me via email: georg.seidel@web.de
*/

#ifndef INCLUDED_LINUX_JOYSTICK_DRIVER_H
#define INCLUDED_LINUX_JOYSTICK_DRIVER_H

#include "joystickdriver.h"

class LinuxJoystickDriverImpl : public JoystickDriverImpl
{
public:
	LinuxJoystickDriverImpl();
	virtual ~LinuxJoystickDriverImpl();

	CenterMode center_mode() const;

	int num_joysticks() const;

	std::string joystick_name(int id) const;

	JoystickImpl* open_joystick(int id);

 private:
        std::string m_prefix;
        int m_version;
};
#endif
