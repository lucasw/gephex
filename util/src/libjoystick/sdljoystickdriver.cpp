#include "sdljoystickdriver.h"

#include <stdexcept>
#include <SDL.h>

class SDLJoystickImpl : public JoystickImpl
{
public:
	SDLJoystickImpl(SDLJoystickDriverImpl* driver, 
		        SDL_Joystick* handle, int id)
		: m_driver(driver), m_handle(handle), m_id(id) 
	{
		m_num_axes    = SDL_JoystickNumAxes(m_handle);
		m_num_buttons = SDL_JoystickNumButtons(m_handle);
		m_state.axes    = std::vector<int>(m_num_axes);
		m_state.buttons = std::vector<bool>(m_num_buttons);

	}

	virtual ~SDLJoystickImpl()
	{
		SDL_JoystickClose(m_handle);
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
	   SDL_JoystickUpdate();

	   for (int i = 0; i < m_num_axes; ++i)
	   {
		   m_state.axes[i] = SDL_JoystickGetAxis(m_handle, i);
	   }

	   for (int j = 0; j < m_num_buttons; ++j)
	   {
		   m_state.buttons[j] = (SDL_JoystickGetButton(m_handle, j) != 0) ? true : false;
	   }

	   return m_state;
	}
		
private:
	SDLJoystickDriverImpl* m_driver;
	SDL_Joystick* m_handle;
	int m_id;
	int m_num_axes;
	int m_num_buttons;
	JoystickState m_state;

};


SDLJoystickDriverImpl::SDLJoystickDriverImpl()
{
	if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
		if(SDL_Init(SDL_INIT_JOYSTICK) == -1)
		{
			if(SDL_InitSubSystem(SDL_INIT_JOYSTICK)==-1)
			{
				return;
			}
		}
		else
		{
			//TODO: when activated, produces a segfault at shutdown
			//	atexit(SDL_QUIT);
		}
    }
	
	SDL_JoystickEventState(SDL_IGNORE);
}

SDLJoystickDriverImpl::~SDLJoystickDriverImpl()
{
}

JoystickDriverImpl::CenterMode SDLJoystickDriverImpl::center_mode() const
{
	return ZERO_CENTER;
}

int SDLJoystickDriverImpl::num_joysticks() const
{
	return SDL_NumJoysticks();
}

std::string SDLJoystickDriverImpl::joystick_name(int id) const
{
	return SDL_JoystickName(id);
}

JoystickImpl* SDLJoystickDriverImpl::open_joystick(int id)
{
	SDL_Joystick* handle = SDL_JoystickOpen(id);
	
	if (handle == 0)    
		throw std::runtime_error("Could not open joystick");
    else
		return new SDLJoystickImpl(this, handle, id);
}
