#ifndef INCLUDED_OSS_MIDI_IN_DRIVER_H
#define INCLUDED_OSS_MIDI_IN_DRIVER_H

#include <memory>

#include "midiindriver.h"

class OSSMidiInDriver : public MidiInDriver
{
public:
  OSSMidiInDriver();
  virtual ~OSSMidiInDriver();
  virtual void open(device_id_t device);

  virtual void close();

  virtual int read(unsigned char* data, int data_size);

  virtual bool is_open() const;

private:
	struct Impl;
	std::auto_ptr<Impl> m_impl;
};

#endif
