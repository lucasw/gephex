#include "synth.h"

#include <cmath>
#include <cstdlib>
#include <algorithm>

/* >> T O D O <<
 *
 * noten -> frequenzwandler
 * sequenzer (midi als format)
 * pulsweiteneinstellung
 * filter
 * Trennung io - generator
 */

#ifndef M_PI
#define M_PI 3.1415
#endif

double lfo(double time, double frequ)
{
  return sin(frequ * time * 2.0* M_PI);
}

double env(double time,double attack,double decay,double sustain_level,double sustain,double release)
{
  if (time < 0.0)
    return 0.0;
  else if (time < attack)
    return (time/attack);
  else if (time < (attack+decay))
    return sustain_level * (time-attack)/decay + (1.0-((time-attack)/decay));
  else if (time < sustain)
    return sustain_level;
  else if (time < (sustain+release))
    return sustain_level * (1.0-(time-sustain)/release);
  else 
    return 0.0;
}

Voice::Voice(const Instrument& inst, 
	     double frequ, double starttime, double length, double amp, 
	     double time_steps)
  :m_inst(inst),m_frequ(frequ),m_starttime(starttime),m_length(length),m_amp(amp),
   m_time_steps(time_steps),m_time(-m_starttime-(1.0/48000.0)),m_phase(0.0),last(0.0)
{
}

double Voice::operator()()
{
  double lasttime = m_time;
  m_time += m_time_steps;
  
  double amplitude=  m_amp * (m_inst.amplitude_env_amount * env(m_time-m_starttime,m_inst.amplitude_env_attack,m_inst.amplitude_env_decay,m_inst.amplitude_env_sustain_level,m_length,m_inst.amplitude_env_release) 
			      * (1.0+ m_inst.amplitude_lfo_amount * lfo(m_time-m_starttime,m_inst.amplitude_lfo_frequ)));
  
  double frequenz= m_frequ 
    + m_inst.frequenz_env_amount * env(m_time-m_starttime,m_inst.frequenz_env_attack,m_inst.frequenz_env_decay,m_inst.frequenz_env_sustain_level,m_length,m_inst.frequenz_env_release) 
    + m_inst.frequenz_lfo_amount * lfo(m_time-m_starttime,m_inst.frequenz_lfo_frequ);

  // frequenz is the key number !!!!!!
  // 0 is C
  // 1 is C#31
  // 2 is D ....

  static const double base_frequ=440.0; // kammerton A
  //1.0595 is the 12th root of 2 wohltemperierte stimmung
  m_phase += base_frequ * pow(1.0595,frequenz) * (m_time-lasttime);
  
  // select waveform
  double signal;
    
  switch( m_inst.waveform )
    {
    case 0: // sinsinsin
      signal = sin( 2.0 * M_PI * m_phase );
      break;
    case 1: // /|/|/|/|
      signal = 2.0 * ( fmod( m_phase, 1.0 ) - 1.0 );
      break; 
    case 2: // _-_-_-_-
      if ( fmod( m_phase, 1.0 ) < 0.5 )
	signal = -1.0;
      else
	signal = 1.0;
      break;
    case 3:
      signal= 2.0*((rand()/(double)RAND_MAX)-1.0);
      break;
    case 4:
		double step = base_frequ * pow(1.0595,frequenz) * (m_time-lasttime);
		double off = (rand()/(double)RAND_MAX)*2*step - step;
		last= last+off;
		if (last < -1)
			last = -1;
		else if (last > 1)
			last = 1;
      signal= last;
    }

  return amplitude*signal;
}






