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

#include "avifiledriver.h"

#include <string>
#include <stdexcept>
#include <sstream>
#include <memory>
#include <algorithm>
#include <iostream>

#include "avifile.h"
#include "libscale.h"
//----------------------------------------------------------------------

static uint32_t bgra2rgba (uint32_t in)
{
  uint32_t out;
  uint8_t* in_b=reinterpret_cast<uint8_t*>(&in);
  uint8_t* out_b=reinterpret_cast<uint8_t*>(&out);
  out_b[0]=in_b[2];
  out_b[1]=in_b[1];
  out_b[2]=in_b[0];
  out_b[3]=0;
  return out;
}

struct bgr_t
{
  uint8_t bgr[3];
};

static uint32_t bgr2rgba (bgr_t in)
{
  uint32_t out;
  uint8_t* in_b=reinterpret_cast<uint8_t*>(&in);
  uint8_t* out_b=reinterpret_cast<uint8_t*>(&out);
  out_b[0]=in_b[2];
  out_b[1]=in_b[1];
  out_b[2]=in_b[0];
  out_b[3]=0;
  return out;
}

//----------------------------------------------------------------------

struct AviFileDriverImpl
{
  AviFileDriverImpl()
    : videoStream(0), videoFile(0), file_name(""), w(0), h(0), nf(0), im(0) {}

  ~AviFileDriverImpl()
  {
    close();
  }

  void close()
  {
    if ( videoStream != 0 )
      {
	videoStream->StopStreaming();
	// TODO delete videoStream;
	videoStream = 0;
      }

    if ( videoFile !=0 )
      {
	delete videoFile;
	videoFile = 0;
      }

    if (im != 0)
      {
	//im->Release();
        delete im;
        im = 0;
      }
      
  }

  bool is_open() const
  {
    return videoFile != 0;
  }


  avm::IReadStream* videoStream;
  avm::IReadFile* videoFile;
  std::string file_name;
  int w;
  int h;
  unsigned int nf;
  avm::CImage* im;
};

AviFileDriver::AviFileDriver()
  : m_impl(new AviFileDriverImpl())
{
}

AviFileDriver::~AviFileDriver()
{
}

std::list<std::string> AviFileDriver::supported_extensions()
{
	std::list<std::string> el;
	el.push_back("avi");
	el.push_back("divx");
	el.push_back("mpg");
	el.push_back("mpeg");
	el.push_back("mov");
	el.push_back("wmv");
	el.push_back("rm");

	return el;
}

void AviFileDriver::load_file(const std::string& file_name, VideoInfo& info)
{
  std::cerr << "load_file_start" << std::endl;
  if (m_impl->is_open())
    throw std::logic_error("Driver already open");

  m_impl->file_name = file_name;
 

  m_impl->videoFile = avm::CreateReadFile(m_impl->file_name.c_str());
  if (m_impl->videoFile == 0)
    throw std::runtime_error("could not open");
  
  std::cerr << "load_file_readfile" << std::endl;
  try
    {
      if(!m_impl->videoFile->IsValid())
        {
          throw std::runtime_error("videoFile is not valid");
        }
          
      if(m_impl->videoFile->IsRedirector())
        {
          throw std::runtime_error("not implemented");	      
        }
          
      if(!m_impl->videoFile->IsOpened())
        {
          throw std::invalid_argument("videoFile not opened");	      
        }
	  
      if(m_impl->videoFile->VideoStreamCount() < 1)
        {
          throw std::runtime_error("no VideoStream");	      
        }
          
      m_impl->videoStream 
        = m_impl->videoFile->GetStream(0,avm::IStream::Video);
      std::cerr << "load_file_getstream" << std::endl;

      if (m_impl->videoStream == 0)
	throw std::runtime_error("could not open stream");	      
      
      try
        {
	  std::auto_ptr<avm::StreamInfo> 
	    sinfo(m_impl->videoStream->GetStreamInfo());

	  if (sinfo.get() == 0)
	    throw std::runtime_error("could not get stream info");	      
	  std::cerr << "load_file_streaminfo" << std::endl;
	  
          info.width      = m_impl->w = sinfo->GetVideoWidth();
          info.height     = m_impl->h = sinfo->GetVideoHeight();
          info.num_frames = m_impl->nf = 
            m_impl->videoStream->GetLength()-1;
              
          //m_impl->videoStream->SetDirection(true);
          int error = m_impl->videoStream->StartStreaming();
          if (error == -1)
            throw std::runtime_error("could not start streaming");
	  std::cerr << "load_file_startstreaming" << std::endl;

          avm::BitmapInfo bi(m_impl->w, m_impl->h, 32);
	  assert(m_impl->im==0);
          m_impl->im = new avm::CImage(&bi);
	  
        }
      catch(std::runtime_error& e)
        {
	  if ( m_impl->im != 0 )
	    {
	      //m_impl->im->Release();
	      delete m_impl->im;
	      m_impl->im=0;
	    }

          delete m_impl->videoStream;
          m_impl->videoStream=0;
          throw;
        }
    }
  catch(std::runtime_error& e)
    {
      if (m_impl->videoFile !=0)
	{
	  //delete m_impl->videoFile;
	  m_impl->videoFile=0;
	}
      throw;
    }
}

void AviFileDriver::close_file()
{
  m_impl->close();
}

bool AviFileDriver::is_open() const
{
  return m_impl->is_open();
}

void AviFileDriver::decode_frame(unsigned int frame_number,
                                 uint_32* framebuffer,
				 int width, int height)
{      
  assert(m_impl->videoFile != 0);
  assert(m_impl->videoStream != 0);

  if (!m_impl->is_open())
    throw std::logic_error("No file loaded");

  if (frame_number >= m_impl->nf)
    throw std::range_error("frame_number out of range");

  // we must decode
  if(m_impl->videoStream->GetLength() != 0 &&
     frame_number != m_impl->videoStream->GetPos())
    {
      // we must seek
      unsigned int pkey = m_impl->videoStream->GetPrevKeyFrame(frame_number);

      if (frame_number == pkey)
        {
          // frame is a keyframe
          m_impl->videoStream->Seek(pkey);
        }
      else
        {
          // frame isnt a keyframe
          if (!(m_impl->videoStream->GetPos() <= frame_number&&
                m_impl->videoStream->GetPos() >= pkey))
            {
              // current position is not  better than any key
              m_impl->videoStream->Seek(pkey);
            }
        }
		  
      // drop non keyframes
      int drop = frame_number - m_impl->videoStream->GetPos();
      for (int i=0; i != drop; ++i)
        {
          //std::cout << "drop " << m_impl->videoStream->GetPos() << std::endl;
          m_impl->videoStream->ReadFrame();
          avm::CImage* image = m_impl->videoStream->GetFrame();
	  if (image!=0)
	    image->Release();
        }
    }
	      
  //std::cout << "decode: " << m_impl->videoStream->GetPos() << std::endl;
  if(!m_impl->videoStream->Eof())
    {
      // decode frame
      int error = m_impl->videoStream->ReadFrame();
          
      // get pointer to internal frame
      if (error == -1)
	  {
          throw std::runtime_error(" error while read ");
      }
        
      avm::CImage* image = m_impl->videoStream->GetFrame();
      if (image!=0)
	{
	  // convert any format to bgra
	  m_impl->im->Convert(image);
	  
	  // release pointer to internal frame
	  image->Release();
	}
      // scale to width x height
      ls_scale32(framebuffer, width, height,
                 reinterpret_cast<const uint_32*>(m_impl->im->Data()),
                 m_impl->w, m_impl->h);

    }
}
