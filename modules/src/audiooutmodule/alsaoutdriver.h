#ifndef INCLUDED_ALSA_OUT_DRIVER_H
#define INCLUDED_ALSA_OUT_DRIVER_H

#include "audiooutdriver.h"

#include <memory>

class AlsaOutDriver : public AudioOutDriver
{
public:
  AlsaOutDriver();
  virtual ~AlsaOutDriver();

  void open(device_id_t device,
	    int sample_rate,
	    sample_format format,
	    int channels,
	    int samples_per_period,
	    int num_periods);


  void close();

  int write(const unsigned char* data,
	    int num_samples);

  bool is_open() const;

 private:
  struct Impl;
  std::auto_ptr<Impl> m_impl;
};

#endif
