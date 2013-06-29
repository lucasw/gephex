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

#include "frbinmodule.h"

#include <string>
#include <stdexcept>
#include <algorithm> 
#include <cctype> // tolower
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <memory>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#include <windows.h>
#endif

#if !defined(COMP_VC)
using std::tolower;
#endif

#include "videofiledriver.h"

#if defined(OS_WIN32)
#include "vfwdriver.h"
//#include "dshowdriver.h"
#endif

#if defined(WITH_AVIFILE)
#include "avifiledriver.h"
#endif

#if defined(WITH_MPEG3)
#include "mpeg3driver.h"
#endif

#if defined(WITH_SDL_IMAGE)
#include "sdlimagedriver.h"
#endif

#if defined(WITH_FFMPEG)
#include "ffmpegdriver.h"
#endif

#include "bmpdriver.h"

#include "framecache.h"
#include "driverfactory.h"

#if defined (FRBINMODULE_CACHE_SIZE)
#define CACHE_SIZE_IN_MB FRBINMODULE_CACHE_SIZE
#else
#define CACHE_SIZE_IN_MB 128
#endif

//---------------------------------------------------------------------

static logT s_log;

static FrameCache* s_cache = 0;
static DriverFactory* s_factory = 0;

static void fallback_setting(NumberType* pos, 
                             NumberType* len,
                             FrameBufferType* fr);

//---------------------------------------------------------------------

typedef std::map<std::string, VideoInfo> InfoMap;

//---------------------------------------------------------------------

typedef struct _MyInstance 
{
  VideoFileDriver* drv;
  VideoInfo  info;
  std::string* fileName;  
  bool flush;

  InfoMap* known_infos;
  bool damaged;
} MyInstance, *MyInstancePtr;

//---------------------------------------------------------------------

int init(logT log_function)
{
  s_log = log_function;
  char buffer[128];
  snprintf(buffer, sizeof(buffer),
           "setting up cache: %i mb",
           CACHE_SIZE_IN_MB);
  s_log(2, buffer);
  s_cache = new FrameCache(CACHE_SIZE_IN_MB);
  s_factory = new DriverFactory();

#if defined(WITH_FFMPEG)
  DriverConstructor<FFMpegDriver>* ffmpeg_ctor
    = new DriverConstructor<FFMpegDriver>();
  s_factory->register_driver(ffmpeg_ctor);
#endif

#if defined(OS_WIN32)
  DriverConstructor<VFWDriver>* vFW_ctor = new DriverConstructor<VFWDriver>();
  s_factory->register_driver(vFW_ctor);
  //  DriverConstructor<DSHOWDriver>* DSHOW_ctor = new DriverConstructor<DSHOWDriver>();
  //    s_factory->register_driver(DSHOW_ctor);
#endif

#if defined(WITH_AVIFILE)
  DriverConstructor<AviFileDriver>* aviFile_ctor 
    = new DriverConstructor<AviFileDriver>();
  s_factory->register_driver(aviFile_ctor);
#endif

#if defined(WITH_MPEG3)
  DriverConstructor<Mpeg3Driver>* mpeg3_ctor 
    = new DriverConstructor<Mpeg3Driver>();
  s_factory->register_driver(mpeg3_ctor);
#endif

#if defined(WITH_SDL_IMAGE)
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
  my->fileName = new std::string("");  
  my->flush = false;

  my->known_infos = new InfoMap();

  my->damaged = false;
  return my;
}

void destruct(MyInstance* my)
{
  delete my->known_infos;
  delete my->fileName;

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
    {
      std::string extension(file_name.substr(pos+1));

      typedef std::string::iterator I;
      std::transform<I,I,int(*)(int)>(extension.begin(),
				      extension.end(),
				      extension.begin(),
				      tolower);
      return extension;
    }
}


