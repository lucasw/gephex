#include "joystickmodule.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#include <windows.h>
#include <Mmsystem.h>
#elif defined(OS_POSIX)
#include "SDL.h"
#endif

static int number_of_joysticks;

typedef struct _MyInstance {

 int xmin;
 int xmax;
 int ymin;
 int ymax;

 unsigned int old_id;

#if defined(OS_POSIX)
  SDL_Joystick* jst;
#endif

} MyInstance, *MyInstancePtr;

// returns 0 on success
/*int getDevCaps(MyInstance* my, unsigned int joy_id)
{
	MMRESULT mr;
	JOYCAPS caps;

	mr = joyGetDevCaps(joy_id, &caps, sizeof(caps));

	if (mr != JOYERR_NOERROR)
	{
		//TODO
		return -1;
	}

	my->xmin = caps.wXmin;
	my->ymin = caps.wYmin;
	my->xmax = caps.wXmax;
	my->ymax = caps.wYmax;



	return 0;
}*/

int init(logT log_function)
{

#if defined(OS_POSIX)
  if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
    if(SDL_Init(SDL_INIT_JOYSTICK) == -1)
      {
	if(SDL_InitSubSystem(SDL_INIT_JOYSTICK)==-1)
	  {
	    return 0;
	  }
      }
    else
      {
	//	atexit(SDL_QUIT);
      }
    }

  SDL_JoystickEventState(SDL_IGNORE);
  number_of_joysticks = SDL_NumJoysticks();

  printf("Number of Joysticks found: %i\n", number_of_joysticks);
#elif defined(OS_WIN32)
  number_of_joysticks = joyGetNumDevs();
#endif
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));  

  my->old_id = -1;
  my->xmin = my->ymin = 0;
  my->xmax = my->ymax = 1;

#if defined(OS_POSIX)
  my->jst = 0;
#endif

  return my;
}

void destruct(MyInstance* my)
{  
#if defined(OS_POSIX)
  if (SDL_JoystickOpened(my->old_id))
    SDL_JoystickClose(my->jst);
#endif
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  double x, y, xs, ys;
  int b1, b2;

#if defined(OS_WIN32)
  MMRESULT hr;
  JOYINFO ji;
#endif

  unsigned int joy_id = inst->in_joy_id->number;

  if (joy_id != my->old_id)
  {
    /*int err;

	  err = getDevCaps(my, joy_id);	  

	  if (err != 0)
	  {
		  printf("Could not get Joystick DevCaps!\n");
		  return;
	  }*/

#if defined(OS_POSIX)
    if (SDL_JoystickOpened(my->old_id))
	SDL_JoystickClose(my->jst);

    my->jst = SDL_JoystickOpen(joy_id);

    if (my->jst == 0)
      {
	printf("Couldn't open Joystick %i\n", joy_id);
      }
#endif

	  my->xmin = UINT32_MAX;
	  my->ymin = UINT32_MAX;
	  my->xmax = 0;
	  my->ymax = 0;


	  my->old_id = joy_id;
  }
  
#if defined(OS_WIN32)
  hr = joyGetPos( 0,  &ji );
  if (hr != JOYERR_NOERROR)
  {
	  printf("Could not get Joystick Pos!\n");
	  return;
  }
  x = ji.wXpos;
  y = ji.wYpos;

  if (x < my->xmin)
    my->xmin = x;
  
  if (x > my->xmax)
    my->xmax = x;
  
  if (y < my->ymin)
    my->ymin = y;
  
  if (y > my->ymax)
    my->ymax = y;

  x = (double) x / (double) (my->xmax - my->xmin);
  y = 1.0 - (double) y / (double) (my->ymax - my->ymin);

  b1 = ji.wButtons & JOY_BUTTON1;
  b2 = ji.wButtons & JOY_BUTTON2;
#elif defined(OS_POSIX)
  SDL_JoystickUpdate();

  xs = SDL_JoystickGetAxis(my->jst, 0);
  ys = SDL_JoystickGetAxis(my->jst, 1);


  if (xs < my->xmin)
    my->xmin = xs;
  
  if (xs > my->xmax)
    my->xmax = xs;
  
  if (ys < my->ymin)
    my->ymin = ys;
  
  if (ys > my->ymax)
    my->ymax = ys;

  if (xs < 0)
    x = 0.5 - (xs / my->xmin)*0.5;
  else
    x = (xs / my->xmax)*0.5 + 0.5;

  if (ys < 0)
    y = 0.5 - (ys / my->ymin)*0.5;
  else
    y = (ys / my->ymax)*0.5 + 0.5;

  /*  printf("Joystick Position: (%f, %f)\n", xs, ys);
  printf("Normalized Pos   : (%f, %f)\n", x, y);
  printf("(xmin,xmax) = (%i,%i)\n(ymin,ymax) = (%i,%i)\n",
  my->xmin, my->xmax, my->ymin, my->ymax);*/

  b1 = SDL_JoystickGetButton(my->jst, 0);
  b2 = SDL_JoystickGetButton(my->jst, 1);
#endif
  {

    inst->out_signal_x->number = (uint_32) (x * UINT32_MAX);
    inst->out_signal_y->number = (uint_32) (y * UINT32_MAX);
    
    inst->out_button_1->number = b1 * UINT32_MAX;
    inst->out_button_2->number = b2 * UINT32_MAX;
  }

}
