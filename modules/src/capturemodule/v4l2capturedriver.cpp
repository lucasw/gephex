/* This source file is a part of the GePhex Project. The v4l2 specific
  stuff has been shamelessly taken from the v4l2 documentation on
  http://v4l2spec.bytesex.org/

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

#include "v4l2capturedriver.h"

#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <iostream>

#include <cassert>

#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <asm/types.h>          /* for videodev2.h */

#include "videodev2.h"  // local copy of kernel header


#include "libscale.h"
#include "libcolorconv.h"


//----------------------------------------------------------------------

struct buffer_t
{
  void * start;
  size_t length;
};

static int xioctl(int fd, int request, void* arg)
{
  int r;

  do r = ioctl (fd, request, arg);
  while (-1 == r && EINTR == errno);

  return r;
}

static void cvt_bgra32_to_bgra(uint8_t* dst_, uint8_t* src_,
			size_t width, size_t height)
{
  uint32_t* dst = reinterpret_cast<uint32_t*>( dst_ );
  uint32_t* src = reinterpret_cast<uint32_t*>( src_ );
  std::copy(src, src + (width*height), dst);
}

static void init_mmap(int fd, buffer_t*& buffers)
{
  struct v4l2_requestbuffers req;

  memset(&req, 0, sizeof(req));

  req.count               = 2;
  req.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  req.memory              = V4L2_MEMORY_MMAP;

  if (-1 == xioctl (fd, VIDIOC_REQBUFS, &req))
    {
      if (EINVAL == errno)
	throw std::runtime_error("does not support memory mapping");
      else
	throw std::runtime_error("VIDIOC_REQBUFS");
    }

  if (req.count < 2)
    throw std::runtime_error("Insufficient buffer memory");
  
  buffers = (buffer_t*) calloc (req.count, sizeof (*buffers));

  if (!buffers)
    throw std::runtime_error("Out of memory\n");

  assert(req.count == 2);

  for (int n_buffers = 0; n_buffers < req.count; ++n_buffers)
    {
      struct v4l2_buffer buf;

      memset(&buf, 0, sizeof(buf));

      buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      buf.memory      = V4L2_MEMORY_MMAP;
      buf.index       = n_buffers;

      if (-1 == xioctl (fd, VIDIOC_QUERYBUF, &buf))
	{
	  free(buffers);
	  buffers = 0;
	  throw std::runtime_error("VIDIOC_QUERYBUF");
	}

      buffers[n_buffers].length = buf.length;
      buffers[n_buffers].start =
	mmap (NULL /* start anywhere */,
	      buf.length,
	      PROT_READ | PROT_WRITE /* required */,
	      MAP_SHARED /* recommended */,
	      fd, buf.m.offset);

    if (MAP_FAILED == buffers[n_buffers].start)
      {
	free(buffers);
	buffers = 0;
	throw std::runtime_error("mmap");
      }
  }
}

static void uninit_mmap(buffer_t*& buffers, int n_bufs)
{
  for (int i = 0; i < n_bufs; ++i)
    if (-1 == munmap (buffers[i].start, buffers[i].length))
      //      throw std::runtime_error("munmap");
      std::cout << "error at munmap";
  
  free (buffers);
  buffers = 0;
}

static void init_device(int fd,
			unsigned int& width,
			unsigned int& height,
			unsigned int& pixelformat)
{
  struct v4l2_capability cap;

  if (-1 == xioctl (fd, VIDIOC_QUERYCAP, &cap))
    {
      if (EINVAL == errno)
	{
	  throw std::runtime_error("no V4L2 device");
	}
      else
	{
	  throw std::runtime_error("VIDIOC_QUERYCAP");
	}
    }

  if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
      throw std::runtime_error("is no video capture device");
    }

  // test for mmap support
  if (!(cap.capabilities & V4L2_CAP_STREAMING))
    {
      throw std::runtime_error("does not support streaming i/o");
    }

  struct v4l2_cropcap cropcap;

  /* Select video input, video standard and tune here. */

  cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

  if (-1 == xioctl (fd, VIDIOC_CROPCAP, &cropcap))
    {
      /* Errors ignored. */
    }

  struct v4l2_crop crop;

  crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  crop.c = cropcap.defrect; /* reset to default */

  if (-1 == xioctl (fd, VIDIOC_S_CROP, &crop))
    {
      switch (errno) {
      case EINVAL:
	/* Cropping not supported. */
	break;
      default:
	/* Errors ignored. */
	break;
      }
    }

  struct v4l2_format fmt;

  memset(&fmt, 0, sizeof(fmt));

  fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  fmt.fmt.pix.width       = width;
  fmt.fmt.pix.height      = height;
  fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;


  // probe for pixel format
  fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_BGR32;

  if (-1 == xioctl (fd, VIDIOC_TRY_FMT, &fmt))
    {
      fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUV420;
      
      if (-1 == xioctl (fd, VIDIOC_TRY_FMT, &fmt))
	throw std::runtime_error("Could not negotiate pixel format");
    }

  // set the probed format
  if (-1 == xioctl (fd, VIDIOC_S_FMT, &fmt))
    throw std::runtime_error("Could not set pixel format");

  /* Note VIDIOC_S_FMT may change width and height. */

  width       = fmt.fmt.pix.width;
  height      = fmt.fmt.pix.height;
  pixelformat = fmt.fmt.pix.pixelformat;

  /* Buggy driver paranoia. */
  unsigned int min;

  min = fmt.fmt.pix.width * 2;
  if (fmt.fmt.pix.bytesperline < min)
    fmt.fmt.pix.bytesperline = min;
  min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
  if (fmt.fmt.pix.sizeimage < min)
    fmt.fmt.pix.sizeimage = min;

}

