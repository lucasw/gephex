#ifndef INCLUDED_MIDI_IN_DRIVER_H
#define INCLUDED_MIDI_IN_DRIVER_H


class MidiInDriver
{
public:
  typedef int device_id_t;

  //static const device_id_t DEFAULT_DEVICE = 0;
  
  virtual ~MidiInDriver() {}
  virtual void open(device_id_t device) = 0;

  virtual void close() = 0;

  /**
   * Returns number of bytes that have been read.
   * data must be big enough to hold data_size bytes
   */
  virtual int read(unsigned char* data, int data_size) = 0;

  virtual bool is_open() const = 0;
};

#endif
