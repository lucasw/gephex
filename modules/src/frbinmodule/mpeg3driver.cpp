#include "mpeg3driver.h"

#include <string>
#include <stdexcept>
#include "libmpeg3.h"
#include <iostream>

struct Mpeg3DriverImpl
{
  Mpeg3DriverImpl()
    :file(0),file_name(""),w(0),h(0),l(0),rows(0),stream(0)
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
  int stream;
};

Mpeg3Driver::Mpeg3Driver()
  : m_impl(new Mpeg3DriverImpl())
{
}

Mpeg3Driver::~Mpeg3Driver()
{
  if (m_impl->file!=0)
    {
      mpeg3_close(m_impl->file);
      m_impl->file=0;
    }
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
  //check is filename changed
  if (m_impl->file_name!=file_name)
    { // close and open file
      m_impl->file_name=file_name;
      if (m_impl->file!=0)
	{
	  mpeg3_close(m_impl->file);
	  m_impl->file=0;
	}
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
		  m_impl->stream=0;
		  int oldh= m_impl->h;
		  m_impl->w=mpeg3_video_width(m_impl->file,m_impl->stream);
		  m_impl->h=mpeg3_video_height(m_impl->file,m_impl->stream);
		  m_impl->l= mpeg3_video_frames(m_impl->file,m_impl->stream);
		  if (m_impl->l==1)
		    throw std::runtime_error("% seeking not implemented");
		  info.width      = m_impl->w;
		  info.height     = m_impl->h;
		  info.num_frames = m_impl->l;
		  if (oldh!=m_impl->h)
		    {
		      delete[] m_impl->rows;
		      m_impl->rows = new uint_8*[m_impl->h];
		    }
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
}

void Mpeg3Driver::decode_frame(unsigned int frame_number, uint_32* framebuffer)
{
  if (m_impl->file == 0)
    throw std::invalid_argument("No file loaded");

  if (frame_number >= m_impl->l)
      throw std::range_error("frame_number out of range");

  // calc rows
  for(int i=0; i!=m_impl->h;++i)
    {
      m_impl->rows[i]=reinterpret_cast<uint_8*>(framebuffer+(i*m_impl->w));
    }
  
  if (mpeg3_set_frame(m_impl->file,frame_number,m_impl->stream)==-1)
    throw std::range_error("could not seek to that position");
  
  // decode one frame
  int errorCode = mpeg3_read_frame(m_impl->file,m_impl->rows,
				   0,0,m_impl->w,m_impl->h, // input window
				   m_impl->w,m_impl->h, // output window
				   MPEG3_BGRA8888,
				   m_impl->stream);
  if (errorCode==-1)
    throw std::runtime_error("could not decode frame");
}

