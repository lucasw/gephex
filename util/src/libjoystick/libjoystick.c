#include "libjoystick.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#include <windows.h>
#elif defined(OS_POSIX)
#include <SDL.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <math.h>

#if defined(OS_POSIX)
typedef SDL_Joystick* JoystickHandle;
#elif defined(OS_WIN32)
typedef int JoystickHandle;
#endif

struct JoystickDevCaps {
	int num_axes;
	int num_buttons;
};

#define JOY_MAX_AXES 16
#define JOY_MAX_BUTTONS 16

struct Joystick {
	JoystickHandle jst;
	
	struct JoystickDevCaps caps;
	
	double axis[JOY_MAX_AXES];
    int button[JOY_MAX_BUTTONS];
	
	double axis_min[JOY_MAX_AXES];
    double axis_max[JOY_MAX_AXES];
};

const char* joystick_get_name(int id)
{
	const char* name = 0;
#if defined(OS_POSIX)
	name = SDL_JoystickName(id);
#elif defined(OS_WIN32)
	MMRESULT mr;
	JOYCAPS jc;
	
	mr = joyGetDevCaps(id, &jc, sizeof(jc));
	
	if (mr != JOYERR_NOERROR)
	{
		name = 0;
	}
	else
		name = jc.szPname;
#endif

	return name;
}

int joystick_get_num_axes(const struct Joystick* self)
{
	return self->caps.num_axes;
}

int joystick_get_num_buttons(const struct Joystick* self)
{
	return self->caps.num_buttons;
}

// returns 0 on success
static int getDevCaps(struct JoystickDevCaps* caps, JoystickHandle joy_id)
{
#if defined(OS_WIN32)
	MMRESULT mr;
	JOYCAPS jc;
	
	mr = joyGetDevCaps(joy_id, &jc, sizeof(jc));
	
	if (mr != JOYERR_NOERROR)
	{
		//TODO
		caps->num_axes = caps->num_buttons = 0;
		return -1;
	}
	
	caps->num_axes    = jc.wNumAxes;
	caps->num_buttons = jc.wNumButtons;
#elif defined(OS_POSIX)
	caps->num_axes    = SDL_JoystickNumAxes(joy_id);
	caps->num_buttons = SDL_JoystickNumButtons(joy_id);
#endif
	
	return 0;
}

struct Joystick* joystick_open(int id)
{
  // int i = 0;
	struct Joystick* jst = (struct Joystick*) malloc(sizeof(*jst));
	
#if defined(OS_POSIX)
	//printf("%i joystick(s) were found.\n\n", SDL_NumJoysticks() );
	/*	printf("The names of the joysticks are:\n");
	
	for( i=0; i < SDL_NumJoysticks(); i++ ) 
    {
		printf("    %s\n", SDL_JoystickName(i));
		}*/
	
	jst->jst = SDL_JoystickOpen(id);
	
	if (jst->jst == 0)
    {
      //		printf("Couldn't open Joystick %i\n", id);
		free(jst);
		return 0;
    }
	
	
#elif defined(OS_WIN32)
	jst->jst = id;  
#endif
	
	if (getDevCaps(&jst->caps, jst->jst) != 0)
	{
		printf("Couldn't get dev caps for jst %i\n", id);
		free(jst);
		return 0;
	}
	
	joystick_recalibrate(jst);
	
	return jst;
}

void joystick_close(struct Joystick* self)
{
#if defined(OS_POSIX)
	SDL_JoystickClose(self->jst);
#endif
	if (self != 0)
		free(self);
}

int joystick_poll(struct Joystick* self)
{  
  int i;
#if defined (OS_POSIX)
	SDL_JoystickUpdate();
	
	for (i = 0; i < self->caps.num_axes; ++i)
	{
		double v = SDL_JoystickGetAxis(self->jst, i);	  
		
		if (v < self->axis_min[i])
			self->axis_min[i] = v;
		
		if (v > self->axis_max[i])
			self->axis_max[i] = v;
		
		
		if (v < 0)
			self->axis[i] = 0.5 - (v / self->axis_min[i])*0.5;
		else
			self->axis[i] = (v / self->axis_max[i])*0.5 + 0.5;
		
	}
	
	/*   printf("Joystick Position: (%f, %f)\n", xs, ys);
	printf("Normalized Pos   : (%f, %f)\n", x, y);
	printf("(xmin,xmax) = (%i,%i)\n(ymin,ymax) = (%i,%i)\n",
	xmin, xmax, ymin, ymax);*/
	
	for (i = 0; i < self->caps.num_buttons; ++i)
	{
		self->button[i] = (SDL_JoystickGetButton(self->jst, i) != 0) ? 1 : 0;
	}
	
	
#elif defined (OS_WIN32)
    {
		MMRESULT hr;
		JOYINFOEX ji;
		
		ji.dwSize = sizeof(ji);
		ji.dwFlags = JOY_RETURNALL | JOY_RETURNCENTERED |JOY_USEDEADZONE;
		hr = joyGetPosEx( 0,  &ji );
		if (hr != JOYERR_NOERROR)
		{
			printf("Could not get Joystick Pos!");
			return -1;
		}
		
		self->axis[0] = ji.dwXpos;
		self->axis[1] = ji.dwYpos;
		if (self->caps.num_axes > 2)
		{
			self->axis[2] = ji.dwZpos;
		}
		
		for (i = 0; i < self->caps.num_axes; ++i) {
			double scale;
			double v =
				(i == 0) ? ji.dwXpos :
				(i == 1) ? ji.dwYpos :
				(i == 2) ? ji.dwZpos : 
				(i == 3) ? ji.dwRpos :
				(i == 4) ? ji.dwUpos :
				(i == 5) ? ji.dwVpos : 0;
				
			if (v < self->axis_min[i])
				self->axis_min[i] = v;
			
			if (v > self->axis_max[i])
				self->axis_max[i] = v;
			
			scale = self->axis_max[i] - self->axis_min[i];
			if (scale == 0 || fabs(scale) < fabs(v))
				self->axis[i] = 0;
			else
				self->axis[i] = v / scale;

			assert(0 <= self->axis[i] <= 1);
		}
		
		self->button[0] = (ji.dwButtons & JOY_BUTTON1) ? 1 : 0;
		self->button[1] = (ji.dwButtons & JOY_BUTTON2) ? 1 : 0;
		self->button[2] = (ji.dwButtons & JOY_BUTTON3) ? 1 : 0;
		self->button[3] = (ji.dwButtons & JOY_BUTTON4) ? 1 : 0;
	}
#endif
	
	return -1;
}

void joystick_recalibrate(struct Joystick* self)
{
	int i;
	for (i = 0; i < self->caps.num_axes; ++i)
	{
		self->axis_max[i] = INT_MIN;
		self->axis_min[i] = INT_MAX;
		
	}
}

double joystick_get_axis(const struct Joystick* self, int axis)
{
	if (axis < self->caps.num_axes)
		return self->axis[axis];
	else
		return 0;
}

/**
* Returns a value between 0 (not pressed) and 1 (pressed).
* If button is >= get_num_buttons(self), the return value is undefined
*/
int joystick_get_button(const struct Joystick* self, int button)
{
	if (button < self->caps.num_buttons)
		return self->button[button];
	else
		return 0;
}

void joystick_init_core()
{
#if defined(OS_POSIX)
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
#endif
}

int joystick_get_num_devices()
{
#if defined(OS_POSIX)
	return SDL_NumJoysticks();
#elif defined(OS_WIN32)
	return joyGetNumDevs();
#endif
}
