#include "videodevice.h"

#include <sstream>
#include <algorithm>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <cassert>

// debug
//#include "videodefostr.h"
#include <iostream>

VideoDevice::VideoDevice(const std::string& deviceFileName, logT log2_)   
  throw (std::runtime_error)
  :initialized(false),
   frontbf(1),
   log2(log2_),  
   m_brightness(-1),
   m_hue(-1),
   m_colour(-1),
   m_contrast(-1),
   m_whiteness(-1)
{
 
  // try to open the video device file
  fd=open(deviceFileName.c_str(),O_RDONLY);
  
  // check for an error
  if(fd==-1)
    { 
      // an error occured. exit
      std::ostringstream errorMsg;
      errorMsg << "VideoDevice::VideoDevice(\"" << deviceFileName <<"\"): ";
      errorMsg << "open: "<< strerror(errno) << "(" << errno << ")";
      throw std::runtime_error(errorMsg.str());
    }
  
  // lets check if it is a v4l device
  int error =ioctl(fd, VIDIOCGCAP, &cap);
  if(error==-1)
    {
      // seems to be not V4L Device
      // close file and exit with an exception
      close(fd);
      std::ostringstream errorMsg;
      errorMsg << "VideoDevice::VideoDevice(\"" << deviceFileName <<"\"): ";
      errorMsg << "VIDIOCGCAP(" << fd << "): " ;
      errorMsg << strerror(errno) << "(" << errno << ")";
      throw std::runtime_error(errorMsg.str());
    }

  // check if device can capture
  if (!(cap.type&VID_TYPE_CAPTURE))
    {
      // this v4l device cant capture
      // close file and exit with an exception
      close(fd);      
      std::ostringstream errorMsg;
      errorMsg << "VideoDevice::VideoDevice(\"" << deviceFileName <<"\"): ";
      errorMsg << "VIDIOCGCAP(" << fd << "): " ;
      errorMsg << "device can not capture";
      throw std::runtime_error(errorMsg.str());
    }

  // the device is open and ready to capture
}

VideoDevice::~VideoDevice()
{
  // todo:
  // 1. sync to last frames
  // 2. int munmap(void *start, size_t length);

  // close the video device
  close(fd);
}

