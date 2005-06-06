#include "pongmodule.h"

#include <cmath>

static logT s_log;

typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

} MyInstance, *MyInstancePtr;

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
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  if (my == 0)
  {
          s_log(0, "Could not allocate memory for MyInstance struct\n");
          return 0;
  }

  // Add your initialization here

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  // Add your effect here!
  // resize output to 160*120
  FrameBufferAttributes attribs;

  framebuffer_getAttributes(inst->out_screen, &attribs);
  attribs.xsize = 160;
  attribs.ysize = 120;
  framebuffer_changeAttributes(inst->out_screen, &attribs);
  
  uint_32* fb = inst->out_screen->framebuffer;

  // default no sound
  inst->out_status->number=0;
  
  // create black background
  for (uint_32* pixel=fb;pixel!=fb+(attribs.xsize*attribs.ysize);++pixel)
    {
      *pixel=0;
    }

  unsigned int i;

  // two lines
  for (i = 10; i!= 151; ++i)
    {
      *(fb + 10*160+i )= 0xFFFFFFFF;
      *(fb + 110*160+i )= 0xFFFFFFFF;
    }

  // paint the players
  // p1
  int pos1= static_cast<int>(10 + trim_double(inst->in_p1->number, 0, 1) * 90);
  int pos2= static_cast<int>(10 + trim_double(inst->in_p2->number, 0, 1) * 90);
  for (i = 0; i!= 10; ++i)
    {
      *(fb + (10+(pos1+i)*160))= 0xFFFFFFFF;
      *(fb + (150+(pos2+i)*160))= 0xFFFFFFFF;
    }
  


  // calc new ball pos
  if (!trim_bool(inst->in_start->number))
    {
      inst->out_ball_x->number= 0.5;
      inst->out_ball_y->number= 0.5;
      inst->out_speed_x->number=0.01;
      inst->out_speed_y->number=0.02;
    }
  else
    {
      int ball_x= (int)(trim_double(inst->in_ball_x->number, 0, 1)*159);
      int ball_y= (int)(trim_double(inst->in_ball_y->number, 0, 1)*119);
      
      if (ball_y<=12 || ball_y>=109)
	inst->out_speed_y->number=-inst->in_speed_y->number;

      if (ball_x<12 && (inst->out_speed_x->number<0) && (ball_y>=pos1 && ball_y<=(pos1+10)))
	{
	  inst->out_speed_x->number=-inst->in_speed_x->number;
	  inst->out_status->number=1;
	}
	  
      if(ball_x>148 && (inst->out_speed_x->number>0) && (ball_y>=pos2 && ball_y<=(pos2+10)))
      {
	inst->out_speed_x->number=-inst->in_speed_x->number;
	inst->out_status->number=2;
      }
      
      inst->out_ball_x->number=  trim_double(inst->out_ball_x->number + 
				    inst->out_speed_x->number,0,1);
      
      inst->out_ball_y->number=  trim_double(inst->out_ball_y->number + 
				    inst->out_speed_y->number,0,1);
      
    }

  // paint the ball
  int ball_x= (int)(trim_double(inst->in_ball_x->number, 0, 1)*159);
  int ball_y= (int)(trim_double(inst->in_ball_y->number, 0, 1)*119);
  
  *(fb + (ball_x+ball_y*160))= 0xFFFFFFFF;
  *(fb + (ball_x+1+(ball_y)*160))= 0xFFFFFFFF;
  *(fb + (ball_x+(ball_y+1)*160))= 0xFFFFFFFF;
  *(fb + (ball_x+1+(ball_y+1)*160))= 0xFFFFFFFF;

  // calc new ball pos
  if (ball_x < 3 || ball_x > 155)
    {
      inst->out_ball_y->number= 0.5;
      inst->out_ball_x->number= 0.5;
      inst->out_speed_x->number=0.01;
      inst->out_speed_y->number=0.02;
    }

}

