#include "joystickmodule.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if !defined(COMP_VC)
#include <algorithm>
using std::min;
#endif

#if defined(OS_WIN32)
#include <windows.h>
#define snprintf _snprintf
#endif

#include "midiutil.h"
#include "libjoystick.h"

//---------------------------------------------------------------------

static logT s_log;

static const int MAX_NUM_AXBU = 32;

//---------------------------------------------------------------------

typedef struct _MyInstance
{
  int old_id;
 
  int axis_old[MAX_NUM_AXBU];
  int button_old[MAX_NUM_AXBU];

  JoystickDriver* jst_drv;
  Joystick* jst;
} MyInstance, *MyInstancePtr;


//---------------------------------------------------------------------

static void reset_axbu(MyInstancePtr my)
{
	for (int i = 0; i < MAX_NUM_AXBU; ++i)
	{
		my->axis_old[i]   = -1;
		my->button_old[i] = -1;
	}
}

//---------------------------------------------------------------------

int init(logT log_function)
{
  s_log = log_function;

  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));  

  my->old_id = -1;
  my->jst    = 0;

  reset_axbu(my);
  try
    {
      my->jst_drv = new JoystickDriver("default");
      return my;
    } 
  catch(std::exception& e)
    {
      char buffer[256];
      snprintf(buffer, sizeof(buffer),
               "Could not create joystick driver: '%s'", e.what());
      s_log(0, buffer);
      free(my);
    }
  return 0;
}

void destruct(MyInstance* my)
{  
  if (my->jst != 0)
    delete my->jst;

  delete my->jst_drv;
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;  

  int joy_id = trim_int(inst->in_joy_id->number, 0, 31);
  int i, num_axes, num_buttons;

  if (joy_id != my->old_id)
    {
      char buffer[64];
    
      snprintf(buffer, sizeof(buffer), "Switching from Joystick %i to "
	       "Joystick %i\n",my->old_id, joy_id);
      s_log(2, buffer);

      if (my->jst != 0)
	{
	  delete my->jst;
	  my->jst = 0;
	}

      try
        {
          my->jst = my->jst_drv->open(joy_id);
        }
      catch (std::exception& e)
        {
          s_log(0, e.what());
          my->old_id = joy_id;
          return;                
        }

      my->old_id = joy_id;

      if (my->jst == 0)
	{
	  snprintf(buffer, sizeof(buffer), "Couldn't open Joystick %i",
		   joy_id);
	  s_log(0, buffer);
	  return;
	}
	
	  reset_axbu(my);         
    }
  
  if (my->jst == 0)
    return;
  
  try
  {
	  my->jst->poll();
	  
	  num_axes    = min(my->jst->num_axes(), MAX_NUM_AXBU);
	  num_buttons = min(my->jst->num_buttons(), MAX_NUM_AXBU);
	 
	  double ax[MAX_NUM_AXBU];	  
	  for (i = 0; i < num_axes; ++i)
	  {
		  ax[i] = my->jst->get_axis(i);	  
	  }
	  
	  bool b[MAX_NUM_AXBU];
	  for (i = 0; i < num_buttons; ++i)
	  {
		  b[i] = my->jst->get_button(i);
	  }
	  
  	  unsigned char midi_buffer[MAX_NUM_AXBU*2*3];
	  int len = 0;
	  
	  for (i = 0; i < num_axes; ++i)
	  {
		  int axc = static_cast<int>(127. * ax[i]);	
		  
		  if (axc != my->axis_old[i])
		  {
			  my->axis_old[i]    = axc;
			  midi_buffer[len++] = MIDI_CTRLCHANGE + 0; //channel 0
			  midi_buffer[len++] = i;
			  midi_buffer[len++] = static_cast<unsigned char>(axc);
		  }
	  }

	  for (i = 0; i < num_buttons; ++i)
	  {
		  int bc = b[i] ? 127 : 0;
		  if (bc != my->button_old[i])
		  {
			  my->button_old[i]  = bc;
			  midi_buffer[len++] = MIDI_CTRLCHANGE + 1; //channel 1
			  midi_buffer[len++] = i;
			  midi_buffer[len++] = static_cast<unsigned char>(bc);
		  }    
	  }
	  
	  midi_set_buffer(inst->out_midi, midi_buffer, len);
	  
	  inst->out_signal_x->number = ax[0];
	  inst->out_signal_y->number = ax[1];
	  
	  inst->out_button_1->number = b[0] ? 1.0 : 0.0;
	  inst->out_button_2->number = b[1] ? 1.0 : 0.0;
  }
  catch (std::exception& e)
  {
	  char buffer[128];
	  snprintf(buffer, sizeof(buffer),
		  "Error at poll(): '%s'", e.what());
	  s_log(0, buffer);
  }
}
