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

//---------------------------------------------------------------------

typedef struct _MyInstance 
{
  VideoFileDriver* drv;
  VideoInfo   info;
  std::string fileName;
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
  //  DriverConstructor<Mpeg3Driver>* mpeg3_ctor 
  //  = new DriverConstructor<Mpeg3Driver>();
  //s_factory->register_driver(mpeg3_ctor);
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

/**
 * Probes for a driver for this file and opens it if possible.
 *
 * \returns a IVideoFileDriver object that has already loaded
 *    the file
 *
 * \throws std::invalid_argument if file_name is not a valid file
 * \throws std::runtime_error if no known driver can load the file
 */
static VideoFileDriver* load_file(const std::string& file_name,
                                  const DriverFactory& factory,
                                  VideoInfo& info)
{
  std::string ext = get_extension(file_name);

  DriverFactory::CtorList ctors = s_factory->get_drivers(ext);

  if (ext != "*")
    {
      DriverFactory::CtorList stars = s_factory->get_drivers("*");
      ctors.insert(ctors.end(), stars.begin(), stars.end());
    }
          
  if (ctors.empty())
    throw std::invalid_argument(std::string("No driver for " 
                                            "extension '")
                                + ext + "'");

  VideoFileDriver* drv = 0;
  for (DriverFactory::CtorList::const_iterator it = ctors.begin();
       it != ctors.end(); ++it)
    {
      drv = (*it)->create();

      try {
        drv->load_file(file_name, info);
        break;
      }
      catch (std::invalid_argument& e)
        {
          delete drv;
          throw e;
        }
      catch (std::runtime_error&)
        {
          delete drv;
          drv = 0;
        }
      catch (...)
        {
          delete drv;
          drv = 0;
        }
    }
    
  if (drv == 0)
    throw std::runtime_error("Could not load file");

  return drv;
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

  std::string newFileName = std::string(inst->in_fileName->text);
  
  //check is filename changed
  if (my->fileName != newFileName || my->drv == 0)
    {
      if (my->drv)
        {
          if (my->drv->is_open())
            my->drv->close_file();
          delete my->drv;
          my->drv = 0;
        }
      try
        {
          my->drv = load_file(newFileName, *s_factory, my->info);
        }
      catch (std::exception& e)
        {
          s_log(0, e.what());
        }
      my->fileName = newFileName;
    }

  if (my->drv == 0 || !my->drv->is_open())
    return;

  int pos; // frame nr to decode
  if(!trim_bool(inst->in_seek->number))
    {
      my->last_frame = my->last_frame+1;
      if (my->last_frame > my->info.num_frames - 1)
	{
	  //my->last_frame = my->info.num_frames - 1;
	  my->last_frame = 0;
	}

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
    
  if (xsize == 0 || ysize == 0)
    {
      xsize = my->info.width;
      ysize = my->info.height;
    }

  // resize output
  FrameBufferAttributes attribs;
  attribs.xsize = xsize;
  attribs.ysize = ysize;
  int result = framebuffer_changeAttributes(inst->out_result, &attribs);

  if (result != 1)
    {
      s_log(0, "Could not scale output!");
      return;
    }

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
          outfb = infb;
        }
    }
  else
    outfb = inst->out_result->framebuffer;
    
  if (infb == 0) //Cache miss
    {      	  
      try
        {          
          my->drv->decode_frame(pos, outfb, xsize, ysize);
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