static std::list<std::string> path_to_dirs(const std::string& media_path)
{
  std::string::size_type pos = 0;
  std::string::size_type old_pos = 0;

  std::list<std::string> dir_list;
  //  std::cout << "path = " << media_path << "\n";
  while ( (pos = media_path.find_first_of(";", old_pos)) != std::string::npos )
    {
      if (old_pos < pos)
	{
	  std::string dir = media_path.substr(old_pos, pos - old_pos);
#if defined(OS_WIN32)
          dir += "\\";
#else
          dir += "/";
#endif
	  dir_list.push_back(dir);
          //          std::cout << "... " << dir << "\n";
	}
      old_pos = pos+1;
    }

  std::string dir = media_path.substr(old_pos);
#if defined(OS_WIN32)
  dir += "\\";
#else
  dir += "/";
#endif
  dir_list.push_back(dir);

  //  std::cout << "... " << dir << "\n";
  return dir_list;
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
static VideoFileDriver* load_file(const std::string& short_file_name,
                                  const DriverFactory& factory,
                                  VideoInfo& info)
{
  static const char* GEPHEX_MEDIA_PATH = "GEPHEX_MEDIA_PATH";
  // create search path list
  std::list<std::string> path;
  path.push_back("");  // local
#if defined(OS_WIN32)
  char media_path_buffer[10240];
  int ret = GetEnvironmentVariable(GEPHEX_MEDIA_PATH,
	     media_path_buffer,
		 sizeof(media_path_buffer));

  const char* media_path;
  if (ret == 0)
    media_path = 0;
  else
    media_path = media_path_buffer;
#else
  const char* media_path = getenv(GEPHEX_MEDIA_PATH);
#endif
  if (media_path == 0)
    {
      s_log(2, "GEPHEX_MEDIA_PATH not set!");
    }
  else
    {
      std::list<std::string> media_dirs = path_to_dirs(media_path);
      // from config file
      path.insert(path.end(), media_dirs.begin(), media_dirs.end());
    }
		 
  // search for the file
  std::list<std::string>::const_iterator it = path.begin();
  while(it!=path.end())
    {
      const std::string fullfilename (*it+short_file_name);
      std::ifstream teststream(fullfilename.c_str());
      //      std::cout <<"filename: "<< fullfilename << std::endl;
      if(teststream)
	break;
      ++it;
    }
  
  if (it == path.end())
    {
      // file not found
      throw std::runtime_error("file not found");
    }

  const std::string file_name( *it + short_file_name );
  
  std::string ext = get_extension(file_name);

  DriverFactory::CtorList ctors = factory.get_drivers(ext);

  if (ext != "*")
    {
      DriverFactory::CtorList stars = factory.get_drivers("*");
      ctors.insert(ctors.end(), stars.begin(), stars.end());
    }
          
  if (ctors.empty())
    throw std::invalid_argument(std::string("No driver for " 
                                            "extension '")
                                + ext + "'");

  VideoFileDriver* drv = 0;
  for (DriverFactory::CtorList::const_iterator cit = ctors.begin();
       cit != ctors.end(); ++cit)
    {
      drv = (*cit)->create();

      try {
        drv->load_file(file_name, info);
        break;
      }
      catch (std::invalid_argument& e)
        {
          delete drv;
          throw e;
        }
      catch (std::runtime_error& e)
        {
          delete drv;
          drv = 0;
          std::cout << e.what() << "\n";
        }
    }
    
  if (drv == 0)
    throw std::runtime_error("Could not load file");

  return drv;
}


void update(void* instance)
{
  const InstancePtr inst = (InstancePtr) instance;
  
  try
    {
      const unsigned int user_xsize = trim_int(inst->in_x_size->number,
					       0 , 1920);
      const unsigned int user_ysize = trim_int(inst->in_y_size->number,
					       0 , 1080);
      const bool use_cache = strcmp(inst->in_cache->text, "yes") == 0;
      const bool flush = trim_bool(inst->in_flush->number) != 0;
      const std::string newFileName = inst->in_fileName->text;  
      const unsigned int frame_number = trim_int(inst->in_frame->number,
						 0, INT_MAX);
      
      // user wants default size ?
      const bool default_size(user_xsize == 0 || user_ysize == 0);

      const MyInstancePtr my = inst->my;
      InfoMap& m_known_infos   = *my->known_infos;
      std::string& m_file_name = *my->fileName;
      
      if (flush != my->flush)
	{
	  my->flush = flush;
	  s_cache->flush();
	  m_known_infos.clear();
	}
      
      if (m_file_name != newFileName   ||
	  (!use_cache && my->drv == 0) ||
	  my->damaged)
	{
	  if (my->drv)
	    {
	      //printf("Closing driver\n");
	      if (my->drv->is_open())
		my->drv->close_file();
	      delete my->drv;
	      my->drv = 0;
	    }
	  
	  if (use_cache)
	    {  	  		  
	      InfoMap::const_iterator it = m_known_infos.find(newFileName);
	      if (it != m_known_infos.end())
		{
		  my->info = it->second;
		}
	      else
		{
		  my->drv = load_file(newFileName, *s_factory, my->info);
		  if (my->info.num_frames < 1)
		    {
		      my->damaged = true;
		      throw std::runtime_error("zero frames in file");
		    }
		  else
		    {
		      my->damaged = false;
		      m_known_infos.insert(std::make_pair(newFileName,
							  my->info));
		    }
		}
	    }  	  
	  else // don't use cache
	    {
	      my->drv = load_file(newFileName, *s_factory, my->info);

	      if (my->info.num_frames < 1)
		{
		  my->damaged = true;
		  throw std::runtime_error("zero frames in file");
		}
	      else
		my->damaged = false;
	    }	  
	  m_file_name = newFileName;
	}
      
      
  assert(m_file_name == newFileName);

  // determine frame number
  assert( my->info.num_frames > 0 );
  
  const unsigned int pos = frame_number % my->info.num_frames;

  const unsigned int xsize = default_size ? my->info.width : user_xsize;
  const unsigned int ysize = default_size ? my->info.height : user_ysize;

  assert( xsize > 0 );
  assert( ysize > 0 );
  

  // resize the output
  {
    FrameBufferAttributes attribs;
    attribs.xsize = xsize;
    attribs.ysize = ysize;  
    
    int result = framebuffer_changeAttributes(inst->out_result, &attribs);
    
    if (result != 1)
      throw std::runtime_error("Could not scale output!");
  }
  
  if( ! use_cache )
    {
      // decode the frame
      my->drv->decode_frame(pos, inst->out_result->framebuffer,
			    xsize, ysize);      
    }
    else
    {
      uint_32* frb = s_cache->lookup(m_file_name, pos, xsize, ysize);
	  
      if (frb == 0) //Cache miss
        {
	  // lacy open in cache mode
	  if (my->drv == 0)
	    {
	      my->drv = load_file(m_file_name, *s_factory, my->info);
	      m_known_infos.insert(std::make_pair(m_file_name, my->info));
	    }
	  
	  // fill cache with a new frame
          try
            {
	      frb = new uint_32[xsize*ysize];
              my->drv->decode_frame(pos, frb, xsize, ysize);
              s_cache->store(m_file_name, pos, xsize, ysize, frb);
            }          
          catch (...)
            {
              delete[] frb;
              frb = 0;
	      throw;
            }
        }
      // copy cached frame to output
      memcpy(inst->out_result->framebuffer, frb, xsize*ysize*4);
    }
   
  inst->out_position->number = (double) pos;
  inst->out_length->number   = (double) my->info.num_frames;
    }
  catch (std::exception& e)
    {
      // log error message
      s_log(0, e.what());

      // no video
      inst->out_position->number = 0.0;
      inst->out_length->number = 0.0; // is this a good error code?

      framebuffer_set_default(inst->out_result);
    }
}
