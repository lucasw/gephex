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

// debug
//#include "videodefostr.h"
#include <iostream>

VideoDevice::VideoDevice(const std::string& deviceFileName, logT log2_)   
  throw (std::runtime_error)
  :initialized(false),frontbf(1),log2(log2_)
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

void VideoDevice::grabImage(Frame& frame) throw (std::runtime_error)
{
  // the default size is minimum size
  if (frame.xSize==0)
    frame.xSize=cap.minwidth;
  if (frame.ySize==0)
    frame.ySize=cap.minheight;

  frame.xSize-=frame.xSize%4;
  frame.ySize-=frame.ySize%4;
  
  //
  // is initialized and grab geometry has changed
  if (initialized &&
      !(frame.xSize==initFrame.xSize&&frame.ySize==initFrame.ySize))
    {
      log2(2,"geometry has changed");
      //sync to last
      std::swap(frontbf,backbf);
      
      assert(frontbf!=backbf);
      //std::cout << "csync " << backbf <<std::endl;
      log2(2,"get missing frames");
      int errorCode = ioctl(fd, VIDIOCSYNC, &backbf);  
      if(errorCode==-1)
	{
	  std::ostringstream errorMsg;
	  errorMsg << "error while cyncing with last buffer: ";
	  errorMsg << backbf << " !!!";
	  errorMsg << " errno= " << errno;
	  errorMsg << " errorstring= " << strerror(errno);
	  log2(2,errorMsg.str().c_str());
	  //throw std::runtime_error(errorMsg.str());
	}
      
      log2(2,"unmap");
      errorCode= munmap(mmapBase,mmapSize);
      if (errorCode==-1)
	{
	  std::ostringstream errorMsg;
	  errorMsg << "error while munmap ";
	  errorMsg << " errno= " << errno;
	  errorMsg << " errorstring= " << strerror(errno);
	  log2(2,errorMsg.str().c_str());
	  //throw std::runtime_error(errorMsg.str());
	}
      initialized=false;
      log2(2,"uninitialized");
    }

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
	  errorMsg << "Grabber doesn't support that geometry" << std::endl;
	  errorMsg << "requested: " << frame.xSize << " " << frame.ySize;
	  errorMsg << " returned: " << videoWindow.width << " " << videoWindow.height;
	  
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
      //for(int i=0; i<videoMBuf.frames; ++i)
      for(int i=0; i!=2; ++i)
	{
	  frameptr[i]=reinterpret_cast<uint_32*>(reinterpret_cast<char*>(mmapBase)+videoMBuf.offsets[i]);
	  //std::cout << frameptr[i]<< std::endl;
	}
      
      frontbf=0;
      backbf=1;

      video_mmap videoMMap; // v4l struct for mmap informations
      videoMMap.frame = frontbf; // buffer position
      videoMMap.width = frame.xSize;
      videoMMap.height = frame.ySize;
      //videoMMap.format =  VIDEO_PALETTE_RGB32;
      videoMMap.format =  VIDEO_PALETTE_YUV420P;
      //std::cout << "cmcap" << frontbf <<std::endl;
      errorCode= ioctl(fd, VIDIOCMCAPTURE, &videoMMap);
      if(errorCode==-1)
	{
	  throw std::runtime_error("error while starting capture to buffer");
	}
      
      //initialize;
      initFrame=frame;
      initialized=true;
    }
  else
    {

    }

  assert(initialized);
  //assert(frontbf==0||frontbf==1);
  //assert(backbf==0||backbf==1);

  //std::cout << frame.xSize << " " << frame.ySize<< std::endl;;
  video_mmap videoMMap; // v4l struct for mmap informations
  videoMMap.frame = backbf; // buffer position
  videoMMap.width = frame.xSize;
  videoMMap.height = frame.ySize;
  //videoMMap.format =  VIDEO_PALETTE_RGB32;
  videoMMap.format =  VIDEO_PALETTE_YUV420P;
  // std::cout << "cmcap " << backbf <<std::endl;
  int errorCode= ioctl(fd, VIDIOCMCAPTURE, &videoMMap);
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
  
  assert(frontbf!=backbf);
  //std::cerr << "csync " << backbf <<std::endl;
  errorCode = ioctl(fd, VIDIOCSYNC, &backbf);  
  if(errorCode==-1)
     {
      std::ostringstream errorMsg;
      errorMsg << "error while cyncing with last buffer: ";
      errorMsg << backbf << " !!!";
      errorMsg << " errno= " << errno;
      errorMsg << " errorstring= " << strerror(errno);
      //throw std::runtime_error(errorMsg.str());
log2(2,errorMsg.str().c_str());
      }

  frame.frameptr=frameptr[backbf];
  

}
