#ifndef INCLUDED_SDLIMAGE_DRIVER
#define INCLUDED_SDLIMAGE_DRIVER

#include <memory>

#include "videofiledriver.h"

class SDLImageDriverImpl;

class SDLImageDriver : public VideoFileDriver
{
public:
  SDLImageDriver();
  virtual ~SDLImageDriver();

  static std::list<std::string> supported_extensions();

  void load_file(const std::string& file_name, VideoInfo& info);
  
  void decode_frame(unsigned int frame_number, uint_32* framebuffer);

 private:
  std::auto_ptr<SDLImageDriverImpl> m_impl;
};
#endif
