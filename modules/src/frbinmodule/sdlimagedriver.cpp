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

#include "sdlimagedriver.h"

extern "C"
{	
#include "SDL.h"
#include "SDL_image.h"
}

#include <sstream>
#include <string>
#include <stdexcept>
//#include <memory>
//#include <cstdlib>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "libscale.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0x0000ff00
#define gmask 0x00ff0000
#define bmask 0xff000000
#define amask 0x000000ff
#else
#define rmask 0x00ff0000
#define gmask 0x0000ff00
#define bmask 0x000000ff
#define amask 0xff000000
#endif

//----------------------------------------------------------------------

class SDLImageDriverImpl
{
public:
  SDLImageDriverImpl()    
	  : m_image(0), m_width(0), m_height(0)
  {
  }

  ~SDLImageDriverImpl()
  {
    close();
  }
  
  void load(const std::string& filename, VideoInfo& info)
  {
    SDL_Surface* tmp_image = IMG_Load(filename.c_str());

    if ( tmp_image == NULL )
      {
        std::ostringstream os;
        os << "Couldn't load '" << filename << "' ("
           << SDL_GetError() << ")";
        throw std::runtime_error(os.str().c_str());
    }

    info.height = tmp_image->h;
    info.width  = tmp_image->w;
    info.num_frames = 1;

    m_image = SDL_CreateRGBSurface(SDL_SWSURFACE, tmp_image->w, tmp_image->h, 
				   32,rmask, gmask, bmask, amask);
    if(m_image == NULL)
      {
	SDL_FreeSurface(tmp_image);
	std::ostringstream os;
	os << "CreateRGBSurface failed: " <<  SDL_GetError();
	throw std::runtime_error(os.str().c_str());
      }

    SDL_Rect all;
    all.x=0;
    all.y=0;
    all.w= tmp_image->w;
    all.h= tmp_image->h;
     m_width=tmp_image->w;
     m_height=tmp_image->h;
    SDL_BlitSurface(tmp_image, &all, m_image, &all);
    SDL_FreeSurface(tmp_image);
  }

  void close()
  {
    SDL_FreeSurface(m_image);
    m_image=0;
  }

  void grab_frame(uint_32* frb, unsigned int frame,
		          int width, int height)
  {	  	  
	if (m_image == 0)
		throw std::runtime_error("No image loaded");

	if (frame != 0)
	   throw std::range_error("No such frame in image (only 0 is valid)");

        ls_scale32(frb, width, height,
                   (uint_32*) m_image->pixels,
                   m_width, m_height);
  }

  bool is_open() const
  {
	  return m_image != 0;
  }

private:
  SDL_Surface* m_image;
  int_32 m_width;
  int_32 m_height;
  
};

//----------------------------------------------------------------------

SDLImageDriver::SDLImageDriver()
	: m_impl(new SDLImageDriverImpl())
{
}

SDLImageDriver::~SDLImageDriver()
{
}

std::list<std::string> SDLImageDriver::supported_extensions()
{
	std::list<std::string> el;
	el.push_back("bmp");
	el.push_back("gif");
	el.push_back("jpg");
	el.push_back("jpeg");
	el.push_back("lbm");
	el.push_back("pcx");
	el.push_back("png");
	el.push_back("pnm");
	el.push_back("tga");
	el.push_back("tif");
	el.push_back("xcf");
	el.push_back("xpm");
	el.push_back("xbm");
	return el;
}

void SDLImageDriver::load_file(const std::string& file_name, VideoInfo& info)
{
	if (m_impl->is_open())
          throw std::logic_error("Driver already open");

	m_impl->load(file_name, info);
}

void SDLImageDriver::close_file()
{
  if (m_impl->is_open())
    m_impl->close();
}
  
void SDLImageDriver::decode_frame(unsigned int frame_number,
                                  uint_32* framebuffer,
                                  int width, int height)
{
	if (!m_impl->is_open())
          throw std::logic_error("Driver not open");

	m_impl->grab_frame(framebuffer, frame_number, width, height);
}

bool SDLImageDriver::is_open() const
{
  return m_impl->is_open();
}
 
