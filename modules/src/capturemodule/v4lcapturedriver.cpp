/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004
 
 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
  
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
   
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
	
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#include "v4lcapturedriver.h"

#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include "stdint.h"

#include <cassert>

// for stat
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "v4l1.h"
#include "libscale.h"
#include "libcolorconv.h"


//----------------------------------------------------------------------

void cvt_bgra32_to_bgra(uint8_t* dst_, uint8_t* src_,
			size_t width, size_t height)
{
  uint32_t* dst = reinterpret_cast<uint32_t*>( dst_ );
  uint32_t* src = reinterpret_cast<uint32_t*>( src_ );
  std::copy(src, src + (width*height), dst);
}


class V4LCaptureDriver::Impl
{
public:
  Impl():m_width(0),m_height(0) 
  {
  }
  ~Impl()  {}
	
  void close()  						
  {
    vd->munmap(m_mmapBase,m_mmapSize);
    delete[]  m_tmp_img;
    vd.reset();
  }
	
  void open(int device_num)
  {
    // check device_num_range
    if (device_num<0)
      throw std::range_error("negative v4l device number");

    // generate v4l device name
    std::ostringstream device_name_stream;
    device_name_stream << "/dev/video" << device_num;
    std::string device_name(device_name_stream.str());
    
    // check device file
    struct stat stat_buf;
    int error_code = stat(device_name.c_str(), &stat_buf);
    
    if (error_code==-1)
      throw std::runtime_error("could not stat v4l device file: "+std::string(strerror(errno)));

    // is it a character device?
    if (!S_ISCHR(stat_buf.st_mode))
      throw std::runtime_error("devicefile is no character device");

    try
      {
	
    vd = std::auto_ptr<v4l1_device>(new v4l1_device(device_name));

    // get capture dimensions
    video_window videoWindow;
    vd->vidiocgwin(videoWindow);
    m_width=videoWindow.width;
    m_height=videoWindow.height;

    // init memory mapping
    // get mmap info
    video_mbuf videoMBuf;
  
    vd->vidiocgmbuf(videoMBuf);
  
    // check if backbuffering is possible(2 frames)
    if (videoMBuf.frames<2)
      {
	std::string errorMsg;
	errorMsg="mmap cant grab 2 frames";
	throw std::runtime_error(errorMsg);
      }
  
    // start mmapping the framegrabber memory
    m_mmapSize=videoMBuf.size;
  
    m_mmapBase=vd->mmap(m_mmapSize);
  
    // initialize array with startpointer to the mapped frames
    for(int i=0; i!=2; ++i)
    {
      m_frame_ptr.push_back(reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(m_mmapBase)+videoMBuf.offsets[i]));
    }
  
    m_front_buf_idx=0;
    m_back_buf_idx=1;
  
    video_mmap videoMMap; // v4l struct for mmap informations
    videoMMap.frame = m_front_buf_idx; // buffer position
    videoMMap.width = m_width;
    videoMMap.height = m_height;
    
    // probe pixelformats
  // todo - use a set of pixel format and probe each
  try
    {
      // try RGBA
      videoMMap.format =  VIDEO_PALETTE_RGB32;
      vd->vidiocmcapture(videoMMap);
    }
  catch(std::runtime_error& e)
    {
      try
	{
	  // try YUV
	  videoMMap.format =  VIDEO_PALETTE_YUV420P;
	  vd->vidiocmcapture(videoMMap);
	}
      catch(std::runtime_error& e)
	{
	  throw std::runtime_error("error while starting capture to buffer");
	}
    }
  
  m_pixel_format=videoMMap.format;

  m_tmp_img = new uint32_t[m_width*m_height];

      }
    catch(std::runtime_error& e)
      {
	vd.release();
	throw e;
      }
  }

  void grab_frame(uint_32* frb, int width, int height)
  {
    video_mmap videoMMap; // v4l struct for mmap informations
    videoMMap.frame = m_back_buf_idx; // buffer position
    videoMMap.width = m_width;
    videoMMap.height = m_height;
    videoMMap.format =  m_pixel_format;

    // start new frame capture
    vd->vidiocmcapture(videoMMap);
    
    std::swap(m_front_buf_idx,m_back_buf_idx);
    
    // block until old capture has finished
    vd->vidiocsync(m_back_buf_idx);
    
    uint32_t* raw_img = m_frame_ptr[m_back_buf_idx];

        // convert the grabber framebuffer format to brga32(gephex default)
    switch (m_pixel_format)
      {
      case VIDEO_PALETTE_RGB32: // tested with a bttv 878 card
	cvt_bgra32_to_bgra(reinterpret_cast<uint_8*>(m_tmp_img),
		      reinterpret_cast<uint_8*>(raw_img),
		      m_width,m_height);
	break;
      case VIDEO_PALETTE_YUV420P: // tested with a phillips webcam
	// convert the image from yuvp to bgra
	cvt_yuv420p_to_bgra(reinterpret_cast<uint_8*>(m_tmp_img),
			    reinterpret_cast<uint_8*>(raw_img),
			    m_width,m_height);
	  break;
      default:
	throw std::runtime_error("unsupported pixelformat");
      }

    ls_scale32(frb, width, height, m_tmp_img, m_width, m_height);
      
    
  }
  
  bool is_open() const
  {
    return vd.get()!=0;
  }
  
  int width() const { return m_width; }

  int height() const { return m_height; }
  
  bool new_sample() const { return true; }

private:
  unsigned int m_width;
  unsigned int m_height;
  unsigned int m_pixel_format;
  unsigned int m_front_buf_idx;
  unsigned int m_back_buf_idx;
  void* m_mmapBase;
  unsigned int m_mmapSize;
  std::vector<uint32_t*> m_frame_ptr;
  std::auto_ptr<v4l1_device> vd;
  uint32_t* m_tmp_img;
};

//----------------------------------------------------------------------

V4LCaptureDriver::V4LCaptureDriver()
  : m_impl(new Impl())
{
}

V4LCaptureDriver::~V4LCaptureDriver()
{
}


void V4LCaptureDriver::open(int device)
{
  if (m_impl->is_open())
    throw std::logic_error("Device already open");
	
  m_impl->open(device);
}

void V4LCaptureDriver::close()
{
  if (m_impl->is_open())
    m_impl->close();
}

void V4LCaptureDriver::decode_frame(uint_32* framebuffer,
                                    int width, int height)
{
  if (!m_impl->is_open())
    throw std::logic_error("Device not open");
	
  m_impl->grab_frame(framebuffer, width, height);
}

void V4LCaptureDriver::status(int& width,
                              int& height,
                              bool& new_sample) const
{
  width      = m_impl->width();
  height     = m_impl->height();
  new_sample = m_impl->new_sample();
}

bool V4LCaptureDriver::is_open() const
{
  return m_impl->is_open();
}
