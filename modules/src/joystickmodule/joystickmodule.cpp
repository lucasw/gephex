#include "joystickmodule.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#include <windows.h>
#define snprintf _snprintf
#endif

#include "midiutil.h"
#include "libjoystick.h"

static int number_of_joysticks;

static logT s_log;


typedef struct _MyInstance {

  unsigned int old_id;
 
  unsigned char axis_old[32];
  unsigned char button_old[32];

  JoystickDriver* jst_drv;
  Joystick* jst;
} MyInstance, *MyInstancePtr;


int init(logT log_function)
{
  s_log = log_function;


  /*joystick_init_core();
  number_of_joysticks = joystick_get_num_devices();

  {
    char buffer[128];
    snprintf(buffer, sizeof(buffer),
	     "Number of Joysticks found: %i", number_of_joysticks);
    s_log(2, buffer);
  }*/
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));  

  my->old_id = -1;
  my->jst = 0;

  try
    {
      my->jst_drv = new JoystickDriver("default");
      return my;
    } 
  catch(...)
    {
      s_log(0, "Could not create joystick driver");
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
  double ax[32];
  int b[32];

  unsigned int joy_id = trim_int(inst->in_joy_id->number, 0, 32);
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
	
      num_axes = my->jst->num_axes();
      for (i = 0; i < num_axes; ++i)
	{
	  my->axis_old[i]   = -1;
	}    
    }
  
  if (my->jst == 0)
    return;

  my->jst->poll();

  num_axes = my->jst->num_axes();
  num_buttons = my->jst->num_buttons();

  for (i = 0; i < num_axes; ++i)
    {
      ax[i] = my->jst->get_axis(i);	  
    }

  for (i = 0; i < num_buttons; ++i)
    {
      b[i] = my->jst->get_button(i);
    }

  {
    unsigned char midi_buffer[64];
    int len = 0;
	

    for (i = 0; i < num_axes; ++i)
      {
	unsigned char axc;
	axc = (unsigned char) (127. * ax[i]);	
		
	if (axc != my->axis_old[i])
	  {
	    my->axis_old[i] = axc;
	    midi_buffer[len++] = MIDI_CTRLCHANGE + 0; //channel 0
	    midi_buffer[len++] = i;
	    midi_buffer[len++] = axc;
	  }
      }	
    for (i = 0; i < num_buttons; ++i)
      {
	if (b[i] != my->button_old[i])
	  {
	    my->button_old[i] = b[i];
	    midi_buffer[len++] = MIDI_CTRLCHANGE + 1; //channel 1
	    midi_buffer[len++] = i;
	    midi_buffer[len++] = b[i]*127;
	  }    
      }

    midi_set_buffer(inst->out_midi, midi_buffer, len);

    inst->out_signal_x->number = ax[0];
    inst->out_signal_y->number = ax[1];
    
    inst->out_button_1->number = b[0];
    inst->out_button_2->number = b[1];
  }

}