void VideoDevice::grabImage(Frame& frame, bool drop) throw (std::runtime_error)
{
  // the default size is minimum size
  if (frame.xSize==0)
    frame.xSize=cap.maxwidth;
  if (frame.ySize==0)
    frame.ySize=cap.maxheight;

  frame.xSize-=frame.xSize%2;
  frame.ySize-=frame.ySize%2;
  
  // check if initialized and grab geometry has changed
  if (initialized &&
      !(frame.xSize==initFrame.xSize&&frame.ySize==initFrame.ySize))
    {
      log2(2,"geometry has changed");
      int errorCode = ioctl(fd, VIDIOCSYNC, &frontbf);  
      if(errorCode==-1)
	{
	  std::ostringstream errorMsg;
	  errorMsg << "error while cyncing with last buffer: ";
	  errorMsg << backbf << " !!!";
	  errorMsg << " errno= " << errno;
	  errorMsg << " errorstring= " << strerror(errno);
	  log2(2,errorMsg.str().c_str());
	}

      errorCode= munmap(mmapBase,mmapSize);
      if (errorCode==-1)
	{
	  std::ostringstream errorMsg;
	  errorMsg << "error while munmap ";
	  errorMsg << " errno= " << errno;
	  errorMsg << " errorstring= " << strerror(errno);
	  log2(2,errorMsg.str().c_str());
	}
      initialized=false;
    }
  
  // assert(!initialized || (initialized&&(frame.xSize==initFrame.xSize&&frame.ySize==initFrame.ySize)));

  if (!initialized)
    {

      //check geometry;
      if (!((cap.minwidth<=frame.xSize)&&(frame.xSize<=cap.maxwidth)
	    &&(cap.minheight<=frame.ySize)&&(frame.ySize<=cap.maxheight)))
	{
	  std::ostringstream errorMsg;
	  errorMsg << "device could not capture with ";
	  errorMsg << "width=" << frame.xSize << " and heigth=" << frame.ySize;
	  throw std::runtime_error(errorMsg.str());
	}

      // check capture dimensions
      // try to set the capture geometry(area)
      video_window videoWindow;
      // upper left corner position
      videoWindow.x = 0;
      videoWindow.y = 0;
      // capture area size
      videoWindow.width = frame.xSize;
      videoWindow.height = frame.ySize;
      // options
      videoWindow.flags = 0;
      videoWindow.clipcount = 0;
      videoWindow.clips = NULL;

      // set grab dimensions
      int errorCode=ioctl(fd, VIDIOCSWIN, &videoWindow);
      if (errorCode==-1)
	{
	  std::string errorMsg;
	  errorMsg="Could not set desired grab geometry";
	  throw std::runtime_error(errorMsg);
	}

      // get grabdimensions back
      errorCode=ioctl(fd, VIDIOCGWIN, &videoWindow);
      if(errorCode==-1)
	{
	  std::string errorMsg;
	  errorMsg="Could not read grab geometry";
	  throw std::runtime_error(errorMsg);
	}

      //std::cerr << videoWindow << std::endl;
      
      // and check them
      if (((int)videoWindow.width!=frame.xSize)||
	  ((int)videoWindow.height!=frame.ySize))
	{
	  std::ostringstream errorMsg;
	  errorMsg << "unsupported geometry" << std::endl;
	  errorMsg << "requested: " << frame.xSize << " " << frame.ySize;
	  throw std::runtime_error(errorMsg.str());
	}

      // init memory mapping
      // get mmap info
      video_mbuf videoMBuf;
      errorCode=ioctl(fd, VIDIOCGMBUF, &videoMBuf);
      if(errorCode==-1)
	{
	  std::string errorMsg;
	  errorMsg="Couldn't read mbuf info";
	  throw std::runtime_error(errorMsg);
	}

      // check if backbuffering is possible(2 frames)
      if (videoMBuf.frames<2)
	{
	  std::string errorMsg;
	  errorMsg="mmap cant grab 2 frames";
	  throw std::runtime_error(errorMsg);
	}

      //std::cerr << videoMBuf << std::endl;

      // start mmapping the framegrabber memory
      mmapSize=videoMBuf.size;
      mmapBase = mmap(NULL,mmapSize,PROT_READ,MAP_SHARED,fd,0);
      //std::cout << "mmapBase= " << mmapBase << std::endl;
      if(mmapBase == MAP_FAILED)
	{
	  throw std::runtime_error("Couldn't mmap memory");
	}

      // initialize array with startpointer to the mapped frames
      for(int i=0; i!=2; ++i)
	{
	  frameptr[i]=reinterpret_cast<uint_32*>(reinterpret_cast<char*>(mmapBase)+videoMBuf.offsets[i]);
	}
      
      frontbf=0;
      backbf=1;

      video_mmap videoMMap; // v4l struct for mmap informations
      videoMMap.frame = frontbf; // buffer position
      videoMMap.width = frame.xSize;
      videoMMap.height = frame.ySize;

      // probe pixelformats
      
      // try RGBA
      videoMMap.format =  VIDEO_PALETTE_RGB32;
      errorCode= ioctl(fd, VIDIOCMCAPTURE, &videoMMap);
      if (errorCode==-1)
	{
	  // try YUV
	  videoMMap.format =  VIDEO_PALETTE_YUV420P;
	  errorCode= ioctl(fd, VIDIOCMCAPTURE, &videoMMap);
	}
      
      if(errorCode==-1)
	{
	  throw std::runtime_error("error while starting capture to buffer");
	}

      // remember working geometry and format
      frame.type=videoMMap.format;
      initFrame=frame;

      initialized=true;
    }

  assert(initialized);

  video_mmap videoMMap; // v4l struct for mmap informations
  videoMMap.frame = backbf; // buffer position
  videoMMap.width = initFrame.xSize;
  videoMMap.height = initFrame.ySize;
  videoMMap.format =  initFrame.type;
  int errorCode=0;

  //TODO: select, check wether driver supports it!
  
  fd_set readfds;
  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_SET(fd, &readfds);
  select(fd+1, &readfds, 0, 0, &tv);
  bool driver_ready = FD_ISSET(fd, &readfds);
  
  if (!driver_ready)
    std::cout << "SELECT -> no data\n";

  if (!drop && driver_ready)
    {      
      errorCode= ioctl(fd, VIDIOCMCAPTURE, &videoMMap);
      if(errorCode==-1)
	{
	  std::ostringstream errorMsg; 
	  errorMsg << "error while starting capture next buffer: ";
	  errorMsg << 0;
	  errorMsg << " errno= " << errno;
	  errorMsg << " errorstring= " << strerror(errno);
	  throw std::runtime_error(errorMsg.str());
	}
  
      std::swap(frontbf,backbf);
 
      errorCode = ioctl(fd, VIDIOCSYNC, &backbf);  
    }

  frame.frameptr=frameptr[backbf];
  frame.type=initFrame.type;
  if(errorCode==-1)
    {
      std::ostringstream errorMsg;
      errorMsg << "error while cyncing with last buffer: ";
      errorMsg << backbf << " !!!";
      errorMsg << " errno= " << errno;
      errorMsg << " errorstring= " << strerror(errno);
      throw std::runtime_error(errorMsg.str());
    }
}

void VideoDevice::setProperties(int brightness,int hue,int colour,
		   int contrast,
		   int whiteness)
{
  /*if (!
      (brightness==m_brightness)&&
      (hue==m_hue)&&
      (colour==m_colour)&&
      (contrast==m_contrast)&&
      (whiteness==m_whiteness)
      )*/
    {
      video_picture videopic;
      
      int errorCode = ioctl(fd, VIDIOCGPICT, &videopic);  
      if(errorCode==-1)
	{
	  std::ostringstream errorMsg;
	  errorMsg << " could not get image parameter: ";
	  errorMsg << " errno= " << errno;
	  errorMsg << " errorstring= " << strerror(errno);
	  throw std::runtime_error(errorMsg.str());
	}
      
      videopic.brightness=brightness;
      videopic.hue=hue;
      videopic.colour=colour;
      videopic.contrast=contrast;
      videopic.whiteness=whiteness;
      
      errorCode = ioctl(fd, VIDIOCSPICT, &videopic);  
      if(errorCode==-1)
	{
	  std::ostringstream errorMsg;
	  errorMsg << " could not set image parameter: ";
	  errorMsg << " errno= " << errno;
	  errorMsg << " errorstring= " << strerror(errno);
	  throw std::runtime_error(errorMsg.str());
	}

      m_brightness=brightness;
      m_hue=hue;
      m_colour=colour;
      m_contrast=contrast;
      m_whiteness=whiteness;
    }
}

