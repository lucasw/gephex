#ifndef INCLUDED_AVI_FILE_DRIVER
#define INCLUDED_AVI_FILE_DRIVER

#include <memory>

#include "videofiledriver.h"

struct AviFileDriverImpl;

class AviFileDriver : public VideoFileDriver
{
 public:
  AviFileDriver();
  virtual ~AviFileDriver();
  
  static std::list<std::string> supported_extensions();
  
  void load_file(const std::string& file_name, VideoInfo& info);

  void close_file();
  
  bool is_open() const;  

  void decode_frame(unsigned int frame_number, uint_32* framebuffer,
	                int width, int height);
  
 private:
  std::auto_ptr<AviFileDriverImpl> m_impl;
};
#endif
