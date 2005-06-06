/* This source file is a part of the GePhex Project.

 Copyright (C) 2004

 Michael Mandl <mandlm@gephex.org>
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

#include "ffmpegoutmodule.h"
#include "ffmpegwriter.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "basic_types.h"

static logT s_log;

struct _MyInstance
{
  _MyInstance()
  {
    scaledFb=framebuffer_newInstance();
    ffmpegWriter = 0;
  }

  ~_MyInstance()
  {
    delete ffmpegWriter;    
    framebuffer_deleteInstance(scaledFb);
  }

  std::string filename;
  std::string encoding;

  FrameBufferType* scaledFb;
  FFMpegWriter *ffmpegWriter;
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
  return new MyInstance;
}

void destruct(MyInstance* my)
{
  delete my;
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstance& my = *inst->my;

  const size_t xsize_pre = trim_int(inst->in_xsize->number, 1, 1400);
  const size_t ysize_pre = trim_int(inst->in_ysize->number, 1, 1080);
  const std::string filename(inst->in_filename->text);
  const std::string encoding(inst->in_encoding->text);

  // change size to valid one
  const size_t xsize = xsize_pre - xsize_pre % 4;
  const size_t ysize = ysize_pre - ysize_pre % 4;

  // yuv4mpeg2 spec or ffpmeg
  assert(xsize%4==0);
  assert(ysize%4==0);
  
  if (filename == "null")
    {
      delete my.ffmpegWriter;
      my.ffmpegWriter = 0;
      return;
    }

  try
    {
      if (my.ffmpegWriter == 0)
	my.ffmpegWriter=new FFMpegWriter(filename,xsize,ysize,encoding);
      
      assert(my.ffmpegWriter != 0);
      
      if (my.ffmpegWriter->getFilename() != filename ||
	  my.ffmpegWriter->getXres() != xsize ||
	  my.ffmpegWriter->getYres() != ysize ||
	  my.ffmpegWriter->getEncoding() != encoding)
	{
	  delete my.ffmpegWriter;
	  my.ffmpegWriter=new FFMpegWriter(filename,xsize,ysize,encoding);
	}
      
      assert(my.ffmpegWriter != 0);
    }
  catch(std::runtime_error& e)
    {
      my.ffmpegWriter=0;
      s_log( 0, e.what() );
    }

  if ( my.ffmpegWriter != 0 )
    {
      // the framebuffer
      uint32_t* fb;

      if (inst->in_in->xsize != my.ffmpegWriter->getXres() ||
	  inst->in_in->ysize != my.ffmpegWriter->getYres())
	{
	  FrameBufferAttributes  in_attr;
	  framebuffer_getAttributes(inst->in_in, &in_attr);
	  in_attr.xsize=my.ffmpegWriter->getXres();
	  in_attr.ysize=my.ffmpegWriter->getYres();
	  framebuffer_convertType(my.scaledFb, inst->in_in , &in_attr);
	  
	  // use the scaled one
	  fb=my.scaledFb->framebuffer;
	}
      else
	{
	  // use the original
	  fb=inst->in_in->framebuffer;
	}

      try
	{
	  my.ffmpegWriter->writeFrame(fb);
	}
      catch(std::runtime_error& e)
	{
	  s_log(0,e.what());
	}
    }
}

