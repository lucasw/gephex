#ifndef V4LGRABBER_H
#define V4LGRABBER_H

#include <vector>
#include <string>

#include <linux/videodev.h> // video4linux interface

typedef int* Frame;
    
class V4LGrabber
{
 public:
  V4LGrabber(const std::string& deviceName);
  void setColorProperties(unsigned char brightness,unsigned char contrast,
                         unsigned char hue,unsigned char saturation);
  void setGrabProperties(int width, int height);
  void setVideoInput(int,int);
  
  void grabNextImage();
  void getGrabbedImage(Frame&);
  ~V4LGrabber();
      
 private:
      int m_videoDevice; // filedescriptor for the opened v4l device
      int m_channelmax; // maximum input channel number
      void* m_mmapBase; // start of mmap area
      int m_mmapSize; // size of mmap area
      int m_lastGrabbedFrame; // number of last grabbed frame
      int m_NrInputChannels;
      int m_width;
      int m_height;

      // framebuffer stuff
      std::vector<unsigned int*> m_frameptr; // pointer to the frames
  };


#endif