static void start_capturing(int fd, int n_bufs)
{
  enum v4l2_buf_type type;

  for (int i = 0; i < n_bufs; ++i)
    {
      struct v4l2_buffer buf;

      memset(&buf, 0, sizeof(buf));

      buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      buf.memory      = V4L2_MEMORY_MMAP;
      buf.index       = i;

      if (-1 == xioctl (fd, VIDIOC_QBUF, &buf))
	throw std::runtime_error("start_capturing VIDIOC_QBUF");
    }
                
  type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

  if (-1 == xioctl (fd, VIDIOC_STREAMON, &type))
    throw std::runtime_error("VIDIOC_STREAMON");
}

static void stop_capturing(int fd)
{
  enum v4l2_buf_type type;

  type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  
  if (-1 == xioctl (fd, VIDIOC_STREAMOFF, &type))
    //throw std::runtime_error("VIDIOC_STREAMOFF");
    std::cout << "error at streamoff";
}


class V4L2CaptureDriver::Impl
{
public:
  Impl()
    : m_fd(-1),m_width(0), m_height(0), m_buffers(0),
      m_capturing_started(false), m_tmp_image(0),
      m_tmp_image_size(0)
  {
  }
  ~Impl()  {}
	
  void close()  						
  {

    if (m_tmp_image_size != 0)
      {
	delete[] m_tmp_image;
	m_tmp_image      = 0;
	m_tmp_image_size = 0;
      }

    if (m_capturing_started)
      {
	stop_capturing(m_fd);
	m_capturing_started = false;
      }
    
    uninit_mmap(m_buffers, 2);

    ::close(m_fd);
    m_fd = -1;
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
      throw std::runtime_error("could not stat v4l device file: "
			       + std::string(strerror(errno)));

    // is it a character device?
    if (!S_ISCHR(stat_buf.st_mode))
      throw std::runtime_error("devicefile is no character device");

    m_device_name = device_name;
    m_fd = ::open(m_device_name.c_str(), O_RDWR /* required */ | O_NONBLOCK, 0);
    
    if (-1 == m_fd)
      throw std::runtime_error("Cannot open device file");

    try
      {	
	m_width  = 640;
	m_height = 480;
	init_device(m_fd, m_width, m_height, m_pixel_format);
	init_mmap(m_fd, m_buffers);
      }
    catch (std::exception&)
      {
	::close(m_fd);
	throw;
      }
  }


