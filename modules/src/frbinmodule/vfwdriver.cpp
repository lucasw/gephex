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

#include "vfwdriver.h"

#include <string>
#include <stdexcept>
#include <memory>
#include <map>

#include <windows.h>
#include <vfw.h>

//----------------------------------------------------------------------


/**
 *
 * There is a bug in vfw AVIStreamGetFrameClose (at least on my os,
 * (win2k, sp4 with all security patches as of Nov 06 2003):
 *
 * Assume an avi file has been opened more than once and for each instance
 * AVIStreamGetFrameOpen has been called.
 * Now I close one instance with AVIStreamGetFrameClose. 
 * AVIStreamGetFrame will cause an access violation in the other
 * instances (although the manual says that AviStreamGetFrameClose is
 * refcounted).
 *
 * The workaround is to hold a static list of all open AVIStreamGetFrame
 * instances for each file and to close them only when all instances
 * are done.
 * This is ugly and leads to a lot of memory consumption if the same
 * avi is open often.
 */
typedef std::list<void*> StreamGetList;
typedef std::map<std::string, std::pair<int, StreamGetList> > StreamMap;
static StreamMap s_get_stream_count;

//----------------------------------------------------------------------
static int createDIB(HDC hdc,
					 HBITMAP* p_hBitmap,
					 uint_32** p_data,
					 int xsize, int ysize)
{
	BITMAPINFOHEADER bmih;
	bmih.biSize        = sizeof (BITMAPINFOHEADER);
	bmih.biPlanes      = 1;
	bmih.biBitCount    = 32;
	bmih.biWidth       = xsize;
	bmih.biHeight      = -ysize;  //top-down
	bmih.biCompression = BI_RGB;
		
	
	*p_hBitmap = CreateDIBSection (hdc, (BITMAPINFO*)&bmih,
		DIB_RGB_COLORS, (void**) p_data,
		NULL, 0);
	
	SelectObject (hdc, *p_hBitmap);
	
	return 1;
}

static void destroyDIB(HDC hdc, HBITMAP* p_hBitmap)
{
  SelectObject(hdc, 0); //TODO

  if (DeleteObject(*p_hBitmap) == 0)
	  printf("DeleteObject failed");
  *p_hBitmap = 0;
}


//----------------------------------------------------------------------

class VFWDriverImpl
{
public:

  VFWDriverImpl()
    : m_pgf(0), m_hdc(0)
  {
    m_hdd = DrawDibOpen();
    AVIFileInit();

  }

  ~VFWDriverImpl()
  {
	  close();
	  DrawDibClose(m_hdd);
	  AVIFileExit();
  }
  
  void load(const std::string& filename, VideoInfo& info)
  {
	  
	  // Opens The AVI Stream
	  if (AVIFileOpen(&m_avifile, filename.c_str(), OF_READ, 0) != 0)
	  {
		  throw std::runtime_error("Failed To Open The file: '"
			                          + filename + "'");
	  }

	  if (AVIFileGetStream(m_avifile, &m_pavi, streamtypeVIDEO, 0) != 0)
	  {	
		  AVIFileRelease(m_avifile);
		  throw std::runtime_error("Failed To Open The AVI Stream: '"
			                          + filename + "'");	
	  }

	  /*if (AVIStreamOpenFromFile(&m_pavi, filename.c_str(),
		                        streamtypeVIDEO, 0, OF_READ, NULL) !=0)
	  {
		  throw std::runtime_error("Failed To Open The AVI Stream: '"
			                          + filename + "'");
	  }*/
	  
	  
	  AVIStreamInfo(m_pavi, &m_psi, sizeof(m_psi));
	  
	  m_width     = m_psi.rcFrame.right - m_psi.rcFrame.left;
	  m_height    = m_psi.rcFrame.bottom - m_psi.rcFrame.top;
	  m_numframes = AVIStreamLength(m_pavi);

	  info.width  = m_width;
	  info.height = m_height;
	  info.num_frames = m_numframes;
	  
	  //m_mpf = AVIStreamSampleToTime(m_pavi,m_numframes-1) / (m_numframes-1);
	  
	  m_pgf = AVIStreamGetFrameOpen(m_pavi, NULL);
	  
	  if (m_pgf == NULL)
	  {		  		  
		  AVIStreamRelease(m_pavi);
		  AVIFileRelease(m_avifile);
		  m_pavi = 0;
		  throw std::runtime_error("Failed To Open The AVI Frame");		  
	  }

	  StreamMap::iterator it = s_get_stream_count.find(filename.c_str());
	  if (it == s_get_stream_count.end())
	  {
		  StreamGetList l;
		  l.push_back(m_pgf);
		  s_get_stream_count.insert(std::make_pair(filename.c_str(),
			  std::make_pair(1,l)));
	  }
	  else
	  {
		  ++it->second.first;
		  it->second.second.push_back(m_pgf);
	  }

	  m_hdc = CreateCompatibleDC(0);
	  m_filename = filename;
	  m_bmp_width = -1;
	  m_bmp_height  = -1;
	  m_hBitmap = 0;	  	  
  }

