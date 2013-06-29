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

#ifndef INCLUDED_JOYSTICK_DRIVER_H
#define INCLUDED_JOYSTICK_DRIVER_H

#include <string>
#include <vector>

struct JoystickState
{
	std::vector<int>  axes;
	std::vector<bool> buttons;
};

class JoystickDriverImpl;

class JoystickImpl
{
public:
	virtual ~JoystickImpl() {};

	virtual JoystickDriverImpl* driver() const = 0;

	virtual int num_axes() const = 0;
	virtual int num_buttons() const = 0;

	/**
	 * \throws std::runtime_error if operation fails
	 */
	virtual JoystickState poll() = 0;
};

class JoystickDriverImpl
{
public:

	/**
	 *  ZERO_CENTER: a value of zero means that the axis is centered
	 *  FLOATING_CENTER: center is between min and max value
	 */
	enum CenterMode { ZERO_CENTER, FLOATING_CENTER };

	virtual ~JoystickDriverImpl() {};

	/**
	 * returns the way the joystick driver centers its data
	 * (see CenterMode above)
	 */
	virtual CenterMode center_mode() const = 0;

	virtual int num_joysticks() const = 0;

	virtual std::string joystick_name(int id) const = 0;

	/**
 	 * \throws std::runtime_error if open fails
	 */
	virtual JoystickImpl* open_joystick(int id) = 0;
};

#endif
