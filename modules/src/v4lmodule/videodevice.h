#ifndef INCLUDED_VIDEODEVICE_H
#define INCLUDED_VIDEODEVICE_H

#include <string>
#include <stdexcept>

extern "C" {
#include "videodev.h"
}

#include "basic_types.h"


class VideoDevice
{
public:
  typedef void (*logT) (int, const char*);
  
  enum PixelType
    {
      RGBA32,
      YUV411P
    };

  struct Frame
  {
    int xSize;
    int ySize;
    unsigned int type;
    uint_32* frameptr;
  };
  

  /** opens a V4L videodevice
   * \param deviceFileName absolute path of the devicefile e.g. "/dev/video1"
   */
  VideoDevice(const std::string& deviceFileName, logT log2) throw (std::runtime_error);


  /** closes a V4L videodevice
   */
  ~VideoDevice();


  /** grabs one frame 
   * \param frame image params 
   */
  void grabImage(Frame& frame,bool drop) throw (std::runtime_error);

  void setProperties(int brightness,int hue,int colour,
		     int contrast,
		     int whiteness);
private:
  /**
   * filedescriptor
   */
  int fd;  

  /**
   * struct will be filled with capture info
   */
  video_capability cap; 
  
  bool initialized;
  Frame initFrame;
  
  // converter parameters
  int m_brightness;
  int m_hue;
  int m_colour;
  int m_contrast;
  int m_whiteness;

  // mmap mode
  void* mmapBase;
  size_t mmapSize;
  uint_32* frameptr[2];
  int frontbf;
  int backbf;

  logT log2;
};

#endif



