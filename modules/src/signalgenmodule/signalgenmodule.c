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

#include "signalgenmodule.h"

#include <math.h>
#include "crandgen.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_POSIX)
#include <sys/time.h>
#elif defined(OS_WIN32)
#define snprintf _snprintf
#include <sys/timeb.h>
#endif

#include <assert.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define EPSILON 0.00000001

static logT s_log;

typedef double (*signal_t)(double t, double f, double amp, void*);
typedef double (*inv_signal_t)(double t, double f, double amp,
                          double delta_val, void*);

static double sinus_signal(double t, double f, double amp, void*);
static double inverse_sinus(double val, double f, double amp, 
                            double delta_val, void*);

static double ramp_signal(double t, double f, double amp, void*);
static double inverse_ramp(double val, double f, double amp,
                            double delta_val, void*);

static double triangle_signal(double t, double f, double amp, void*);
static double inverse_triangle(double val, double f, double amp,
                            double delta_val, void*);

static double rectangle_signal(double t, double f, double amp, void*);

static double inverse_rectangle(double val, double f, double amp,
                               double delta_val, void*);

static double noize_signal(double t, double f, double amp, void*);
static double inverse_noize(double val, double f, double amp,
                            double delta_val, void*);

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

  signal_t     signal;
  inv_signal_t inverse_signal;

  int    mode;
  double relative_time;

  double old_value;
  double delta_value;
  double freq;
  double amp;
  double extra_phase;

  double old_time;

  struct NoizeData noize_data;
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
  
  my->signal            = 0;
  my->inverse_signal    = 0;
	
  my->noize_data.values = 0;
  my->noize_data.size   = 0;
  my->noize_data.pos    = 0;

  my->mode              = REAL_MODE;
  my->relative_time     = 0;

  my->extra_phase       = 0;
  my->freq              = 1;
  my->amp               = 1;
  my->old_value         = 0;
  my->delta_value       = 0;

  my->old_time          = get_time(my);

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
    
  double amp   = inst->in_Amplitude->number;
  double freq  = inst->in_Frequenz->number;
  double shift = trim_double(inst->in_Phase->number, 0, 1);
    
  double trans = inst->in_Position->number;
  double result;

  int routine_changed = 0;
  int mode_changed    = 0;
    
  if (strcmp(my->routine_text.text, inst->in_signal->text) != 0)
    {
      string_assign(&my->routine_text, inst->in_signal);
      routine_changed = 1;
        
      if (strcmp(my->routine_text.text, "sinus") == 0)
        {
          my->signal         = sinus_signal;
          my->inverse_signal = inverse_sinus;
        }
      else if (strcmp(my->routine_text.text, "ramp") == 0)
        {     
          my->signal         = ramp_signal;
          my->inverse_signal = inverse_ramp;
        }
      else if (strcmp(my->routine_text.text, "triangle") == 0)
        {     
          my->signal         = triangle_signal;
          my->inverse_signal = inverse_triangle;
        }
      else if (strcmp(my->routine_text.text, "rectangle") == 0)
        {     
          my->signal         = rectangle_signal;
          my->inverse_signal = inverse_rectangle;
        }
      else if (strcmp(my->routine_text.text, "noize") == 0)
        {     
          my->signal         = noize_signal;
          my->inverse_signal = inverse_noize;
            
          if (my->noize_data.values == 0)
            {
              int n = 33;
              my->noize_data.values = (double*) malloc(sizeof(double) * n);
              my->noize_data.size = n;
              my->noize_data.pos = n;
              // initialize it value
              my->noize_data.values[n-1] = 0;
            }
        }
      else
        {
          char buffer[128];
          snprintf(buffer, sizeof(buffer),
                   "Unsupported signal routine: '%s', using 'sinus' instead",
                   my->routine_text.text);
            
          s_log(0, buffer);
          my->signal         = sinus_signal;
          my->inverse_signal = inverse_sinus;
        }
    }

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
    
  {
    double T;
    double time = get_time(my);
    double deltat = time - my->old_time;
    my->old_time = time;

    if (fabs(freq) < EPSILON || fabs(amp) < EPSILON)
      {
	if (fabs(amp) < EPSILON)
          {
            my->old_value   = 0;
            my->delta_value = 0;
          }

        inst->out_Signal->number = my->old_value + trans;
	my->freq        = freq;
	my->amp         = amp;
        return;
      }
        
    T = 1.0 / freq;
        
    // try to make it continuous
    if (fabs(freq - my->freq)*T > EPSILON ||
	fabs(amp - my->amp) / my->amp > EPSILON ||
	routine_changed || mode_changed)
      {
	double old_value = my->old_value;
        double t;

	if (old_value > amp)
	  old_value = amp;

        t = my->inverse_signal(old_value,
                               freq, amp,
                               my->delta_value,
                               &my->noize_data);

        if (!mode_changed)
          t += deltat;

        t -= time + shift*T;

        my->extra_phase = fmod(t * freq, 1);

        if (my->extra_phase < 0)
          my->extra_phase += 1;

        assert(0 <= my->extra_phase && my->extra_phase <= 1);

        my->freq = freq;
	my->amp  = amp;
      }

    time += (shift + my->extra_phase)*T;

    result = my->signal(time, freq, amp, &my->noize_data);
   
    if (result > amp)
      result = amp;
    else if (result < 0)
      result = 0;

    my->delta_value = result - my->old_value;
    my->old_value   = result;
        
    inst->out_Signal->number = (result + trans);
  }
}

