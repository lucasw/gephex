#include "timesourcemodule.h"

#include "config.h"

#if defined(OS_POSIX)
#include <sys/time.h>
#elif defined(OS_WIN32)
#define snprintf _snprintf
#include <sys/timeb.h>
#endif

#define REAL_MODE 0
#define RELATIVE_MODE 1

static const double TIME_STEP = 1 / 25.;

static double time_in_secs()
{
  double time;
#if defined(OS_POSIX)
  struct timeval tv;
  gettimeofday(&tv, 0);
  time = (double) tv.tv_sec + (double) tv.tv_usec/1000000.;
#elif defined(OS_WIN32)
  struct _timeb timebuffer;	

  _ftime( &timebuffer );

  time = (double) timebuffer.time + (double) timebuffer.millitm/1000.;
#endif

  return time;
}


static logT s_log;

typedef struct _MyInstance 
{
  StringType mode_text;
  int    mode;
  double relative_time;
} MyInstance, *MyInstancePtr;

/**
 * Must be called exactly once per update
 * (because it increases the relative time).
 */
static double get_time(MyInstancePtr my)
{
  switch (my->mode)
    {
    case REAL_MODE:
      return time_in_secs();
    case RELATIVE_MODE:
      {
        double t = my->relative_time;
        my->relative_time += TIME_STEP;
        return t;
      }
    default:		
      s_log(0, "Invalid internal mode!!!");
      return 0;
    }
}


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

  if (my == 0)
  {
          s_log(0, "Could not allocate memory for MyInstance struct\n");
          return 0;
  }

  my->mode              = REAL_MODE;
  my->relative_time     = 0;
  string_initInstance(&my->mode_text);

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  int mode_changed    = 0;

  if (strcmp(my->mode_text.text, inst->in_mode->text) != 0)
    {
      string_assign(&my->mode_text, inst->in_mode);

      mode_changed = 1;
        
      if (strcmp(my->mode_text.text, "real") == 0)
        {
          my->mode = REAL_MODE;
        }
      else if (strcmp(my->mode_text.text, "relativ") == 0)
        {     
          my->mode = RELATIVE_MODE;
        }
      else
        {
          char buffer[128];
          snprintf(buffer, sizeof(buffer),
                   "Unsupported mode: '%s', using 'real' instead",
                   my->mode_text.text);
            
          s_log(0, buffer);
          my->mode = REAL_MODE;
        }
    }

    double time = get_time(my);

    inst->out_Time->number = time;
}

