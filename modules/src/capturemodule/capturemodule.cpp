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

#include "capturemodule.h"

#include <stdexcept>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "capturedriver.h"

#if defined(OS_POSIX)
#include "v4lcapturedriver.h"
#include "v4l2capturedriver.h"
#elif defined(OS_WIN32)
#include "dshowcapturedriver.h"
#endif

//---------------------------------------------------------------------

CaptureDriver* create_driver()
{
#if defined(OS_POSIX)
  return new V4L2CaptureDriver();
#elif defined(OS_WIN32)
  return new DSHOWCaptureDriver();
#endif
}


struct device_descriptor
{
  device_descriptor()
    : drv(0), dev_num(-1), ref_count(0)
  {}
  ~device_descriptor() { delete drv; }
	
  void decrease_refcount()
  {
    assert(ref_count >= 0);
    if (ref_count <= 0)
      return;
		
    --ref_count;
    if (ref_count == 0)
      {
        assert(drv);
        if (drv->is_open())
          drv->close();
			
        delete drv;
        drv = 0;
      }
  }
	
  void increase_refcount()
  {
    assert(ref_count >= 0);
		
    if (ref_count == 0)
      {
        try
          {
#if defined(OS_POSIX)
            drv = new V4L2CaptureDriver();
            try
              {
                drv->open(dev_num);
              }
            catch (std::exception& e)
              {
                delete drv;
                drv = new V4LCaptureDriver();
              }
#elif defined(OS_WIN32)
            drv = new DSHOWCaptureDriver();
#endif
            if (!drv->is_open())
              drv->open(dev_num);
          }
        catch (...)
          {
            delete drv;
            drv = 0;
            throw;
          }
      }
    assert(drv);
    ++ref_count;
  }
	

  CaptureDriver* drv;
  int dev_num;
  int ref_count;
};

//---------------------------------------------------------------------

static logT s_log;


#define MAX_DEVICES 16
static device_descriptor s_devices[MAX_DEVICES];

//---------------------------------------------------------------------

typedef struct _MyInstance 
{ 
  int device_num;
  CaptureDriver* drv;
} MyInstance, *MyInstancePtr;

//---------------------------------------------------------------------

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

//---------------------------------------------------------------------


static CaptureDriver* open_device(int device_num)
{
  s_devices[device_num].dev_num = device_num;
  s_devices[device_num].increase_refcount();

  CaptureDriver* drv = s_devices[device_num].drv;

  return drv;
}

static void close_device(int device_num)
{
  s_devices[device_num].decrease_refcount();
}

MyInstance* construct()
{
  MyInstance* my = new MyInstance;

  my->device_num = -1;
  my->drv        = 0;

  return my;
}

void destruct(MyInstance* my)
{
  if (my->device_num != -1)
    {
      close_device(my->device_num);
    }

  delete my;
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  int xsize = trim_int(inst->in_x_size->number, 0 , 1024);
  int ysize = trim_int(inst->in_y_size->number, 0 , 1024);

  int device_num = trim_int(inst->in_device->number, 0, MAX_DEVICES-1);
    
  //check if device changed
  if (my->device_num != device_num || my->drv == 0 ||
      !my->drv->is_open())
    {
      try
        {
          if (my->device_num != -1)
            {
              my->drv = 0;
              close_device(my->device_num);			  
            }
          
          my->drv = open_device(device_num);
          my->device_num = device_num;
        }
      catch (std::exception& e)
        {
          my->device_num = -1;
          s_log(0, e.what());
        }
    }
  
  try
    {
      
  if (my->drv == 0 || !my->drv->is_open())
    throw std::runtime_error("no usable capture device");

  bool new_frame = true;
  int capture_width;
  int capture_height;
  my->drv->status(capture_width, capture_height, new_frame);
  if (xsize == 0 || ysize == 0)
    {
      // set xsize and ysize to the format of the capture device
      xsize = capture_width;
      ysize = capture_height;
    }   

  if (new_frame == false)
    return;

  // resize output
  FrameBufferAttributes attribs;
  attribs.xsize = xsize;
  attribs.ysize = ysize;
  framebuffer_changeAttributes(inst->out_result, &attribs);

      my->drv->decode_frame(inst->out_result->framebuffer,
                            xsize, ysize);
    }
  catch (std::exception& e)
    {	          
      s_log(0, e.what());
	  
      // set error dummy
      FrameBufferAttributes attribs;
      attribs.xsize=1;
      attribs.ysize=1;
      framebuffer_changeAttributes(inst->out_result,&attribs);
      // set black background
      *(inst->out_result->data)=0x00000000;         
      return;
    }
}

//---------------------------------------------------------------------
