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

#include <string>
#include <map>
#include <cmath>

#include "signals.h"

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

#define EPSILON 0.00000001

static logT s_log;

static const int    REAL_MODE     = 0;
static const int    RELATIVE_MODE = 1;
static const double TIME_STEP     = 1 / 25.;

//-----------------------------------------------------------------------------

/**
 * Must be called exactly once per update
 * (because it increases the relative time).
 */
static double get_time(int mode, double& relative_time);

//-----------------------------------------------------------------------------

class SignalRegistry
{
public:
  ~SignalRegistry()
  {
    for (FactoryMap::const_iterator it = m_factories.begin();
         it != m_factories.end(); ++it)
      {
        delete it->second;
      }
  }

  void register_signal(SignalFactory* f)
  {
    m_factories.insert(std::make_pair(f->name(), f));
  }

  Signal* create(const std::string& name) const
  {
    FactoryMap::const_iterator it = m_factories.find(name);

    if (it == m_factories.end())
      return 0;
    else
      return it->second->create();
  }

private:
  typedef std::map<std::string, SignalFactory*> FactoryMap;
  FactoryMap m_factories;
};

static SignalRegistry s_registry;

//-----------------------------------------------------------------------------

typedef struct _MyInstance
{
  StringType routine_text;
  StringType mode_text;

  Signal*    signal;

  int    mode;
  double relative_time;

  double old_value;
  double delta_value;
  double freq;
  double amp;
  double trans;
  double extra_phase;

  double old_time;

} MyInstance, *MyInstancePtr;

//-----------------------------------------------------------------------------

int init(logT log_function)
{
  s_log = log_function;

  s_registry.register_signal(new SinusFactory());
  s_registry.register_signal(new TriangleFactory());
  s_registry.register_signal(new RampFactory());
  s_registry.register_signal(new RectangleFactory());
  s_registry.register_signal(new NoiseFactory());
  
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
  
  my->signal            = 0;

  my->mode              = REAL_MODE;
  my->relative_time     = 0;

  my->extra_phase       = 0;
  my->freq              = 1;
  my->amp               = 1;
  my->trans             = 0;
  my->old_value         = 0;
  my->delta_value       = 0;

  my->old_time          = get_time(my->mode, my->relative_time);

  string_initInstance(&my->routine_text);
  string_initInstance(&my->mode_text);

  return my;
}

void destruct(MyInstance* my)
{ 
  string_destroyInstance(&my->routine_text);
  string_destroyInstance(&my->mode_text);

  delete my->signal;

  free(my);
}

static int sgn(double v)
{
  return (v >= 0) ? 1 : -1;
}

//-----------------------------------------------------------------------------

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
    
  double amp   = fabs(inst->in_Amplitude->number);
  double sign  = sgn(inst->in_Amplitude->number);
  double freq  = inst->in_Frequenz->number;
  double shift = trim_double(inst->in_Phase->number, 0, 1);
    
  double trans = inst->in_Position->number;
  double result;

  bool routine_changed = false;
  bool mode_changed    = false;
    
  if (strcmp(my->routine_text.text, inst->in_signal->text) != 0)
    {
      string_assign(&my->routine_text, inst->in_signal);
      routine_changed = true;
      delete my->signal;
    
      my->signal = s_registry.create(inst->in_signal->text);

      if (my->signal == 0)
        {
          char buffer[128];
          snprintf(buffer, sizeof(buffer),
                   "Unsupported signal routine: '%s', using 'sinus' instead",
                   my->routine_text.text);
            
          s_log(0, buffer);
          my->signal = s_registry.create("sinus");
        }

      assert(my->signal);
    }

  if (strcmp(my->mode_text.text, inst->in_mode->text) != 0)
    {
      string_assign(&my->mode_text, inst->in_mode);

      mode_changed = true;
        
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
    double time = get_time(my->mode, my->relative_time);
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
    if (fabs(freq - my->freq)*T > EPSILON       ||
	fabs(amp - my->amp) / my->amp > EPSILON ||
        fabs(trans - my->trans) > EPSILON       ||
	routine_changed || mode_changed)
      {
	double old_value = my->old_value + my->trans;
        double t;

	if (old_value-trans > amp)
          old_value = amp+trans;
        if (old_value-trans < 0)
          old_value = trans;

        t = my->signal->inv(old_value - trans, freq, amp, my->delta_value);

        if (!mode_changed)
          t += deltat;

        t -= time + shift*T;

        my->extra_phase = fmod(t * freq, 1);

        if (my->extra_phase < 0)
          my->extra_phase += 1;

        assert(0 <= my->extra_phase && my->extra_phase <= 1);

        my->freq  = freq;
        my->amp   = amp;
        my->trans = trans;
      }

    time += (shift + my->extra_phase)*T;

    result = (*my->signal)(time, freq, amp);
   
    if (result > amp)
      result = amp;
    else if (result < 0)
      result = 0;

    my->delta_value = result - my->old_value;
    my->old_value   = result;
        
    inst->out_Signal->number = sign * (result + trans);
  }
}

//-----------------------------------------------------------------------------


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

static double get_time(int mode, double& relative_time)
{
  switch (mode)
    {
    case REAL_MODE:
      return time_in_secs();
    case RELATIVE_MODE:
      {
        double t = relative_time;
        relative_time += TIME_STEP;
        return t;
      }
    default:		
      s_log(0, "Invalid internal mode!!!");
      return 0;
    }
}

//-----------------------------------------------------------------------------
