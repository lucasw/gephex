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

#include "win32joystickdriver.h"

#include <stdexcept>
#include <windows.h>

class Win32JoystickImpl : public JoystickImpl
{
public:
	Win32JoystickImpl(Win32JoystickDriverImpl* driver, int handle)
		: m_driver(driver), m_handle(handle) 
	{
		MMRESULT mr;
		JOYCAPS jc;
		
		mr = joyGetDevCaps(handle, &jc, sizeof(jc));
		
		if (mr != JOYERR_NOERROR)
		{
			throw std::runtime_error("Could not get caps for joystick");
		}
		
		m_num_axes      = jc.wNumAxes;
		m_num_buttons   = jc.wNumButtons;
		m_state.axes    = std::vector<int>(m_num_axes, 0);
		m_state.buttons = std::vector<bool>(m_num_buttons, false);
	}

	virtual ~Win32JoystickImpl()
	{
		
	}

	virtual JoystickDriverImpl* driver() const
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
		MMRESULT hr;
		JOYINFOEX ji;	
		
		ji.dwSize = sizeof(ji);
		ji.dwFlags = JOY_RETURNALL | JOY_RETURNCENTERED |JOY_USEDEADZONE;
		hr = joyGetPosEx( 0,  &ji );
		if (hr != JOYERR_NOERROR)
		{
			throw std::runtime_error("Could not get Joystick Pos!");			
		}
		
		m_state.axes[0] = ji.dwXpos;
		m_state.axes[1] = ji.dwYpos;
		if (m_num_axes > 2)		
			m_state.axes[2] = ji.dwZpos;
		if (m_num_axes > 3)		
			m_state.axes[3] = ji.dwRpos;
		if (m_num_axes > 4)		
			m_state.axes[4] = ji.dwUpos;
		if (m_num_axes > 5)		
			m_state.axes[5] = ji.dwVpos;						

		if (m_num_buttons > 0)
			m_state.buttons[0] = (ji.dwButtons & JOY_BUTTON1) ? 1 : 0;
		
	    if (m_num_buttons > 1)
			m_state.buttons[1] = (ji.dwButtons & JOY_BUTTON2) ? 1 : 0;

		if (m_num_buttons > 2)
			m_state.buttons[2] = (ji.dwButtons & JOY_BUTTON3) ? 1 : 0;

		if (m_num_buttons > 3)
			m_state.buttons[3] = (ji.dwButtons & JOY_BUTTON4) ? 1 : 0;

		return m_state;
	}
		
private:
	Win32JoystickDriverImpl* m_driver;
	int m_handle;
	int m_num_axes;
	int m_num_buttons;
	JoystickState m_state;
};


Win32JoystickDriverImpl::Win32JoystickDriverImpl()
{	
}

Win32JoystickDriverImpl::~Win32JoystickDriverImpl()
{
}

JoystickDriverImpl::CenterMode Win32JoystickDriverImpl::center_mode() const
{
	return FLOATING_CENTER;
}

int Win32JoystickDriverImpl::num_joysticks() const
{
	return joyGetNumDevs();
}

std::string Win32JoystickDriverImpl::joystick_name(int id) const
{
    MMRESULT mr;
	JOYCAPS jc;
	
	mr = joyGetDevCaps(id, &jc, sizeof(jc));
	
	if (mr != JOYERR_NOERROR)
	{
		return "";
	}
	else
		return jc.szPname;
}

JoystickImpl* Win32JoystickDriverImpl::open_joystick(int id)
{
	return new Win32JoystickImpl(this, id);
}
