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

#ifndef INCLUDED_LIB_JOYSTICK_H
#define INCLUDED_LIB_JOYSTICK_H

#include <string>
#include <vector>

/**
 * Simple joystick lib.
 *
 * Usage:
 *  First create a driver with joystick_create_driver().
 *  Using the returned handle you can query for number of joysticks
 *  and joystick names.
 *
 *  Then, open one of the joysticks with joystick_open.
 *  Now you can query the buttons with joystick_get_button()
 *  and the axes with joystick_get_axis().
 *
 *  When done, close the joystick with joystick_close() and
 *  free the driver with joystick_destroy_driver()
 */

class Joystick;
class JoystickDriverImpl;
class JoystickDriver
{
 public:
  /**
   * Valid driver strings are:
   *     "default" for the platforms default driver
   *     "sdl"     for the generic sdl driver
   *
   * \throws std::invalid_argument if driver is an invalid driver string 
   * \throws std::runtime_error if driver initialization fails
   */
  JoystickDriver(const std::string& driver_name);
  ~JoystickDriver();

  /**
   * Returns the number of joysticks.
   */
  int num_devices() const;

  /**
   * Returns the name of an joystick.
   */
  std::string name(int id) const;

  /**
   * Opens a joystick.
   * \throws std::range_error if id is out of range
   * \throws std::runtime_error if open does not succeed.
   */
  Joystick* open(int id);

 private:
  JoystickDriverImpl* m_impl;

  JoystickDriver(const JoystickDriver&); // not impl.
  JoystickDriver& operator=(const JoystickDriver&); // not impl.
};

class JoystickImpl;
class Joystick
{
  public:
  Joystick(JoystickImpl* impl);
  ~Joystick();

  int num_axes() const;
  int num_buttons() const;


  /**
   * Polls the joystick driver for new data.
   * Must be called before get_axis or get_button.
   */
  void poll();

  void recalibrate();

  /**
   * Returns a value between 0 and 1.
   * 0.5 is the center value.
   * If axis < 0 || axis >= get_num_axes(self),
   * the return value is undefined
   */
  double get_axis(int axis) const;


  /**
   * Returns a value between 0 (not pressed) and 1 (pressed).
   * If button < 0 || button is >= get_num_buttons(self),
   * the return value is undefined
   */
  bool get_button(int button) const;

 private:
  JoystickImpl* m_impl;

  std::vector<double> axis;
  std::vector<bool> button;
	
  std::vector<double> axis_min;
  std::vector<double> axis_max;

  Joystick(const Joystick&); // not impl.
  Joystick& operator=(const Joystick&); // not impl.
};




#endif


