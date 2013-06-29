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

#include "audiosynthmodule.h"

#include <cmath>
#include <algorithm>
#include <string>
#include "synth.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_POSIX)
#include <sys/time.h>
#elif defined(OS_WIN32)
#include <sys/timeb.h>
#endif

static logT s_log;

struct _MyInstance 
{
public:
  double t;
  Instrument inst;
  Voice voice;
  bool lastkeystate;
  double lastkey;
  _MyInstance()
    :voice(inst,0,0,0,0)
  {}
};

typedef _MyInstance MyInstance;

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

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


void shutDown(void)
{
}

_MyInstance* construct()
{
  MyInstance* my = new MyInstance();

  // Add your initialization here
  my->inst.frequenz_env_amount=-0.05;
  my->inst.frequenz_env_attack=0.1;
  my->inst.frequenz_env_decay=0.3;
  my->inst.frequenz_env_sustain_level=0.0;
  my->inst.frequenz_env_release=0.0;
  my->inst.frequenz_lfo_amount=0.01;
  my->inst.frequenz_lfo_frequ=3.0;
  my->inst.amplitude_lfo_amount=+0.15;
  my->inst.amplitude_lfo_frequ=3;
  my->inst.amplitude_env_amount=.7;
  my->inst.amplitude_env_attack=0.1;
  my->inst.amplitude_env_decay=0.2;
  my->inst.amplitude_env_sustain_level=0.3;
  my->inst.amplitude_env_release=1;
  my->inst.waveform=0;
  my->lastkeystate=false;
  my->t= time_in_secs();
  return reinterpret_cast<_MyInstance*>(my);
}

void destruct(_MyInstance* my)
{
  // Add your cleanup here
  delete reinterpret_cast<_MyInstance*>(my);
}



void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstance* my = reinterpret_cast<MyInstance*>(inst->my);

  int sample_rate = trim_int(inst->in_sample_rate->number, 8000, 44100);
  
  double tt = time_in_secs();
  double delta_tt = tt - my->t;

 if (delta_tt <= 0) 
   {
     my->t = tt;
     return;
   }

 int num_samples;
 double time_diff;

 if (delta_tt > 0.075) 
   {
     num_samples = 1024;
     my->t = tt - ((double) num_samples) / ((double) sample_rate);
     delta_tt = tt - my->t;
     time_diff = delta_tt;
   }
 else 
   {
     num_samples = (int) (sample_rate * delta_tt + 0.5);
     time_diff = ((double) num_samples) / ((double) sample_rate);
   }


  inst->out_r->channels         = 1;
  inst->out_r->sample_rate      = sample_rate;
  audio_resize(inst->out_r, num_samples);
  inst->out_r->len              = num_samples;
  
  double* samples               = inst->out_r->samples;

  // update inst
  std::string waveform(inst->in_signal->text);
  if (waveform=="sinus")
    my->inst.waveform=0;
  else if (waveform=="saegezahn")
    my->inst.waveform=1;
  else if (waveform=="rechteck")
    my->inst.waveform=2;
  else if (waveform=="noize")
    my->inst.waveform=3;
  else if (waveform=="brownnoize")
    my->inst.waveform=4;

  my->inst.frequenz_env_amount=(inst->in_f_env->amount )*12;
  my->inst.frequenz_env_attack=pow(inst->in_f_env->attack, 3);
  my->inst.frequenz_env_decay=inst->in_f_env->decay;
  my->inst.frequenz_env_sustain_level=inst->in_f_env->sustain_level;
  my->inst.frequenz_env_release=inst->in_f_env->release;;
  my->inst.frequenz_lfo_amount=inst->in_f_lfo->amount;
  my->inst.frequenz_lfo_frequ=inst->in_f_lfo->frequenz;
  my->inst.amplitude_lfo_amount=inst->in_a_lfo->amount;
  my->inst.amplitude_lfo_frequ=inst->in_a_lfo->frequenz;
  my->inst.amplitude_env_amount=inst->in_a_env->amount;
  my->inst.amplitude_env_attack=pow(inst->in_a_env->attack,3);
  my->inst.amplitude_env_decay=inst->in_a_env->decay;
  my->inst.amplitude_env_sustain_level=inst->in_a_env->sustain_level;
  my->inst.amplitude_env_release=inst->in_a_env->release;

    // fehler
  
  // update frequency
  const double key = trim_double(inst->in_key->number, 0, 127);
  my->voice.m_frequ=key-24;

  const double amp = trim_double(inst->in_amplitude->number, 0, 1);
  my->voice.m_amp=amp;

  bool pressed = trim_bool(inst->in_key_press->number) != 0;
  
  /* begin Aenderung von georg
  if (my->lastkey != key) {
	  pressed = true;
  }
  else
	  pressed = false;

  my->lastkey = key;
  

  */ //TODO: sorry martin, nur zum ausprobieren
  if (my->lastkeystate!=pressed)

  // end Aenderung von georg
    {
      if (pressed)
	{
	  my->voice.m_starttime=my->voice.m_time;
	  my->voice.m_length=100000000; // quite long note
	}
      else
	{
	  my->voice.m_length=my->voice.m_time;
	}
    }
  my->lastkeystate=pressed;
  

  for (int i=0;i!=num_samples;++i)
    {
      samples[i]=my->voice();
    }

  my->t += time_diff;

}

