#ifndef INCLUDED_SYNTH_H
#define INCLUDED_SYNTH_H

struct Instrument
{
  double frequenz_env_amount;
  double frequenz_env_attack;
  double frequenz_env_decay;
  double frequenz_env_sustain_level;
  double frequenz_env_sustain;
  double frequenz_env_release;
  double frequenz_lfo_amount;
  double frequenz_lfo_frequ;
  double amplitude_lfo_amount;
  double amplitude_lfo_frequ;
  double amplitude_env_amount;
  double amplitude_env_attack;
  double amplitude_env_decay;
  double amplitude_env_sustain_level;
  double amplitude_env_sustain;
  double amplitude_env_release;
  int waveform;
};

class Voice
{
public: 
  const Instrument& m_inst;
  double m_frequ;
  double m_starttime;
  double m_length;
  double m_amp;
  const double m_time_steps;
  
  double m_phase;
  double m_time;

  double last;
public:
  /**
   * construct new voice
   */
  Voice(const Instrument& inst, 
	double frequ, double starttime, double length, double amp, 
	double time_steps=1.0/44100.0);
  
  /**
   * calculate next sample
   */
  double operator()();
};


#endif
