#include "midiinmodule.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

static logT s_log;

#if defined(OS_POSIX)
#include "ossmidiindriver.h"
#elif defined(OS_WIN32)
#include "wavemidiindriver.h"
#endif

typedef struct _MyInstance {

  int device;
  MidiInDriver* drv;

} MyInstance, *MyInstancePtr;

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

  my->device = -1;

#if defined(OS_POSIX)
  my->drv = new OSSMidiInDriver();
#elif defined(OS_WIN32)
  my->drv = new WaveMidiInDriver();
#endif

  return my;
}

void destruct(MyInstance* my)
{
  my->device = -1;

  if (my->drv)
  {
	  delete my->drv;
	  my->drv = 0;
  }

  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  int device = trim_int(inst->in_device->number, 0, 256);

  assert(my->drv);
  if (device != my->device || !my->drv->is_open())
  {
	  my->device = device;
	  
	  if (my->drv->is_open())
		  my->drv->close();
	  
	  try
	  {
		  my->drv->open(device);
	  }
	  catch (std::exception& e)
	  {
		  char buf[128];
		  snprintf(buf, sizeof(buf), "Error while opening: %s", e.what());
		  s_log(0, buf);
	  }      
  }

  if (!my->drv->is_open())
	  return;
  
  try
  {
	  static const int MAX_MSG_LEN = 1024;
	  unsigned char buffer[MAX_MSG_LEN];
	  int len = my->drv->read(buffer, sizeof(buffer));

	  midi_set_buffer(inst->out_r, buffer, len);
  }
  catch (std::exception& e)
  {
	  char buf[128];
	  snprintf(buf, sizeof(buf), "Error while reading: %s", e.what());
	  s_log(0, buf);
  }
  
}

