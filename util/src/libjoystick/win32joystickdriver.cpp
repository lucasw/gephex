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
		hr = joyGetPosEx( m_handle,  &ji );
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
		if (m_num_buttons > 4)
			m_state.buttons[4] = (ji.dwButtons & JOY_BUTTON5) ? 1 : 0;
	    if (m_num_buttons > 5)
			m_state.buttons[5] = (ji.dwButtons & JOY_BUTTON6) ? 1 : 0;
		if (m_num_buttons > 6)
			m_state.buttons[6] = (ji.dwButtons & JOY_BUTTON7) ? 1 : 0;
		if (m_num_buttons > 7)
			m_state.buttons[7] = (ji.dwButtons & JOY_BUTTON8) ? 1 : 0;
		if (m_num_buttons > 8)
			m_state.buttons[8] = (ji.dwButtons & JOY_BUTTON9) ? 1 : 0;
	    if (m_num_buttons > 9)
			m_state.buttons[9] = (ji.dwButtons & JOY_BUTTON10) ? 1 : 0;
		if (m_num_buttons > 10)
			m_state.buttons[10] = (ji.dwButtons & JOY_BUTTON11) ? 1 : 0;
		if (m_num_buttons > 11)
			m_state.buttons[11] = (ji.dwButtons & JOY_BUTTON12) ? 1 : 0;
		if (m_num_buttons > 12)
			m_state.buttons[12] = (ji.dwButtons & JOY_BUTTON13) ? 1 : 0;
	    if (m_num_buttons > 13)
			m_state.buttons[13] = (ji.dwButtons & JOY_BUTTON14) ? 1 : 0;
		if (m_num_buttons > 14)
			m_state.buttons[14] = (ji.dwButtons & JOY_BUTTON15) ? 1 : 0;
		if (m_num_buttons > 15)
			m_state.buttons[15] = (ji.dwButtons & JOY_BUTTON16) ? 1 : 0;
        if (m_num_buttons > 16)
			m_state.buttons[16] = (ji.dwButtons & JOY_BUTTON17) ? 1 : 0;
	    if (m_num_buttons > 17)
			m_state.buttons[17] = (ji.dwButtons & JOY_BUTTON18) ? 1 : 0;
		if (m_num_buttons > 18)
			m_state.buttons[18] = (ji.dwButtons & JOY_BUTTON19) ? 1 : 0;
		if (m_num_buttons > 19)
			m_state.buttons[19] = (ji.dwButtons & JOY_BUTTON20) ? 1 : 0;
		if (m_num_buttons > 20)
			m_state.buttons[20] = (ji.dwButtons & JOY_BUTTON21) ? 1 : 0;
		if (m_num_buttons > 21)
			m_state.buttons[21] = (ji.dwButtons & JOY_BUTTON22) ? 1 : 0;
	    if (m_num_buttons > 22)
			m_state.buttons[22] = (ji.dwButtons & JOY_BUTTON23) ? 1 : 0;
		if (m_num_buttons > 23)
			m_state.buttons[23] = (ji.dwButtons & JOY_BUTTON24) ? 1 : 0;
		if (m_num_buttons > 24)
			m_state.buttons[24] = (ji.dwButtons & JOY_BUTTON25) ? 1 : 0;
		if (m_num_buttons > 25)
			m_state.buttons[25] = (ji.dwButtons & JOY_BUTTON26) ? 1 : 0;
	    if (m_num_buttons > 26)
			m_state.buttons[26] = (ji.dwButtons & JOY_BUTTON27) ? 1 : 0;
		if (m_num_buttons > 27)
			m_state.buttons[27] = (ji.dwButtons & JOY_BUTTON28) ? 1 : 0;
		if (m_num_buttons > 28)
			m_state.buttons[28] = (ji.dwButtons & JOY_BUTTON29) ? 1 : 0;
        if (m_num_buttons > 29)
			m_state.buttons[29] = (ji.dwButtons & JOY_BUTTON30) ? 1 : 0;
	    if (m_num_buttons > 30)
			m_state.buttons[30] = (ji.dwButtons & JOY_BUTTON31) ? 1 : 0;
		if (m_num_buttons > 31)
			m_state.buttons[31] = (ji.dwButtons & JOY_BUTTON32) ? 1 : 0;

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
