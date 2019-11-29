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

#include "audiowavegenmodule.h"

#include <math.h>
#include <assert.h>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_POSIX)
#include <sys/time.h>
#elif defined(OS_WIN32)
#include <sys/timeb.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static logT s_log;

typedef struct _MyInstance {

  double t;
  double phase;
  double f;

  double last_val;
} MyInstance, *MyInstancePtr;

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
#else
#error NO IMPLEMENTATION FOR THIS PLATFORM
#endif

  return time;
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

  my->f = 0;
  my->phase = 0;
  my->t = time_in_secs();
  my->last_val = 0;

  return my;
}

void destruct(MyInstance* my)
{
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  int i;
  double t;
  double* samples;
  int sample_rate = trim_int(inst->in_sample_rate->number, 8000, 44100);
  int num_samples;
  double delta_tt;
  double f;
  double factor;
  double tt = time_in_secs();
  double time_diff;
  double ttt;
  double amplitude = trim_double(inst->in_amplitude->number, 0, 1);

  delta_tt = tt - my->t;

  if (delta_tt <= 0) {
    my->t = tt;
    return;
  }

  if (delta_tt > 0.075) {
    num_samples = 1024;
    my->t = tt - ((double) num_samples) / ((double) sample_rate);
    delta_tt = tt - my->t;
    time_diff = delta_tt;
  }
  else {
    num_samples = (int) (sample_rate * delta_tt + 0.5);
    time_diff = ((double) num_samples) / ((double) sample_rate);
  }

  f = fabs(inst->in_freq->number);
  factor = 2.0 * M_PI * f;

  //  printf("sample_rate = %i\n", sample_rate);
  //  printf("delta_tt = %f ms\nnum_samples = %i\n", delta_tt*1000, num_samples);

  inst->out_r->channels         = 1;
  inst->out_r->sample_rate      = sample_rate;
  audio_resize(inst->out_r, num_samples);
  inst->out_r->len              = num_samples;
  samples                       = inst->out_r->samples;

  ttt = fmod(my->t, 2.0*M_PI);
  // if the frequency has changed, change the phase of the sinus wave
  // to ensure a continuous function
  if (my->f != f)
    {
      double new_phase = fmod(2*M_PI*ttt * (my->f - f) + my->phase, 2*M_PI);
      /*      if (fabs(sin(ttt*my->f + my->phase) - sin(ttt*f + new_phase)) 
          > 0.01)
        {
          printf("t = %f, f_old = %f, f_new = %f, ph_old = %f, ph_new = %f\n",
                 my->t, my->f, f, my->phase, new_phase);       
                 }*/
      my->phase = new_phase;
      my->f = f;
    }

  for (i = 0; i < num_samples; ++i) {
    t = (i / ((double) num_samples)) * time_diff + ttt;
    samples[i] = amplitude * sin(t * factor + my->phase);
  }
  //printf("diff = %f\n", my->last_val - samples[0]);
  my->last_val = samples[num_samples-1];

  my->t += time_diff;
}


