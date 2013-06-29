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

#include "mpeg3driver.h"

#include <string>
#include <stdexcept>
#include "libmpeg3.h"
#include <iostream>

struct Mpeg3DriverImpl
{
  Mpeg3DriverImpl()
    :file(0),file_name(""),w(0),h(0),l(0),rows(0), num_rows(0),stream(0)
  {
  }

  ~Mpeg3DriverImpl()
  {
  }

  mpeg3_t* file;
  std::string file_name;
  int w;
  int h;
  int l;
  uint_8** rows;
  int num_rows;
  int stream;
};

Mpeg3Driver::Mpeg3Driver()
  : m_impl(new Mpeg3DriverImpl())
{
}

Mpeg3Driver::~Mpeg3Driver()
{
  if (m_impl->file != 0)
    {
      mpeg3_close(m_impl->file);
      m_impl->file = 0;
    }

  if (m_impl->rows != 0)
	  delete[] m_impl->rows;
}

std::list<std::string> Mpeg3Driver::supported_extensions()
{
	std::list<std::string> el;
	el.push_back("mpg");
	el.push_back("mpeg");
	return el;
}

void Mpeg3Driver::load_file(const std::string& file_name, VideoInfo& info)
{
  if (is_open())
    throw std::logic_error("file already loaded");

  m_impl->file_name=file_name;

  if(mpeg3_check_sig(const_cast<char*>(m_impl->file_name.c_str()))==1)
    {
      m_impl->file=mpeg3_open(const_cast<char*>(m_impl->file_name.c_str()));
	  
      try
        {
          if (!mpeg3_has_video(m_impl->file))
            { 
              throw std::runtime_error("sorry no video stream");
            }
          else
            { // we have video
              // todo mpeg3_total_vstreams
              m_impl->stream = 0;
		  
              m_impl->w = mpeg3_video_width(m_impl->file,m_impl->stream);
              m_impl->h = mpeg3_video_height(m_impl->file,m_impl->stream);
              m_impl->l = mpeg3_video_frames(m_impl->file,m_impl->stream);

              if (m_impl->l == 1)
                throw std::runtime_error("% seeking not implemented");

              info.width      = m_impl->w;
              info.height     = m_impl->h;
              info.num_frames = m_impl->l;		  
            }
        }
      catch(std::runtime_error& e)
        { // log and clean up
          //s_log(2,e.what());
          mpeg3_close(m_impl->file);
          m_impl->file=0;
        }
    }
}

void Mpeg3Driver::close_file()
{
  if (is_open())
    {
      mpeg3_close(m_impl->file);
      m_impl->file=0;
    }
}

bool Mpeg3Driver::is_open() const
{
  return m_impl->file != 0;
}

void Mpeg3Driver::decode_frame(unsigned int frame_number,
                               uint_32* framebuffer,
                               int width, int height)
{
  if (!is_open())
    throw std::logic_error("No file loaded");

  if (frame_number >= m_impl->l)
      throw std::range_error("frame_number out of range");

  // allocate new rows if needed
  if (m_impl->rows == 0 || m_impl->num_rows != height)
	{
	  if (m_impl->rows)
	    delete[] m_impl->rows;

	  m_impl->rows = new uint_8*[height];
	}

  // calc rows
  for (int i = 0; i != height; ++i)
    {
      m_impl->rows[i]=reinterpret_cast<uint_8*>(framebuffer+(i*width));
    }
  
  if (mpeg3_set_frame(m_impl->file,frame_number,m_impl->stream)==-1)
    throw std::range_error("could not seek to that position");
  
  // decode one frame
  int errorCode = mpeg3_read_frame(m_impl->file,m_impl->rows,
				   0,0,m_impl->w,m_impl->h, // input window
				   width,height, // output window
				   MPEG3_BGRA8888,
				   m_impl->stream);
  if (errorCode==-1)
    throw std::runtime_error("could not decode frame");
}

