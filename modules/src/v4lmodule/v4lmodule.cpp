extern "C" {
#include "v4lmodule.h"
}

#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>
#include "v4l.h"

typedef struct _MyInstance 
{
  int xSize;
  int ySize;
  std::string deviceFile;
  bool initialized;
  V4LGrabber* grabber;

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  return 1;
}

void shutDown(void)
{

}

MyInstance* construct()
{
  MyInstance* my = new MyInstance;

  my->initialized=false;

  my->grabber=0;
  my->xSize=0;
  my->ySize=0;
  my->deviceFile="";

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  delete my->grabber;
  delete my;
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;


  std::string devicefile(inst->in_devicefile->text);
  if (my->initialized)
    {
      // check for new properties
      if (devicefile!=my->deviceFile||
	  inst->in_x_size->number!=my->xSize||
	  inst->in_y_size->number!=my->ySize)
	{
	  delete my->grabber;
	  delete[] inst->out_r->framebuffer; 
	  my->initialized = false;
	}
    }

  my->deviceFile=devicefile;
  my->xSize=inst->in_x_size->number;
  my->ySize=inst->in_y_size->number;

  if(!my->initialized)
    {
      try
	{	
	  std::cout << "v4lmodule: open("<<my->deviceFile<<"), with "
		    << my->xSize << ", " << my->ySize << std::endl;
	  my->grabber=new V4LGrabber(my->deviceFile);
	  my->grabber->setGrabProperties(my->xSize,my->ySize);
	  //my->grabber->setColorProperties(128,128,128,128);
	  //my->grabber->setVideoInput(int,int);
	  //my->grabber->grabNextImage();
	  //my->grabber->grabNextImage();

	  inst->out_r->xsize=my->xSize;
	  inst->out_r->ysize=my->ySize;

	  // todo
	  //delete inst->out_r->framebuffer;
	  inst->out_r->framebuffer= new uint_32[my->xSize*my->ySize];
	  
	  my->initialized=true;
	} 
      catch (std::runtime_error& e)
	{
	  std::cerr << e.what();
	  delete my->grabber;
	}
    }
  
  if (my->initialized)
    { 
      try
	{
	  my->grabber->grabNextImage();

	  int* raw_pic1;
	  my->grabber->getGrabbedImage(raw_pic1);
	  unsigned char* raw_pic=(unsigned char*)raw_pic1;

	  // convert raw data in the framebuffer
	  // webcam
	  unsigned char* y_ptr=raw_pic;
	  unsigned char* y_ptr2=raw_pic+my->xSize;
	  unsigned int y_size =my->xSize*my->ySize;

	  unsigned char* u_ptr=raw_pic+y_size;
	  unsigned int u_size =(my->xSize*my->ySize)/4;
	  
	  unsigned char* v_ptr=raw_pic+y_size+u_size;
	  unsigned int v_size =(my->xSize*my->ySize)/4;

	  uint_32* pixel_end=inst->out_r->framebuffer;
	  uint_32* pixel_ptr=pixel_end+my->xSize*my->ySize-1;
	  uint_32* pixel_ptr2=pixel_ptr-my->xSize-2;
	  
	  for (int y=0;y!=my->ySize;++(++y))
	    {
	      
	      for (int x=0;x!=my->xSize;++(++x))
		{

		  double v=*v_ptr;
		  double u=*u_ptr;

		  int r =(int)std::max(0.0,(1.370705*(v-128)));
		  int g =(int)std::max(0.0,(-(0.698001*(v-128))-(0.337633*(u-128))));
		  int b =(int) std::max(0.0,1.732446 *(u-128));		  

		  char pixel[4];

		  pixel[0]=(unsigned char)std::min(255,*y_ptr+r);
		  pixel[1]=(unsigned char)std::min(255,std::max(0,((int)*y_ptr)+g));
		  pixel[2]=(unsigned char)std::min(255,*y_ptr+b);
		  *pixel_ptr=*(uint_32*)pixel;
		  --pixel_ptr;
		  ++y_ptr;

		  pixel[0]=(unsigned char)std::min(255,*y_ptr+r);
		  pixel[1]=(unsigned char)std::min(255,std::max(0,((int)*y_ptr)+g));

		  pixel[2]=(unsigned char)std::min(255,*y_ptr+b);
		  *pixel_ptr=*(uint_32*)pixel;
		  --pixel_ptr;
		  ++y_ptr;

		  pixel[0]=(unsigned char)std::min(255,*y_ptr+r);
		  pixel[1]=(unsigned char)std::min(255,std::max(0,((int)*y_ptr)+g));

		  pixel[2]=(unsigned char)std::min(255,*y_ptr+b);
		  *pixel_ptr2=*(uint_32*)pixel;
		  --pixel_ptr2;
		  ++y_ptr2;

		  pixel[0]=(unsigned char)std::min(255,*y_ptr+r);
		  pixel[1]=(unsigned char)std::min(255,std::max(0,((int)*y_ptr)+g));

		  pixel[2]=(unsigned char)std::min(255,*y_ptr+b);
		  *pixel_ptr2=*(uint_32*)pixel;
		  --pixel_ptr2;
		  ++y_ptr2;

		  ++v_ptr;
		  ++u_ptr;		  
		}
	      pixel_ptr-=my->xSize;
	      pixel_ptr2-=my->xSize;
	      y_ptr+=my->xSize;
	      y_ptr2+=my->xSize;

	    }
	  
	}      
      catch (std::runtime_error& e)
	{
	  std::cerr << e.what();
	  my->initialized=false;
	  delete my->grabber;
	}
    }

  if (!my->initialized)
    {
      // generate dummy image
      inst->out_r->xsize=1;
      inst->out_r->ysize=1;
      //delete inst->out_r->framebuffer;
      inst->out_r->framebuffer= new uint_32[1];
    }
}


