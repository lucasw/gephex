#include "v4lmodule.h"

#include <stdexcept>
#include <string>
#include <stdint.h>
#include <algorithm>
#include <map>
#include <sstream>

#include "videodevice.h"
#include "colorconv.h"

// debug
#include <cassert>
#include <iostream>

static std::map<std::string, VideoDevice*> videoDevices;
static logT s_log;

typedef struct _MyInstance
{
  int videoDeviceDescriptor;
  int blubb;
} MyInstance, *MyInstancePtr;

int init(logT log_function)
{ 
  s_log = log_function;
  init_tabs();
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
    MyInstance* my = new MyInstance;
    my->blubb = 0;
    return my;
}

void destruct(MyInstance* my)
{
  // todo dec some kind of refcount for the last open videodev
  delete my;
}


void update(void* instance)
{
  InstancePtr inst = static_cast<InstancePtr>(instance);
  MyInstancePtr my = inst->my;

  if (my->blubb == 0)
    my->blubb = 2;
  else {
    my->blubb--;
    return;
  }



  try
    {
      // get the videodevice object by name
      std::string deviceFileName(inst->in_devicefile->text);
      std::map<std::string, VideoDevice*>::iterator it =
	videoDevices.find(deviceFileName);
      VideoDevice* videoDev;
      if (it!=videoDevices.end())
	{
	  // the video device is already known
	  // check if it is a valid device
	  if (it->second==0)
	    {
	      // dont retry on every update
	      throw std::runtime_error("no valid device");
	    }
	  videoDev=it->second;
	}
      else
	{
	  // there is no open videodevice 
	  // try to open it, if it fails a exception is thrown
	  try
	    {
	      videoDev = new VideoDevice(deviceFileName,s_log);
	      // add it to the map
	      videoDevices[deviceFileName]=videoDev;
	    }
	  catch(std::runtime_error& e)
	    {
	      // mark it als unvalid
	      videoDevices[deviceFileName]=0;
	      throw;
	    } 
	}
      
      // now we have an open videodevice

      // set a/d converter params
      videoDev->setProperties(
			      trim_int(inst->in_brightness->number*65535.0,
				       0,65535),
			      trim_int(inst->in_hue->number*65535.0,
				       0,65535),
			      trim_int(inst->in_colour->number*65535.0,
				       0,65535),
			      trim_int(inst->in_contrast->number*65535.0,
				       0,65535),
			      trim_int(inst->in_whiteness->number*65535.0,
				       0,65535)
			      );

      // its time to grab a frame
      VideoDevice::Frame frame;
      frame.xSize=trim_int(inst->in_x_size->number,0,FRAMEBUFFER_X_MAX);
      frame.ySize=trim_int(inst->in_y_size->number,0,FRAMEBUFFER_Y_MAX);
      videoDev->grabImage(frame);
    
      // change framebuffer size
      FrameBufferAttributes attribs;
      attribs.xsize=frame.xSize;
      attribs.ysize=frame.ySize;
      framebuffer_changeAttributes(inst->out_r,&attribs);


      switch (frame.type)
	{
	case VIDEO_PALETTE_RGB32:
	  rgb32_2_bgra(reinterpret_cast<uint_8*>(inst->out_r->framebuffer),
		       reinterpret_cast<uint_8*>(frame.frameptr),
		       frame.xSize,frame.ySize);
	  break;
	case VIDEO_PALETTE_YUV420P: 
	  // convert the image from yuv411p to bgra
	  yuv411p_2_bgra(reinterpret_cast<uint_8*>(inst->out_r->framebuffer),
			 reinterpret_cast<uint_8*>(frame.frameptr),
			 frame.xSize,frame.ySize);
	  break;
	default:
	   throw std::runtime_error("unsupported pixelformat");
	}
    }
  catch (std::runtime_error& e)
    {
      s_log(2,e.what());

      // in case of an error return a dummy image of size 1x1
      FrameBufferAttributes attribs;
      attribs.xsize=1;
      attribs.ysize=1;
      framebuffer_changeAttributes(inst->out_r,&attribs);
      
      // set it to black
      *inst->out_r->framebuffer=0x00000000;
    }
}

