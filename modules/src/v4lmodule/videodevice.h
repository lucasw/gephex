#ifndef INCLUDED_VIDEODEVICE_H
#define INCLUDED_VIDEODEVICE_H

#include <string>
#include <stdexcept>

#include "basic_types.h"
#include "linux/videodev.h"

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
    PixelType type;
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
  void grabImage(Frame& frame) throw (std::runtime_error);
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
  void* mmapBase;
  size_t mmapSize;
  uint_32* frameptr[2];
  int frontbf;
  int backbf;


  logT log2;
};

#endif



