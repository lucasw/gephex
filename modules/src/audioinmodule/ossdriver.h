#ifndef INCLUDED_OSS_DRIVER_H
#define INCLUDED_OSS_DRIVER_H

#include <memory>

#include "audioindriver.h"

class OSSDriver : public AudioInDriver
{
public:
  OSSDriver();
  virtual ~OSSDriver();

  void open(device_id_t device,
	    int sample_rate,
	    sample_format format,
	    int channels);

  virtual void close();

  /**
   * Returns number of *samples* (not bytes) that have been read.
   * data must be big enough to hold num_samples samples
   */
  int read(unsigned char* data, int num_samples);

  bool is_open() const;
private:
  struct Impl;
  std::auto_ptr<Impl> m_impl;
};

#endif