  void close()
  {	  
	  if (is_open())
	  {
		  if (m_hBitmap != 0)
			destroyDIB(m_hdc, &m_hBitmap);

		  if (DeleteDC(m_hdc) == 0)
			  printf("DeleteDC failed\n");
		  m_hdc = 0;


		  StreamMap::iterator it = s_get_stream_count.find(m_filename.c_str());
		  if (it == s_get_stream_count.end())
		      printf("SFHALSGKHALGKHAGLSKH\n");
		  else
		  {
		     --it->second.first;
			 if (it->second.first == 0)
			 {				 
				 for (StreamGetList::iterator i = it->second.second.begin();
				      i != it->second.second.end(); ++i)
					  {
				  if (AVIStreamGetFrameClose((IGetFrame*)*i) != 0)
					  printf("StreamGetFrameClose failed\n");
					  }

				it->second.second.clear();
			 }
		  }
		  m_pgf = 0;

		  if (AVIStreamRelease(m_pavi) != 0)
			  printf("StreamRelease failed\n");
		  m_pavi = 0;

		  if (AVIFileRelease(m_avifile) != 0)
              printf("FileRelease failed\n");
		  m_avifile = 0;

		  m_filename = "";
	  }	  
  }

  bool is_open() const
  {
	  return m_hdc != 0;
  }

  void grab_frame(unsigned int frame, uint_32* frb, int width, int height)
  {	  	  
	  // Holds The Bitmap Header Information
	  LPBITMAPINFOHEADER lpbi;
	  	  
	  if (frame >= m_numframes)
		  throw std::range_error("frame_number out of range");
	  
	  // Grab Data From The AVI Stream
	  lpbi = (LPBITMAPINFOHEADER) AVIStreamGetFrame(m_pgf, frame);
	  
	  if ( lpbi == 0 )
	  {
		  throw std::runtime_error("Error at AVIStreamGetFrame()!");
	  }
	  else
	  {		  	  
		  if (m_hBitmap == 0 || m_bmp_width != width ||
			  m_bmp_height != height)
		  {
			  m_bmp_width  = width;
			  m_bmp_height = height;

			  if (m_hBitmap)
				  destroyDIB(m_hdc, &m_hBitmap);

			  createDIB(m_hdc, &m_hBitmap, &m_data, width, height);
		  }
		  
		  // Pointer To Data Returned By AVIStreamGetFrame:
		  char* pdata= ((char *)lpbi) + lpbi->biSize 
			           + lpbi->biClrUsed * sizeof(RGBQUAD);

		  //Convert Data To Requested Bitmap Format
		  DrawDibDraw (m_hdd, m_hdc, 0, 0, width, height,
			           lpbi, pdata, 0, 0, m_width, m_height, 0);
		  
		  //return m_data;
		  memcpy(frb, m_data, width*height*4);
	  }
  }  

private:
  AVISTREAMINFO	m_psi;
  PAVIFILE      m_avifile;
  PAVISTREAM	m_pavi;	
  PGETFRAME		m_pgf;
  HBITMAP		m_hBitmap;
  HDC			m_hdc;
  int			m_numframes;
  uint_32*		m_data;
  int			m_width;
  int			m_height;
  HDRAWDIB      m_hdd; //from DrawDibOpen

  int m_bmp_width;
  int m_bmp_height;
  std::string m_filename;
  
};

//----------------------------------------------------------------------

VFWDriver::VFWDriver()
	: m_impl(new VFWDriverImpl())
{
}

VFWDriver::~VFWDriver()
{
}

std::list<std::string> VFWDriver::supported_extensions()
{
	std::list<std::string> el;
	el.push_back("avi");
	el.push_back("divx");
	el.push_back("mpg");
	el.push_back("mpeg");
	el.push_back("mov");
	el.push_back("wmv");
	el.push_back("rm");
	el.push_back("*");

	return el;
}

void VFWDriver::load_file(const std::string& file_name, VideoInfo& info)
{
	if (m_impl->is_open())
		throw std::logic_error("Driver already open");

	m_impl->load(file_name, info);
}

void VFWDriver::close_file()
{
	m_impl->close();
}

bool VFWDriver::is_open() const
{
	return m_impl->is_open();
}
  
void VFWDriver::decode_frame(unsigned int frame_number, uint_32* framebuffer,
							 int width, int height)
{
	if (!m_impl->is_open())
		throw std::logic_error("Driver not open");

	m_impl->grab_frame(frame_number, framebuffer, width, height);	
}

 
