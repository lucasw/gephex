#ifndef INCLUDED_MPEG3_DRIVER
#define INCLUDED_MPEG3_DRIVER

#include <memory>

#include "videofiledriver.h"

struct Mpeg3DriverImpl;

class Mpeg3Driver : public VideoFileDriver
{
public:
  Mpeg3Driver();
  virtual ~Mpeg3Driver();

  static std::list<std::string> supported_extensions();

  void load_file(const std::string& file_name, VideoInfo& info);
  
  void decode_frame(unsigned int frame_number, uint_32* framebuffer);

 private:
  std::auto_ptr<Mpeg3DriverImpl> m_impl;
};
#endif
