#ifndef INCLUDED_V4L1_H
#define INCLUDED_V4L1_H

#include <string>

// transitional
#include <videodev.h>

enum v4l1_pixel_format
  {
    RGB32,   // VIDEO_PALETTE_RGB32
    YUV411P  // VIDEO_PALETTE_YUV411P
    // feel free to add the others
  };


struct v4l1_intern;

class v4l1_device
{
 public:
  v4l1_device(const std::string& device_name);
  ~v4l1_device();
  
  // transitional
  void vidiocmcapture (video_mmap&    videoMMap);
  void vidiocsync     (int            backbf);
  void vidiocgmbuf    (video_mbuf&    videoMBuf);

  void vidiocgwin     (video_window&  videoWindow);
  void vidiocswin     (video_window&  videoWindow);

  void vidiocgpict    (video_picture& videopic);
  void vidiocspict    (video_picture& videopic);

  bool select();
  void* mmap(size_t size);
  void  munmap(void* mmapBase,size_t mmapSize);


  size_t min_width();
  size_t max_width();
  size_t min_height();
  size_t max_height();
  
  const video_capability& cap();
 private:
  int fd();
  v4l1_intern* intern;
};

#endif
