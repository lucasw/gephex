#include "libjoystick.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include <stdexcept>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <cassert>
#include <cmath>

#include "joystickdriver.h"

#if defined(OS_WIN32)
#include "win32joystickdriver.h"
#endif

#if defined(OS_LINUX)
#include "linuxjoystickdriver.h"
#endif

#if defined(HAVE_SDL)
#include "sdljoystickdriver.h"
#endif

//--------------------------------------------------------------------

JoystickDriver::JoystickDriver(const std::string& driver_name)
{
#if defined(OS_WIN32)
  if (driver_name == "default")
    {
      m_impl = new Win32JoystickDriverImpl();
    }
  else
#endif
#if defined(OS_LINUX)
  if (driver_name == "default")
    {
      m_impl = new LinuxJoystickDriverImpl();
    }
  else
#endif
#if defined(HAVE_SDL)
    if (driver_name == "sdl" || driver_name == "default")
      {
        m_impl = new SDLJoystickDriverImpl();
      }
    else
#endif
      {
        throw std::invalid_argument("Unknown driver name");
      }
}

JoystickDriver::~JoystickDriver()
{
  delete m_impl;
}

int JoystickDriver::num_devices() const
{
    return m_impl->num_joysticks();
}

std::string JoystickDriver::name(int id) const
{
    return m_impl->joystick_name(id);
}

Joystick* JoystickDriver::open(int id)
{
  // int i = 0;	
    JoystickImpl* jst = m_impl->open_joystick(id);
    return new Joystick(jst);
}


//--------------------------------------------------------------------

Joystick::Joystick(JoystickImpl* jst)
  : m_impl(jst)
{
  int na = m_impl->num_axes();
  int nb = m_impl->num_buttons();
  axis   = std::vector<double>(na);
  button = std::vector<bool>(nb);

  axis_min = std::vector<double>(na);
  axis_max = std::vector<double>(na);
}

Joystick::~Joystick()
{
  delete m_impl;
}

int Joystick::num_axes() const
{
  return m_impl->num_axes();
}

int Joystick::num_buttons() const
{
  return m_impl->num_buttons();
}

void Joystick::poll()
{  
  JoystickDriverImpl* drv = m_impl->driver();

  JoystickState state = m_impl->poll();

  for (int i = 0; i < m_impl->num_axes(); ++i)
    {
      double v = state.axes[i];
      if (v < axis_min[i])
        axis_min[i] = v;
        
      if (v > axis_max[i])
        axis_max[i] = v;
        
      if (drv->center_mode() == JoystickDriverImpl::ZERO_CENTER)
        {
          if (v < 0)
            axis[i] = 0.5 - (v / axis_min[i])*0.5;
          else
            axis[i] = (v / axis_max[i])*0.5 + 0.5;
        }
      else if (drv->center_mode() == JoystickDriverImpl::FLOATING_CENTER)
        {				  				  
          double scale = axis_max[i] - axis_min[i];
          if (scale == 0 || fabs(scale) < fabs(v))
            axis[i] = 0;
          else
            axis[i] = v / scale;
			  
          assert(0 <= axis[i] && axis[i] <= 1);	  
        }
    }

  for (int j = 0; j < m_impl->num_buttons(); ++j)
    {
      button[j] = state.buttons[j];
    }
}

void Joystick::recalibrate()
{
  for (int i = 0; i < m_impl->num_axes(); ++i)
    {
      axis_max[i] = INT_MIN;
      axis_min[i] = INT_MAX;		
    }
}

double Joystick::get_axis(int ax) const
{
  if (ax >= 0 && ax < m_impl->num_axes())
    return axis[ax];
  else
    return 0;
}

bool Joystick::get_button(int but) const
{
  if (but >= 0 && but < m_impl->num_buttons())
    return button[but];
  else
    return 0;
}

