#include "signalgenmodule.h"

#include <limits.h>
#include <math.h>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_POSIX)
#include <sys/time.h>
#elif defined(OS_WIN32)
#define snprintf _snprintf
#include <sys/timeb.h>
#endif

#ifndef M_PI
#define M_PI 3.1415
#endif

static logT s_log;

typedef double (*signalT)(double t, double f, double amp, void*);

static double sinus_signal(double t, double f, double amp, void*);
static double rampen_signal(double t, double f, double amp, void*);
static double saege_signal(double t, double f, double amp, void*);
static double rechteck_signal(double t, double f, double amp, void*);
static double noize_signal(double t, double f, double amp, void*);

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

struct NoizeData {
  double* values;
  int size;
  int pos;
};

typedef struct _MyInstance {  
  StringType routine_text;
  StringType mode_text;
  signalT signal;
  int mode;
  double relative_time;

  struct NoizeData noize_data;
} MyInstance, *MyInstancePtr;


/**
 * Must be called exactly once per update (because it increases the relative time).
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
  
  my->signal = 0;
	
  my->noize_data.values = 0;
  my->noize_data.size = 0;
  my->noize_data.pos = 0;

  my->mode = REAL_MODE;
  my->relative_time = 0;

  string_initInstance(&my->routine_text);
  string_initInstance(&my->mode_text);

  return my;
}

void destruct(MyInstance* my)
{ 
  string_destroyInstance(&my->routine_text);
  string_destroyInstance(&my->mode_text);

  if (my->noize_data.values != 0)
    {
      free(my->noize_data.values);
      my->noize_data.values = 0;
    }
  my->noize_data.size = 0;

  free(my);
}

void update(void* instance)
{
    InstancePtr inst = (InstancePtr) instance;
    MyInstancePtr my = inst->my;
    
    double amp = inst->in_Amplitude->number / 2.0;
    double freq = inst->in_Frequenz->number;
    double shift = trim_double(inst->in_Phase->number, 0, 1);
    
    double trans = inst->in_Position->number;
    double result;    
    
    if (strcmp(my->routine_text.text, inst->in_signal->text) != 0)
    {
        string_assign(&my->routine_text, inst->in_signal);
        
        if (strcmp(my->routine_text.text, "sinus") == 0)
        {
            my->signal = sinus_signal;
        }
        else if (strcmp(my->routine_text.text, "rampe") == 0)
        {     
            my->signal = rampen_signal;
        }
        else if (strcmp(my->routine_text.text, "saegezahn") == 0)
        {     
            my->signal = saege_signal;
        }
        else if (strcmp(my->routine_text.text, "rechteck") == 0)
        {     
            my->signal = rechteck_signal;
        }
        else if (strcmp(my->routine_text.text, "noize") == 0)
        {     
            my->signal = noize_signal;
            
            if (my->noize_data.values == 0)
            {
                int n = 33;
                my->noize_data.values = (double*) malloc(sizeof(double) * n);
                my->noize_data.size = n;
                my->noize_data.pos = n;
            }
        }
        else
        {
            char buffer[128];
            snprintf(buffer, sizeof(buffer),
                "Unsupported signal routine: '%s', using 'sinus' instead",
                my->routine_text.text);
            
            s_log(0, buffer);
            my->signal = sinus_signal;
        }
    }

	if (strcmp(my->mode_text.text, inst->in_mode->text) != 0)
    {
        string_assign(&my->mode_text, inst->in_mode);
        
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
    
    {
        double T;
        double time = get_time(my);
        
        
        if (fabs(freq) > 0.00001)
            T = 1.0 / freq;
        else
            T = 0;
        
        time += shift*T;
        result = my->signal(time, freq, amp, &my->noize_data);
        
        inst->out_Signal->number = (result + trans);
        
    }
}

/*****************************************************************************/

static double sinus_signal(double t, double f, double amp, void* d)
{
    return (amp*(1.0+sin(2*M_PI*f*t)));
}

static double saege_signal(double t, double f, double amp, void* d)
{
    double T = 1.0 / f;
    double time = fmod(t, T);
    
    if (time < 0.5*T)
        return (amp * 4.0 * f * time);
    else
        return 4.0*amp - (amp * 4.0 * f * time);
}

static double rampen_signal(double t, double f, double amp, void* d)
{
    double time = fmod(t, 1.0 / f);
    return (amp * 2.0 * f * time);
}

static double rechteck_signal(double t, double f, double amp, void* d)
{
    double T = 1.0 / f;
    double time = fmod(t, T);
    
    if (time < 0.5*T)
        return 2*amp;
    else
        return 0;
}

static void noize_fill_data(struct NoizeData* noize_data, double f, double amp)
{
    int size = noize_data->size;
    int n = size;
    int k = (int) (log(size) / log(2));
    double sigma = 1;
    double* values = noize_data->values;
    double a;
    if (f < 0.999)
        a = amp / (1 + (1-f) - (1-pow(f,k+1)));
    else
        a = amp / (k+1);
    
    values[0] = values[n-1]; // use old value
    values[n-1] = (rand() / (double) RAND_MAX)*a*sigma;
    
    do {
        int i;
        
        n >>= 1;
        sigma *= f;
        for (i = n; i < size; i += n) {
            if ((i & ((n<<1)-1)) == 0)
                continue; //don't calculate values that have been calculated before
            values[i] = (rand() / (double) RAND_MAX)*a*sigma 
                + 0.5*(values[i-n] + values[i+n]);
        }
        
    } while (n > 1);
    
    noize_data->pos = 0;
}

static double noize_signal(double t, double f, double amp, void* data)
{
    struct NoizeData* noize_data = (struct NoizeData*) data;
    
    if (noize_data->pos >= noize_data->size)
    {
        noize_fill_data(noize_data, f, amp);
        //      s_log(3, "Calculating next values");
    }
    
    return noize_data->values[noize_data->pos++];
}
