#include "v4lmodule.h"

#include <stdexcept>
#include <string>
#include <stdint.h>
#include <algorithm>
#include <map>
#include <sstream>
#include <cassert>
#include <linux/videodev.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>

#include "videodevice.h"

// debug
#include <iostream>

static std::map<std::string, VideoDevice*> videoDevices;
static logT s_log;

typedef struct _MyInstance
{
  int videoDeviceDescriptor;
} MyInstance, *MyInstancePtr;

int init(logT log_function)
{ 
  s_log = log_function;
  return 1;
}

void shutDown(void)
{}

MyInstance* construct()
{
    MyInstance* my = new MyInstance;
    return my;
}

void destruct(MyInstance* my)
{
  // todo dec some kind of refcount for the last open videodev
  delete my;
}

void yuv411p_2_bgra(uint8_t* from[3], int xSize, int ySize, uint8_t* to)
{
  assert(xSize%2==0);
  assert(ySize%2==0);
  assert(ySize>=0);
  assert(xSize>=0);

  const int offset_blue = 0;
  const int offset_green = 1;
  const int offset_red = 2;
  const int offset_alpha = 3;

  uint8_t* y[4];
  y[0]=from[0];
  y[1]=y[0]+1;
  y[2]=y[0]+xSize;
  y[3]=y[2]+1;
  uint8_t* u=from[1];
  uint8_t* v=from[2];

  uint8_t* r[4];
  r[0]=to+offset_red;
  r[1]=r[0]+4;
  r[2]=r[0]+xSize*4;
  r[3]=r[2]+4;
  uint8_t* g[4];
  g[0]=to+offset_green;
  g[1]=g[0]+4;
  g[2]=g[0]+xSize*4;
  g[3]=g[2]+4;
  uint8_t* b[4];
  b[0]=to+offset_blue;
  b[1]=b[0]+4;
  b[2]=b[0]+xSize*4;
  b[3]=b[2]+4;
  uint8_t* a[4];
  a[0]=to+offset_alpha;
  a[1]=a[0]+4;
  a[2]=a[0]+xSize+4;
  a[3]=a[2]+4;

  for (int line=0;line!=ySize/2;++line)
    {
      for (int pixel=0; pixel!=xSize/2; ++pixel)
	{

	  int rv = static_cast<int>( 1.4075 * (*v - 128));
	  int gv = static_cast<int>(-0.7169 * (*v - 128));
	  int gu = static_cast<int>(-0.3455 * (*u - 128));
	  int bu = static_cast<int>( 1.7790 * (*u - 128));
	  
	  for (int i=0;i!=4;++i)
	  {	    
	    *r[i]=std::max(0,std::min(255,*y[i]+rv));
	    *g[i]=std::max(0,std::min(255,*y[i]+gv+gu));
	    *b[i]=std::max(0,std::min(255,*y[i]+bu));
	    *a[i]=0;
	  }
	  
	  // increment pointers
	  ++u;
	  ++v;
	  for (int i=0;i!=4;++i)
	    {
	      y[i]+=2;
	      r[i]+=8;
	      g[i]+=8;
	      b[i]+=8;	  
	      a[i]+=8;
	    }
	}

      // increment pointers
      for (int i=0;i!=4;++i)
	{
	  y[i]+=xSize;
	  r[i]+=xSize*4;
	  g[i]+=xSize*4;
	  b[i]+=xSize*4;
	  a[i]+=xSize*4;
	}
	}
}

void update(void* instance)
{
  InstancePtr inst = static_cast<InstancePtr>(instance);
  MyInstancePtr my = inst->my;

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
	      // could not open videodevice
	      s_log(2,e.what());
	      
	      // mark it als unvalid
	      videoDevices[deviceFileName]=0;
	      throw;
	    } 
	}
      
      // now we have a open videodevice
      // its time to grab a frame
      VideoDevice::Frame frame;
      frame.xSize=trim_int(inst->in_x_size->number,0,FRAMEBUFFER_X_MAX);
      frame.ySize=trim_int(inst->in_y_size->number,0,FRAMEBUFFER_Y_MAX);

      try
	{
	  videoDev->grabImage(frame);
	}
      catch(std::runtime_error& e)
	{
	  // could not open videodevice
	  s_log(2,e.what());
	  
	  throw;
	} 

      //std::ostringstream msg;
      //msg << "size changed to: " << frame.xSize << "x" << frame.ySize;
      //s_log(2,msg.str().c_str());
      
      // change framebuffer size
      FrameBufferAttributes attribs;
      attribs.xsize=frame.xSize;
      attribs.ysize=frame.ySize;
      framebuffer_changeAttributes(inst->out_r,&attribs);

      assert(frame.xSize%2==0);
      assert(frame.ySize%2==0);

      // convert the image from yuv411p to bgra
      int ySize=frame.ySize;
      int xSize=frame.xSize;

      // todo sth is strange with the start positions
      uint8_t* from[3]; // pointers to the y,u and v planes
      from[0]=reinterpret_cast<uint_8*>(frame.frameptr);
      from[1]=from[0]+xSize*ySize;
      from[2]=from[0]+5*(xSize*ySize/4);

      yuv411p_2_bgra(from,xSize,ySize,(uint8_t*)inst->out_r->framebuffer);
    }
  catch (std::runtime_error& e)
    {
      // could not grab any image
      // return a dummy 1x1 image as fallback
      FrameBufferAttributes attribs;
      attribs.xsize=1;
      attribs.ysize=1;
      framebuffer_changeAttributes(inst->out_r,&attribs);
      *inst->out_r->framebuffer=0x00000000;
    }
}

