#include "frbinmodule.h"

#include <string>
#include <stdexcept>
//#include <sstream>
#include <memory>
//#include <algorithm>
#include <iostream>
#include <map>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "videofiledriver.h"

#if defined(OS_POSIX)

#if defined(HAVE_AVIFILE)
#include "avifiledriver.h"
#endif
#if defined(HAVE_MPEG3)
#include "mpeg3driver.h"
#endif
#elif defined(OS_WIN32)
#include "vfwdriver.h"
//#include "dshowdriver.h"
#endif

#if defined(HAVE_SDL_IMAGE)
#include "sdlimagedriver.h"
#endif

#include "bmpdriver.h"

#include "framecache.h"
#include "driverfactory.h"

#define CACHE_SIZE_IN_MB 100

//---------------------------------------------------------------------

static logT s_log;

static FrameCache* s_cache = 0;
static DriverFactory* s_factory = 0;

static int scale(uint_32* result, const uint_32* data, int_32 width,
                 int_32 height, int_32 newWidth, int_32 newHeight);

//---------------------------------------------------------------------

typedef struct _MyInstance 
{
  VideoFileDriver* drv;
  VideoInfo   info;
  std::string fileName;
  bool loaded;
  int last_frame;
  int flush;
} MyInstance, *MyInstancePtr;

//---------------------------------------------------------------------

int init(logT log_function)
{
  s_log = log_function;
  s_cache = new FrameCache(CACHE_SIZE_IN_MB);
  s_factory = new DriverFactory();

#if defined(OS_POSIX)
#if defined(HAVE_MPEG3)
  DriverConstructor<Mpeg3Driver>* mpeg3_ctor 
    = new DriverConstructor<Mpeg3Driver>();
  s_factory->register_driver(mpeg3_ctor);
#endif
#if defined(HAVE_AVIFILE)
  DriverConstructor<AviFileDriver>* aviFile_ctor 
    = new DriverConstructor<AviFileDriver>();
  s_factory->register_driver(aviFile_ctor);

#endif
#elif defined(OS_WIN32)
  /*DriverConstructor<DSHOWDriver>* DSHOW_ctor = new DriverConstructor<DSHOWDriver>();
    s_factory->register_driver(DSHOW_ctor);*/
  DriverConstructor<VFWDriver>* vFW_ctor = new DriverConstructor<VFWDriver>();
  s_factory->register_driver(vFW_ctor);
#endif

#if defined (HAVE_SDL) && defined(HAVE_SDL_IMAGE)
  DriverConstructor<SDLImageDriver>* sdlimage_ctor 
    = new DriverConstructor<SDLImageDriver>();
  s_factory->register_driver(sdlimage_ctor);
#endif  
  DriverConstructor<BMPDriver>* bMP_ctor = new DriverConstructor<BMPDriver>();
  s_factory->register_driver(bMP_ctor);
  return 1;
}

void shutDown(void)
{
  delete s_factory;
  s_factory = 0;

  delete s_cache;
  s_cache = 0;
}

//---------------------------------------------------------------------

MyInstance* construct()
{
  MyInstance* my = new MyInstance;

  my->drv = 0;
  my->fileName = "";
  my->loaded   = false;
  my->last_frame = -1;
  my->flush = 0;

  return my;
}

void destruct(MyInstance* my)
{
  if (my->drv != 0)
    delete my->drv;

  delete my;
}

