#ifndef INCLUDED_AUDIO_IN_DRIVER_H
#define INCLUDED_AUDIO_IN_DRIVER_H


class AudioInDriver
{
public:
  typedef int device_id_t;

  //static const device_id_t DEFAULT_DEVICE = 0;

  enum sample_format { SF_16LE };
  virtual ~AudioInDriver() {}
  virtual void open(device_id_t device,
		    int sample_rate,
		    sample_format format,
		    int channels) = 0;


  virtual void close() = 0;

  /**
   * Returns number of *samples* (not bytes) that have been read.
   * data must be big enough to hold num_samples samples
   */
  virtual int read(unsigned char* data, int num_samples) = 0;

  virtual bool is_open() const = 0;
};

#endif
