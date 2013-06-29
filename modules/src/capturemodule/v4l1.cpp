#include "v4l1.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <sstream>
#include <videodev.h>

#include <errno.h>

struct v4l1_intern
{
  int fd;
  video_capability cap; 
};

v4l1_device::v4l1_device(const std::string& device_name)
  :intern(new v4l1_intern())
{
  intern->fd=open(device_name.c_str(),O_RDONLY);

  try
    {
      // check for an error
      if(intern->fd==-1)
	{ 
	  // an error occured. exit
	  std::ostringstream errorMsg;
	  errorMsg << "v4l1_device::v4l1_device(\"" << device_name <<"\"): ";
	  errorMsg << "open: "<< strerror(errno) << "(" << errno << ")";
	  throw std::runtime_error(errorMsg.str());
	}
      
      
      
      // lets check if it is a v4l device
      int error =ioctl(intern->fd, VIDIOCGCAP, &intern->cap);
      if(error==-1)
	{
	  // seems to be not V4L Device
	  // close file and exit with an exception
	  std::ostringstream errorMsg;
	  errorMsg << "v4l1_device::v4l1_device(\"" << device_name <<"\"): ";
	  errorMsg << "VIDIOCGCAP(" << intern->fd << "): " ;
	  errorMsg << strerror(errno) << "(" << errno << ")";
	  throw std::runtime_error(errorMsg.str());
	}

      // check if device can capture
      if (!intern->cap.type&VID_TYPE_CAPTURE)
	{
	  // this v4l device cant capture
	  // close file and exit with an exception
	  std::ostringstream errorMsg;
	  errorMsg << "v4l1_device::v4l1_device(\""<< device_name <<"\"): ";
	  errorMsg << "VIDIOCGCAP";
	  errorMsg << "device can not capture";
	  throw std::runtime_error(errorMsg.str());
	}

  // the device is open and ready to capture

    } 
  catch (std::runtime_error& e) 
    {
      close(intern->fd);
      std::cerr << e.what();
      throw e;
    }
}

v4l1_device::~v4l1_device()
{
  close(intern->fd);
  delete intern;
  
}

int v4l1_device::fd()
{
  return intern->fd;
}

const video_capability& v4l1_device::cap()
{
  return intern->cap;
}


bool v4l1_device::select()
{
  if (false)
    {
      fd_set readfds;
      struct timeval tv;
      tv.tv_sec = 0;
      tv.tv_usec = 0;
      FD_ZERO(&readfds);
      FD_SET(intern->fd, &readfds);
      ::select(intern->fd+1, &readfds, 0, 0, &tv);
      return FD_ISSET(intern->fd, &readfds);
    }
  else
    {
      return true;
    }
}

void v4l1_device::munmap(void* mmapBase,size_t mmapSize)
{
  int errorCode= ::munmap(mmapBase,mmapSize);
  if (errorCode==-1)
    {
      std::ostringstream errorMsg;
      
      errorMsg << "error while munmap ";
      errorMsg << " errno= " << errno;
      errorMsg << " errorstring= " << strerror(errno);
      
      throw std::runtime_error( errorMsg.str() );
    }
}


void* v4l1_device::mmap(size_t size)
{
  void* mmapBase = ::mmap(NULL,size,PROT_READ,MAP_SHARED,intern->fd,0);
  
  if(mmapBase == MAP_FAILED)
    {
      throw std::runtime_error("Couldn't mmap memory");
    }
  return mmapBase;
}



void v4l1_device::vidiocmcapture(video_mmap& videoMMap)
{
  int errorCode = ioctl( intern->fd , VIDIOCMCAPTURE , &videoMMap );
  
  if ( errorCode == -1 )
    {
      std::ostringstream errorMsg; 
      
      errorMsg << "error while starting capture next buffer: ";
      errorMsg << 0;
      errorMsg << " errno= " << errno;
      errorMsg << " errorstring= " << strerror(errno);
      
      throw std::runtime_error( errorMsg.str() );
    }
}

  
void v4l1_device::vidiocsync(int backbf)
{
  int errorCode = ioctl( intern->fd , VIDIOCSYNC , &backbf );  
  
  if ( errorCode == -1 )
    {
      std::ostringstream errorMsg;
      
      errorMsg << "error while cyncing with last buffer: ";
      errorMsg << backbf << " !!!";
      errorMsg << " errno= " << errno;
      errorMsg << " errorstring= " << strerror(errno);
      
      throw std::runtime_error( errorMsg.str() );
    }
}

  
void v4l1_device::vidiocswin(video_window& videoWindow)
{
  int errorCode = ioctl( intern->fd , VIDIOCSWIN , &videoWindow );
  
  if ( errorCode == -1 )
    {
      std::string errorMsg;
      
      errorMsg="Could not set desired grab geometry";
      
      throw std::runtime_error( errorMsg );
    }
}
  
  
void v4l1_device::vidiocgwin(video_window& videoWindow)
{
  int errorCode = ioctl ( intern->fd , VIDIOCGWIN , &videoWindow );
  
  if ( errorCode == -1 )
    {
      std::string errorMsg;
      
      errorMsg="Could not read grab geometry";
      
      throw std::runtime_error( errorMsg );
    }
}

  
void v4l1_device::vidiocgmbuf(video_mbuf& videoMBuf)
{
  int errorCode = ioctl ( intern->fd , VIDIOCGMBUF, &videoMBuf );
  
  if ( errorCode == -1 )
    {
      std::string errorMsg;
      
      errorMsg="Couldn't read mbuf info";
      
      throw std::runtime_error( errorMsg );
    }
}

  
void v4l1_device::vidiocgpict(video_picture& videopic)
{
  int errorCode = ioctl ( intern->fd , VIDIOCGPICT , &videopic );  
  
  if ( errorCode == -1 )
    {
      std::ostringstream errorMsg;
      
      errorMsg << " could not get image parameter: ";
      errorMsg << " errno= " << errno;
      errorMsg << " errorstring= " << strerror(errno);
	  
      throw std::runtime_error( errorMsg.str() );
    }
}
  
  
void v4l1_device::vidiocspict(video_picture& videopic)
{
  int errorCode = ioctl( intern->fd , VIDIOCSPICT , &videopic );
  
  if ( errorCode == -1 )
    {
      std::ostringstream errorMsg;
      
      errorMsg << " could not set image parameter: ";
      errorMsg << " errno= " << errno;
      errorMsg << " errorstring= " << strerror(errno);
      
      throw std::runtime_error( errorMsg.str() );
    }
}


size_t v4l1_device::min_width()
{
  return intern->cap.minwidth;
}

size_t v4l1_device::max_width()
{
  return intern->cap.maxwidth;
}

size_t v4l1_device::min_height()
{
  return intern->cap.minheight;
}

size_t v4l1_device::max_height()
{
  return intern->cap.maxheight;
}