  void grab_frame(uint_32* frb, int width, int height)
  {
    if (m_fd == -1 || !m_buffers || width != m_width || height != m_height)
      {
	if (m_capturing_started)
	  {
	    stop_capturing(m_fd);
	    m_capturing_started = false;
	  }

	if (m_buffers)
	  uninit_mmap(m_buffers, 2);

	if (m_fd != -1)
	  {
	    ::close(m_fd);
	    m_fd = -1;
	  }

	unsigned int w = width;
	unsigned int h = height;

	m_fd = ::open(m_device_name.c_str(), O_RDWR /* required */ | O_NONBLOCK, 0);
	if (m_fd == -1)
	  throw std::runtime_error("Could not reopen device");

	// can change w and h
	init_device(m_fd, w, h, m_pixel_format);

	m_width  = w;
	m_height = h;
	init_mmap(m_fd, m_buffers);
      }

    if (!m_buffers)
      return;

    struct v4l2_buffer buf;
    try
      {
	if (!m_capturing_started)
	  {
	    start_capturing(m_fd, 2);
	    m_capturing_started = true;
	  }

	memset(&buf, 0, sizeof(buf));

	buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;

	if (-1 == xioctl (m_fd, VIDIOC_DQBUF, &buf))
	  {
	    switch (errno)
	      {
	      case EAGAIN:
		std::cout << "v4l2: EAGAIN!!!\n";
		return;
	      case EIO:
		throw std::runtime_error("VIDIOC_DQBUF: EIO");
		/* Could ignore EIO, see spec. */
		/* fall through */
	      default:
		throw std::runtime_error("VIDIOC_DQBUF");
	      }
	  }

	assert (buf.index < 2);
      }
    catch (...)
      {
	// close everything down on error, will be reopened on next
	// update
	if (m_capturing_started)
	  {
	    stop_capturing(m_fd);
	    m_capturing_started = false;
	  }

	if (m_buffers)
	  uninit_mmap(m_buffers, 2);

	if (m_fd != -1)
	  {
	    ::close(m_fd);
	    m_fd = -1;
	  }
	throw;
      }


    //  process_image (buffers[buf.index].start);
    uint8_t* raw_img = reinterpret_cast<uint8_t*>(m_buffers[buf.index].start);

    // resize tmp_image
    int needed_size = m_width*m_height*4;
    if (m_tmp_image_size < needed_size)
      {
	delete[] m_tmp_image;
	m_tmp_image = new uint8_t[needed_size];
      }

    // convert the grabber framebuffer format to brga32(gephex default)
    switch (m_pixel_format)
      {
      case V4L2_PIX_FMT_BGR32: // tested with a bttv 878 card
	cvt_bgra32_to_bgra(reinterpret_cast<uint_8*>(m_tmp_image),
			   reinterpret_cast<uint_8*>(raw_img),
			   m_width,m_height);
	break;
      case V4L2_PIX_FMT_YUV420: // tested with a phillips webcam
	// convert the image from yuvp to bgra
	cvt_yuv420p_to_bgra(reinterpret_cast<uint_8*>(m_tmp_image),
			    reinterpret_cast<uint_8*>(raw_img),
			    m_width,m_height);
	break;
      default:
	throw std::runtime_error("unsupported pixelformat");
      }

    ls_scale32(frb, width, height, (uint32_t*) m_tmp_image, m_width, m_height);

    if (-1 == xioctl (m_fd, VIDIOC_QBUF, &buf))
      throw std::runtime_error ("grab_frame VIDIOC_QBUF");
  }
  
  bool is_open() const
  {
    return m_fd != -1;
  }
  
  int width() const { return m_width; }

  int height() const { return m_height; }
  
  bool new_sample() const
  {
    struct timeval tv;
    fd_set readfds;

    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&readfds);
    FD_SET(m_fd,&readfds);
    select(m_fd+1,&readfds,0,0,&tv);
    //TODO: handle EINTR

    return FD_ISSET(m_fd, &readfds);
  }

private:
  int m_fd;
  unsigned int m_width;
  unsigned int m_height;
  unsigned int m_pixel_format;

  struct buffer_t* m_buffers;

  bool m_capturing_started;

  uint8_t* m_tmp_image;
int m_tmp_image_size;

std::string m_device_name;
};

//----------------------------------------------------------------------

V4L2CaptureDriver::V4L2CaptureDriver()
  : m_impl(new Impl())
{
}

V4L2CaptureDriver::~V4L2CaptureDriver()
{
}


void V4L2CaptureDriver::open(int device)
{
  if (m_impl->is_open())
    throw std::logic_error("Device already open");
	
  m_impl->open(device);
}

void V4L2CaptureDriver::close()
{
  if (m_impl->is_open())
    m_impl->close();
}

void V4L2CaptureDriver::decode_frame(uint_32* framebuffer,
                                    int width, int height)
{
  if (!m_impl->is_open())
    throw std::logic_error("Device not open");
	
  m_impl->grab_frame(framebuffer, width, height);
}

void V4L2CaptureDriver::status(int& width,
			       int& height,
			       bool& new_sample) const
{
  width      = m_impl->width();
  height     = m_impl->height();
  new_sample = m_impl->new_sample();
}

bool V4L2CaptureDriver::is_open() const
{
  return m_impl->is_open();
}
