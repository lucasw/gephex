#include "v4l.h"

// lowlevel LINUX V4L headers
#include <sys/mman.h> // mmap - for mapping the framegrabber data in userspace
#include <sys/ioctl.h>
#include <sys/fcntl.h> //systemcall via filehandles
#include <unistd.h>
//#include <sys/signal.h>

// DEBUG
#include <iostream> //debug
#include "videodefostr.h" // debug

// errorhandling
#include <stdexcept>

  V4LGrabber::V4LGrabber(const std::string& deviceName)
  :m_lastGrabbedFrame(0)
  {
    // open videodevice file
    if( 0>(m_videoDevice = open(deviceName.c_str(),O_RDONLY)))
    {
      std::string errorMsg;
      errorMsg="Could not open videodevice: ";
      throw std::runtime_error(errorMsg);
    }
    // m_videoDevice is now the filehandle for the device
    #ifndef NDEBUG
      std::cout << "open(" <<deviceName << ",O_RDONLY) : "
           << m_videoDevice <<std::endl;
    #endif
  }

  void V4LGrabber::setGrabProperties(int width, int height)
  {
    // test for videocapture features
    int errorCode;
    video_capability cap; // struct will be filled with capture info
    if( (errorCode=ioctl(m_videoDevice, VIDIOCGCAP, &cap) ))
    {
      std::string errorMsg;
      errorMsg="Couldn't read videodev capability";
      throw std::runtime_error(errorMsg);
    }
    // video_capability has now valid infos about the video device
      std::cout << "ioctl(m_videoDevice, VIDIOCGCAP, &m_videoCapability) : "
           << errorCode << std::endl;
      std::cout << cap;

    // check if device can capture
    if (!(cap.type&VID_TYPE_CAPTURE))
    {
      std::string errorMsg;
      errorMsg="device could not capture";
      throw std::runtime_error(errorMsg);
    }
    //remember number of channels
    m_NrInputChannels=cap.channels;

    // check capture dimensions
    if (!((cap.minwidth<=width)&&(width<=cap.maxwidth)
       &&(cap.minheight<=height)&&(height<=cap.maxheight)))
    {
      std::string errorMsg;
      errorMsg="device could not capture that width or heigth";
      throw std::runtime_error(errorMsg);
    }

    // try to set the capture geometry(area)
    video_window videoWindow;
    // upper left corner position
    videoWindow.x = 0;
    videoWindow.y = 0;
    // capture area size
    videoWindow.width = width;
    videoWindow.height = height;
    // options
    videoWindow.flags = 0;
    videoWindow.clipcount = 0;
    videoWindow.clips = NULL;

    if ( (errorCode=ioctl(m_videoDevice, VIDIOCSWIN, &videoWindow)))
    {
      std::string errorMsg;
      errorMsg="Could not set desired grab geometry";
      throw std::runtime_error(errorMsg);
    }
      std::cout << "ioctl(m_videoDevice, VIDIOCSWIN, &videoWindow) : ";
      std::cout << errorCode << std::endl;


    // and check it(params could be different)
    // get setting back
    if( (errorCode=ioctl(m_videoDevice, VIDIOCGWIN, &videoWindow)))
    {
      std::string errorMsg;
      errorMsg="Could not read grab geometry";
      throw std::runtime_error(errorMsg);
    }
      std::cout << "ioctl(m_videoDevice, VIDIOCGWIN, &videoWindow) : ";
      std::cout << errorCode << std::endl;
      std::cout << videoWindow;


    if (((int)videoWindow.width!=width)||((int)videoWindow.height!=height))
    {
      std::string errorMsg;
      errorMsg="Grabber doesn't support that geometry";
      throw std::runtime_error(errorMsg);
    }
    m_width=width;
    m_height=height;

    // init memory mapping

    // get mmap info
    video_mbuf videoMBuf;
    if(( errorCode=ioctl(m_videoDevice, VIDIOCGMBUF, &videoMBuf)))
    {
      std::string errorMsg;
      errorMsg="Couldn't read mbuf info";
      throw std::runtime_error(errorMsg);
    }

      std::cout << "ioctl(m_videoDevice, VIDIOCGMBUF, &videoMBuf) : ";
      std::cout << errorCode << std::endl;
      std::cout << videoMBuf;


    // check if backbuffering is possible(2 frames)
    if (videoMBuf.frames<2)
    {
      std::string errorMsg;
      errorMsg="mmap can only 2 frames";
      throw std::runtime_error(errorMsg);
    }

    // start mmapping the framegrabber memory
    // mmap(NULL = beliebige Adresse,size in bytes des Bereichs,
    //    nur lesezugriff, ka,filedescriptor,ka)
    m_mmapSize = videoMBuf.size;
    m_mmapBase = mmap(NULL, m_mmapSize, PROT_READ, MAP_SHARED,
                          m_videoDevice, 0);
    if(m_mmapBase == MAP_FAILED)
      throw std::runtime_error("Couldn't mmap memory");


      std::cout << "mmap(NULL, videoMBuf.size, PROT_READ, MAP_SHARED, m_videoDevice, 0) : ";
      std::cout << (int)m_mmapBase << std::endl;


    // initialize vector with startpointer to the mapped frames
    m_frameptr = std::vector<unsigned int*>(videoMBuf.frames);
    for(int i=0; i<videoMBuf.frames; ++i)
      m_frameptr[i] = (unsigned int *)m_mmapBase + videoMBuf.offsets[i];
  }
    

  void V4LGrabber::setVideoInput(int channel, int norm)
  {
    // check if channel number is valid
    if (!(0<= channel && channel < m_channelmax))
      throw std::runtime_error("no valid input channel (void V4LGrabber::setVideoInput(int,int))");

    // check if norm number is valid
    // TODO check if constants are the right (VIDEO_MODE_xxxx or VIDEO_TUNER_xxxx)
    if (!(norm==VIDEO_MODE_PAL)||(norm==VIDEO_MODE_NTSC)||
      (norm==VIDEO_MODE_SECAM)||(norm==VIDEO_MODE_AUTO))
      throw std::runtime_error("no valid input norm (void V4LGrabber::setVideoInput(int,int))");

    #ifndef NDEBUG // output existing channels
    {
      video_channel videoChannel;
      for(int i=0; i<m_NrInputChannels; ++i)
      {
        videoChannel.channel = i;
        if(ioctl(m_videoDevice, VIDIOCGCHAN, &videoChannel))
          throw std::runtime_error("Couldn't read channel properties");
        std::cout << videoChannel;
      }
    }
    #endif

    // set input properties
    video_channel videoChannel;
    videoChannel.channel = channel; // input
    videoChannel.norm = norm; // videonorm PAL oder NTSC

    int errorCode;
    if ( (errorCode = ioctl(m_videoDevice, VIDIOCSCHAN, &videoChannel)))
      throw std::runtime_error ("Couldn't set proper channel");
    #ifndef NDEBUG
      std::cout << "ioctl(m_videoDevice, VIDIOCSCHAN, &videoChannel) : ";
      std::cout << errorCode << std::endl;
    #endif
  }

  V4LGrabber::~V4LGrabber()
  {
    if(m_mmapBase) munmap(m_mmapBase,m_mmapSize);
    if(m_videoDevice)close(m_videoDevice);
  }



  void V4LGrabber::getGrabbedImage(Frame& frame)
  {
    // return last grabbed buffer
    // sync the buffer
    // TODO
    int errorCode = ioctl(m_videoDevice, VIDIOCSYNC, &m_lastGrabbedFrame);
    /*if(errorCode == -1 && errno != EINTR)
    {
       std::cout << "error while reading from device! return: "
         << errorCode << "; errno: " << errno << endl;
      }*/

    // return it
    frame=(int*)m_frameptr[m_lastGrabbedFrame];
  }


  void V4LGrabber::setColorProperties(unsigned char brightness,
                      unsigned char contrast, unsigned char hue,
                      unsigned char saturation)
  {
    video_picture videoPicture; //v4l struct for image properties
    if(ioctl(m_videoDevice, VIDIOCGPICT, &videoPicture))
      throw std::runtime_error ("Couldn't get video properties");
    std:: cout << videoPicture << std::endl;

    videoPicture.brightness = (unsigned int)brightness << 8;
    videoPicture.hue = (unsigned int)hue << 8;
    videoPicture.colour = (unsigned int)saturation << 8;
    videoPicture.contrast = (unsigned int)contrast << 8;
    videoPicture.depth = 24;
    videoPicture.palette =  VIDEO_PALETTE_YUV420P;

    std:: cout << videoPicture << std::endl;

    if(ioctl(m_videoDevice, VIDIOCSPICT, &videoPicture))
      throw std::runtime_error ("Couldn't set video properties");
  }


  void V4LGrabber::grabNextImage()
  {
    //++m_lastGrabbedFrame;
    //if (m_lastGrabbedFrame==2) m_lastGrabbedFrame=0;
    video_mmap videoMMap; // v4l struct for mmap informations
    videoMMap.frame = m_lastGrabbedFrame; // buffer position
    videoMMap.height = m_height;
    videoMMap.width = m_width;
    videoMMap.format =  VIDEO_PALETTE_YUV420P;
    int errorCode;
    #ifndef NDEBUG
      std::cout << m_lastGrabbedFrame;
      std::cout.flush();
    #endif
    if( (errorCode = ioctl(m_videoDevice, VIDIOCMCAPTURE, &videoMMap)))
    {
      throw std::runtime_error("error while starting capture to buffer");
    }
    #ifndef NDEBUG
      //std::cout << "ioctl(m_videoDevice, VIDIOCMCAPTURE, &videoMMap) : ";
      //std::cout << errorCode << std::endl;
    #endif
  }