/*****************************************************************************/

static double sinus_signal(double t, double f, double amp, void* d)
{
  return (amp*0.5*(1.0+sin(2*M_PI*f*t)));
}

static double inverse_sinus(double val, double f, double amp, 
                            double delta_val, void* d)
{
  double inv;
  double arg = 2.0*val/amp - 1;

  if (arg < -1)
    arg = -1;
  else if (arg > 1)
    arg = 1;

  assert(-1 <= arg && arg <= 1);

  if (arg >= 0)
    {
      if (delta_val >= 0)
        {
          inv = asin(arg);

          assert(0 <= inv && inv <= M_PI/2.0);
        }
      else
        {
          inv = (M_PI/2.0 - asin(arg)) + M_PI/2.0;
          
          assert(M_PI/2.0 <= inv && inv <= M_PI);
        }
    }
  else if (arg < 0)
    {
      if (delta_val < 0)
        {
          inv = (-M_PI/2.0 - asin(arg)) + 3.*M_PI/2.;

          assert(M_PI <= inv && inv <= 3.*M_PI/2.0);
        }
      else
        {
          inv = asin(arg) + 2.*M_PI;

          assert(3.*M_PI/2 <= inv && inv <= 2.*M_PI);
        }
    }

  return inv / (2*M_PI * f);
}

static double triangle_signal(double t, double f, double amp, void* d)
{
  double T = 1.0 / f;
  double time = fmod(t, T);
  double aa = 2.0 * amp;
    
  if (time < 0.5*T)
    return (aa * f * time);
  else
    return aa * (1 - f*time);
}

static double inverse_triangle(double val, double f, double amp,
                               double delta_val, void* d)
{
  double T = 1.0 / f;
  double tmp = val / (2.0*amp);

  if (delta_val >= 0)
      return T * tmp;
  else
      return T * (1 - tmp);
}

static double ramp_signal(double t, double f, double amp, void* d)
{
  double time = fmod(t, 1.0 / f);
  return (amp * f * time);
}

static double inverse_ramp(double val, double f, double amp,
                            double delta_val, void* d)
{
  return val / (amp*f);
}

static double rectangle_signal(double t, double f, double amp, void* d)
{
  double T = 1.0 / f;
  double time = fmod(t, T);
    
  if (time < 0.5*T)
    return amp;
  else
    return 0;
}

static double inverse_rectangle(double val, double f, double amp,
                               double delta_val, void* d)
{
  if (delta_val >= 0)
    return 0;
  else
    return 1.0 / (2*f);
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
  values[n-1] = (rnd_mt19937() / (double) 0xFFFFFFFF)*a*sigma;
    
  do {
    int i;
        
    n >>= 1;
    sigma *= f;
    for (i = n; i < size; i += n) {
      if ((i & ((n<<1)-1)) == 0)
        continue; //don't calculate values that have been calculated before
      values[i] = (rnd_mt19937() / (double) 0xFFFFFFF)*a*sigma 
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
      noize_fill_data(noize_data, f, amp/2.0);
      //      s_log(3, "Calculating next values");
    }
    
  return noize_data->values[noize_data->pos++];
}

static double inverse_noize(double val, double f, double amp,
                            double delta_val, void* data)
{
  return 0; //TODO
}