static std::string get_extension(const std::string& file_name)
{
  unsigned int pos = file_name.find_last_of(".");
  if (pos == std::string::npos)
    return "";
  else 
    return file_name.substr(pos+1);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  int xsize = trim_int(inst->in_x_size->number, 0 , 1024);
  int ysize = trim_int(inst->in_y_size->number, 0 , 1024);
  int flush = trim_int(inst->in_flush->number, 0, 1);
  bool use_cache = false;

  if (strcmp(inst->in_cache->text, "yes") == 0)
    use_cache = true;

  if (flush != my->flush)
    {
      my->flush = flush;
      s_cache->flush();
    }

  std::string newFileName=std::string(inst->in_fileName->text);
  
  //check is filename changed
  if (my->fileName!=newFileName)
    {
      try
        {
          std::string ext = get_extension(newFileName);
          my->drv = s_factory->get_driver(ext);
          
          if (my->drv == 0)
            throw std::invalid_argument(std::string("No driver for " 
                                                    "extension '")
                                        + ext + "'");

          my->drv->load_file(newFileName, my->info);          
          my->loaded = true;
        }
      catch (std::exception& e)
        {
          my->loaded = false;
          s_log(0, e.what());
        }
      my->fileName = newFileName;
    }

  if (!my->loaded)
    return;

  int pos; // frame nr to decode
  if(!trim_bool(inst->in_seek->number))
    {
      my->last_frame = my->last_frame+1;
      if (my->last_frame > my->info.num_frames - 1)
        my->last_frame = my->info.num_frames - 1;

      pos = my->last_frame;
    }
  else
    {
      my->last_frame = trim_int(inst->in_position->number*
                                (my->info.num_frames - 1.0),
                                0,
                                my->info.num_frames-1);
      pos = my->last_frame;
      
      //std::cout <<"pos: " << pos 
      //	<<" prevkey: "<<my->videoStream->GetPrevKeyFrame(pos) 
      //	<<" nextkey: "<<my->videoStream->GetNextKeyFrame(pos) 
      //	<<" total: " <<my->videoStream->GetLength()
      //	<< std::endl;
    }
  
  bool need_scale = false;
  if (xsize == 0 || ysize == 0)
    {
      xsize = my->info.width;
      ysize = my->info.height;
    }

  // resize output
  FrameBufferAttributes attribs;
  attribs.xsize = xsize;
  attribs.ysize = ysize;
  framebuffer_changeAttributes(inst->out_result, &attribs);

  if (xsize != my->info.width || ysize != my->info.height)
    need_scale = true;

  uint_32* infb = 0;
  uint_32* outfb = 0;
  if (use_cache)
    {
      infb = s_cache->lookup(my->fileName, pos, xsize, ysize);
      if (infb == 0)
        {
          outfb = new uint_32[xsize*ysize];
        }
      else
        {
          need_scale = false;
          outfb = infb;
        }
    }
  else
    outfb = inst->out_result->framebuffer;
    
  if (infb == 0) //Cache miss
    {
      //std::cout << " ...miss\n";
      uint_32* temp;
      if (need_scale)
        temp = new uint_32[my->info.width*my->info.height];
      else
        temp = outfb;
	  
      try
        {          
          my->drv->decode_frame(pos, temp);
        }          
      catch (std::exception& e)
        {
          //delete[] temp;          
          s_log(0, e.what());
		  
          // set error dummy
          FrameBufferAttributes attribs;
          attribs.xsize=1;
          attribs.ysize=1;
          framebuffer_changeAttributes(inst->out_result,&attribs);
          // set black background
          *(inst->out_result->data)=0x00000000;
          inst->out_position->number=0.0;
          return;
        }
		  
      if ( need_scale )
        {		  
          assert(temp != outfb);
          scale(outfb, temp, my->info.width, my->info.height, xsize, ysize);
          delete[] temp;
        }
	  
      if (use_cache)
        {
          s_cache->store(my->fileName, pos, xsize, ysize, outfb);
        }
    }

  if (use_cache)
    {
      memcpy(inst->out_result->framebuffer, outfb, xsize*ysize*4);
    }
	  
  inst->out_position->number = (double)pos / (double)my->info.num_frames;

}

//---------------------------------------------------------------------

/**
* Scales a bitmap to a new resolution.
*/
static int scale(uint_32* result, const uint_32* data, int_32 width,
                 int_32 height, int_32 newWidth, int_32 newHeight)
{	
  int_32 x,y;
  double alpha = (double) width / (double) newWidth;
  double beta = (double) height / (double) newHeight;
  uint_32 A = (int_32) (alpha* (1<<16));
  uint_32 B = (int_32) (beta* (1<<16));

  if (newWidth == width && newHeight == height)
    {
      memcpy(result,data,width*height*4);
    }
  else
    {
      int_32 bb = 0;
      for (y = 0; y < newHeight; ++y)
        {			
          int_32 aa = 0;			
          const uint_32* offset_ = data + (int) ((bb >> 16) * width);
          for (x = 0; x < newWidth; ++x)
            {
              *result = offset_[aa >> 16];
              aa += A;
              ++result;
            }
          bb += B;
        }
    }
  return 1;
}

//---------------------------------------------------------------------
