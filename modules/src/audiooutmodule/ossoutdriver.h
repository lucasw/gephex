#ifndef INCLUDED_OSS_OUT_DRIVER_H
#define INCLUDED_OSS_OUT_DRIVER_H

#include <memory>

#include "audiooutdriver.h"

class OSSOutDriver : public AudioOutDriver
{
public:
  OSSOutDriver();
  virtual ~OSSOutDriver();

  void open(device_id_t device,
	    int sample_rate,
	    sample_format format,
	    int channels,
            int samples_per_period,
            int num_periods);

  void close();

  /**
   * Returns number of *samples* (not bytes) that have been read.
   * data must be big enough to hold num_samples samples
   */
  int write(const unsigned char* data, int num_samples);

  bool is_open() const;
private:
  struct Impl;
  std::auto_ptr<Impl> m_impl;
};

#endif
