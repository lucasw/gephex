/* This source file is a part of the GePhex Project.

 Copyright (C) 2004

 Martin Bayer <martin@gephex.org> 
 
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

#include "y4moutputmodule.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <stdexcept>

#include "libcolorconv.h"
#include "libscale.h"

static logT s_log;

static const int WAIT_CYCLES_AFTER_REOPEN = 1;

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(_MSC_VER)
#include <io.h>

//#define close _close
//#define open _open
//#define write _write
#elif defined(OS_POSIX)
#include <unistd.h> // for write and close
#endif

enum color_model_t {NONE, YUV420P, BGRA8888};


struct stream_dsc
{
  stream_dsc()
    : color_model(NONE), fd(0)
  {
    scaledFb=framebuffer_newInstance();
  }

  ~stream_dsc()
  {
    if (fd) close(fd);
    
    framebuffer_deleteInstance(scaledFb);
  }

  std::string filename;
  color_model_t color_model;
  int fd;
  size_t x_res;
  size_t y_res;
  std::vector<uint8_t> yuv_buf;
  size_t stream_header_size;
  size_t frame_header_size;
  bool wrote_header;
  FrameBufferType* scaledFb;
};

static std::map<std::string,stream_dsc*> stream_registry;

struct _MyInstance
{
  //std::map<std::string,stream_dsc> dsc;
  int wait_cycles;
};

typedef _MyInstance MyInstance;
typedef _MyInstance* MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = new MyInstance;

  if (my == 0)
    return 0;

  my->wait_cycles = 0;

  return my;
}

void destruct(MyInstance* my)
{
  delete my;
}

static int get_frame_size(int w, int h, color_model_t cm)
{
  switch(cm)
    {
    case YUV420P:
      return (w*h*6)/4;
    case BGRA8888:
      return w*h*4;
    default:
      assert(!"invalid color model in get_frame_size()");
      return 0;
    }
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstance& my = *inst->my;

  if (my.wait_cycles > 0)
    {
      --my.wait_cycles;
      return;
    }

  std::string filename(inst->in_filename->text);
  std::string color_model_s(inst->in_color_model->text);
  color_model_t color_model;

  if (color_model_s == "yuv420p")
    color_model = YUV420P;
  else if (color_model_s == "bgra8888")
    color_model = BGRA8888;
  else
    {
      std::ostringstream os;
      os << "Unknown colormodel '" << color_model_s << "', using 'yuv420p'";
      s_log(1, os.str().c_str());

      color_model = YUV420P;
    }

  std::map<std::string,stream_dsc*>::iterator it;
  it=stream_registry.find(filename);
  if (it == stream_registry.end())
    stream_registry.insert(std::make_pair(filename,new stream_dsc()));

  stream_dsc& stream=*stream_registry[filename];

  try
    {
  int xsize = trim_int(inst->in_xsize->number, 1, 1400);
  int ysize = trim_int(inst->in_ysize->number, 1, 1080);

  // change size to valid one
  xsize -= xsize%4;
  ysize -= ysize%4;

  // yuv4mpeg2 spec
  assert(xsize%4==0);
  assert(ysize%4==0);

  // new stream?
  if (stream.fd == 0 || 
      filename != stream.filename ||
      xsize != stream.x_res || 
      ysize != stream.y_res ||
      color_model != stream.color_model)
    {
      if (stream.fd != 0)
	{
	  close(stream.fd);
          stream.fd = 0;

          // wait some time to give the reader process enough time
          // to reopen the stream
          if (filename == stream.filename)
            my.wait_cycles = WAIT_CYCLES_AFTER_REOPEN;
          return;
	}
      
      // new stream
      stream.x_res       = xsize;
      stream.y_res       = ysize;
      stream.filename    = filename;
      stream.color_model = color_model;
      
      // open new file
      
      stream.fd = open(filename.c_str(),O_WRONLY|O_CREAT|O_TRUNC,00666);
      if (stream.fd == -1)
	{
	  stream.fd = 0;
	  throw std::runtime_error("could not open stream");
	}
      
      std::ostringstream stream_header_str;

      switch(stream.color_model)
        {
        case YUV420P:  stream_header_str << "YUV4MPEG2 "; break;
        case BGRA8888: stream_header_str << "BGRA8888 "; break;
        default: assert(!"invalid color model");
        }

      stream_header_str << "W" << stream.x_res << " ";
      stream_header_str << "H" << stream.y_res << " ";
      stream_header_str << "F25:1 Ip A0:0\n";
      
      std::string stream_header(stream_header_str.str());
      stream.stream_header_size=stream_header.length();
      
      std::string frame_header("FRAME\n");
      stream.frame_header_size=frame_header.length();
      
      stream.yuv_buf.resize(stream.stream_header_size +
                            stream.frame_header_size + 
                            get_frame_size(stream.x_res,
                                           stream.y_res,
                                           stream.color_model));
      
      // stream_header
      std::copy(stream_header.begin(),
		stream_header.end(),
		stream.yuv_buf.begin());
      
      // frame_header
      std::copy(frame_header.begin(),
		frame_header.end(),
		stream.yuv_buf.begin() + stream.stream_header_size);
      
      // write header next time
      stream.wrote_header=false;
    }

  uint8_t* buf = &stream.yuv_buf[stream.stream_header_size +
    stream.frame_header_size];

  if (stream.color_model == YUV420P)
    {
      // the framebuffer
      uint32_t* fb;

      if (inst->in_in->xsize != stream.x_res ||
          inst->in_in->ysize != stream.y_res)
        {
          FrameBufferAttributes  in_attr;
          framebuffer_getAttributes(inst->in_in, &in_attr);
          in_attr.xsize=stream.x_res;
          in_attr.ysize=stream.y_res;
          framebuffer_convertType(stream.scaledFb, inst->in_in , &in_attr);
      
          // use the scaled one
          fb = stream.scaledFb->framebuffer;
        }
      else
        {
          // use the original
          fb = inst->in_in->framebuffer;
        }

      // convert
      int pitches[3] ={stream.x_res, stream.x_res/2, stream.x_res/2 };
      int offsets[3] ={0, stream.x_res*stream.y_res,
                       5*(stream.x_res*stream.y_res)/4};

      cvt_rgb32_to_i420(buf, fb,
                        stream.x_res, stream.y_res,
                        pitches, offsets);
    }
  else if (stream.color_model == BGRA8888)
    {
      ls_scale32((uint32_t*) buf, stream.x_res, stream.y_res,
                 inst->in_in->framebuffer,
                 inst->in_in->xsize,
                 inst->in_in->ysize);
    }

  // and write  
  {
    uint8_t* start;
    size_t length;
  
    if ( stream.wrote_header )
      {
	start= &stream.yuv_buf[stream.stream_header_size];
	length= stream.yuv_buf.size()-stream.stream_header_size;
      }
    else
      {
	start= &stream.yuv_buf[0];
	length= stream.yuv_buf.size();
	stream.wrote_header=true;
      }

    // TODO select    
    size_t wlen = write(stream.fd,start,length);
    if (wlen == -1)
      throw std::runtime_error("could not write to stream");
    
    if (wlen != length)
      throw std::runtime_error("could not write full frame to stream");

    // TODO partial writes
  }
    } 
  catch (std::runtime_error&)
    {
      if (stream.fd != 0)
	{
	  close(stream.fd);
	}
    }

}

