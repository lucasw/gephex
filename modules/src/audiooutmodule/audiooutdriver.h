#ifndef INCLUDED_AUDIO_OUT_DRIVER_H
#define INCLUDED_AUDIO_OUT_DRIVER_H

class AudioOutDriver
{
 public:
  typedef int device_id_t;

  enum sample_format { SF_16LE };

  virtual ~AudioOutDriver() {};
  /**
   *
   * Output is buffered. The size of the buffer is
   * num_periods*samples_per_period samples. This buffer determines the
   * latency of audio output.
   */
  virtual void open(device_id_t device,
                    int sample_rate,
                    sample_format format,
                    int channels,
                    int samples_per_period,
                    int num_periods) = 0;


  virtual void close() = 0;

  /**
   * Returns the number of samples written (not bytes!).
   * Return value always >= 0.
   */ 
  virtual int write(const unsigned char* data,
		    int num_samples) = 0;

  virtual bool is_open() const = 0;
};

#endif
