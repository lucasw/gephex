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

#include "dshowdriver.h"

#include <string>
#include <stdexcept>
#include <memory>
#include <iostream>

#include <windows.h>
#include <dshow.h>
#include <qedit.h>

#include "timer.h"

#include <sys/timeb.h>

//#include "samplecallback.h"
#include "dshowutils.h"

#include "libscale.h"

static unsigned long time_in_ms()
{
	struct _timeb timebuffer;

	_ftime( &timebuffer );

	return timebuffer.time*1000 + timebuffer.millitm;
}

//#define SEGMENT_SEEK
#define ONE_SHOT

//----------------------------------------------------------------------

static BOOL GetFormattedError(LPTSTR dest,int size)
{
	DWORD dwLastError=GetLastError();
	if(!dwLastError)
		return 0;
	BYTE width=0;
	DWORD flags;
	flags  = FORMAT_MESSAGE_MAX_WIDTH_MASK &width;
	flags |= FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS;
	return 0 != FormatMessage(flags,
		NULL,
		dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		dest,
		size,
		NULL);
}


//----------------------------------------------------------------------

class Callback : public TimerCallback
{
public:
	Callback(IMediaControl* media,
		     const unsigned long& last_grab,
			 const bool& in_grab_frame,
			 unsigned long time_to_stop)
		: m_media(media), m_last_grab(last_grab),
		  m_in_grab_frame(in_grab_frame),
		  m_time_to_stop(time_to_stop) {}

	void operator()()
	{
		unsigned long time = time_in_ms();
		if(!m_in_grab_frame && time - m_last_grab > m_time_to_stop)
		{
			m_media->Stop();
		}
	}

private:
	IMediaControl* m_media;
	const unsigned long& m_last_grab;
	const bool m_in_grab_frame;
	unsigned long m_time_to_stop;
};
//----------------------------------------------------------------------

class DSHOWDriverImpl
{
public:
	DSHOWDriverImpl()
		: m_event(0), m_grabber_basefilter(0), m_graph(0),
		  m_mediacontrol(0),
		  m_null_renderer(0),
		  m_samplegrabber(0), m_src(0),
		  m_media_seek(0),
		  m_width(0),
		  m_height(0),
		  m_tmp_data(0),
		  m_last_grabtime(0),		  
		  m_timer(0),
		  m_in_grab_frame(false)
	{
		CoInitialize(NULL);		
	}
	
	~DSHOWDriverImpl()
	{
		destroyFilterGraph();
		
		delete m_timer;
		
		CoUninitialize();

		delete[] m_tmp_data;
		
	}
	
	void destroyFilterGraph()
	{
		if (m_timer != 0)
		{
			delete m_timer;
			m_timer = 0;
		}

		if (m_mediacontrol != 0)
		{
			m_mediacontrol->Release();
			m_mediacontrol = 0;
		}

		if (m_media_seek != 0)
		{
			m_media_seek->Release();
			m_media_seek= 0;
		}
		
		if (m_event != 0)
		{
			m_event->Release();
			m_event = 0;
		}
		
		if (m_grabber_basefilter != 0)
		{
			m_grabber_basefilter->Release();
			m_grabber_basefilter = 0;
		}
		
		if (m_samplegrabber != 0)
		{
			m_samplegrabber->Release();
			m_samplegrabber = 0;
		}
		
		if (m_null_renderer != 0)
		{
			m_null_renderer->Release();
			m_null_renderer = 0;
		}
		
		if (m_src != 0)
		{
			m_src->Release();
			m_src = 0;
		}
		
		if (m_graph != 0)
		{
			m_graph->Release();
			m_graph = 0;
		}
	}
	
	void close()  						
	{	
		destroyFilterGraph();
	}
	
	void load(const std::string& filename, VideoInfo& info)
	{	
		
		build_grabber_graph(&m_graph, &m_mediacontrol,
			                &m_grabber_basefilter, &m_samplegrabber,
							&m_null_renderer, 0);
			                //&m_callback);
		
		
		m_graph->QueryInterface(IID_IMediaEvent, (void **)&m_event);		
		
		HRESULT hr;
		unsigned short buffer[1024];
		MultiByteToWideChar(CP_ACP,0,
			                filename.c_str(),
			                filename.length()+1,
							buffer,
							sizeof(buffer));
		
		hr = m_graph->AddSourceFilter(buffer, L"Source", &m_src);
		if (FAILED(hr)) 
		{
			char temp[1024];
			AMGetErrorText(hr, temp, sizeof(temp));
			
			throw std::runtime_error(temp);
		}
		
		connect_source_filter(m_graph, m_grabber_basefilter,
			                  m_samplegrabber, m_null_renderer,
							  m_src, m_width, m_height);

		info.width  = m_width;
		info.height = m_height;

		hr = m_graph->QueryInterface(IID_IMediaSeeking,
			                         (void**) &m_media_seek);
		if (FAILED(hr))
		{
			char temp[1024];
			AMGetErrorText(hr, temp, sizeof(temp));
			
			throw std::runtime_error(temp);
		}

		DWORD dwCap = 0;
		hr = m_media_seek->GetCapabilities(&dwCap);
		if (FAILED(hr)) 
		{
			char temp[1024];
			AMGetErrorText(hr, temp, sizeof(temp));
			
			throw std::runtime_error(temp);
		}
		if (!(AM_SEEKING_CanSeekAbsolute & dwCap)  /*||
			!(AM_SEEKING_CanGetCurrentPos & dwCap) *//*||
			!(AM_SEEKING_CanGetStopPos & dwCap)    ||*/
			/*!(AM_SEEKING_CanGetDuration & dwCap)*/)
		{
			throw std::runtime_error("Can not seek in file");
		}
#if defined (SEGMENT_SEEK)
		if (!(AM_SEEKING_CanDoSegments & dwCap))
		{
			//throw std::runtime_error("Can't do segment seeks");
		}
#endif


		hr = m_media_seek->SetTimeFormat(&TIME_FORMAT_FRAME);
		if (FAILED(hr)) 
		{
			char temp[1024];
			AMGetErrorText(hr, temp, sizeof(temp));
			
			throw std::runtime_error(temp);
		}

		LONGLONG current;
		LONGLONG  stop;
		hr = m_media_seek->GetPositions(&current, &stop);
		if (FAILED(hr)) 
		{
			char temp[1024];
			AMGetErrorText(hr, temp, sizeof(temp));
			
			throw std::runtime_error(temp);
		}

		info.num_frames = stop+1;

#if defined(ONE_SHOT)
		m_samplegrabber->SetOneShot(TRUE);
#endif

		m_last_grabtime = time_in_ms();
		Callback* cb = new Callback(m_mediacontrol,
			                        m_last_grabtime,
									m_in_grab_frame,
									500);
		//m_timer = new Timer(500, cb);

		m_mediacontrol->Run();
	}
	
	
	void grab_frame(uint_32* frb, int frame, int width, int height)
	{	
		m_in_grab_frame = true;
		HRESULT hr;
	
#if !defined (ONE_SHOT)
		m_mediacontrol->Pause();
#endif

		LONGLONG current;
		LONGLONG  stop;
		hr = m_media_seek->GetPositions(&current, &stop);
		if (FAILED(hr)) 
		{
			char temp[1024];
			AMGetErrorText(hr, temp, sizeof(temp));
			
			throw std::runtime_error(temp);
		}

		if (current != frame)
		{
			LONGLONG c = frame;
#if defined (SEGMENT_SEEK)
			hr = m_media_seek->SetPositions(&c,
				                            AM_SEEKING_AbsolutePositioning |
											AM_SEEKING_NoFlush || AM_SEEKING_Segment,
											&c,
											AM_SEEKING_NoFlush || AM_SEEKING_Segment);
#else
			hr = m_media_seek->SetPositions(&c,
				                            AM_SEEKING_AbsolutePositioning |
											AM_SEEKING_NoFlush,
											0,
											AM_SEEKING_NoPositioning);
#endif

			if (FAILED(hr)) 
			{
				char temp[1024];
				AMGetErrorText(hr, temp, sizeof(temp));
				
				throw std::runtime_error(temp);
			}

		m_mediacontrol->Run();

#if defined (ONE_SHOT)
		// wait for one shot		
		long event;
		hr = m_event->WaitForCompletion(1000, &event);
		if (FAILED(hr))
		{
			char temp[1024];
			AMGetErrorText(hr, temp, sizeof(temp));		
			
			throw std::runtime_error(temp);
		}
		if (event != EC_COMPLETE)
		{
			std::cerr << "invalid event code: " << event << "\n";
		}
#elif defined (SEGMENT_SEEK)
		// wait for one shot		
		long event = -1;
		do
		{
			long p1, p2;
			hr = m_event->GetEvent(&event, &p1, &p2, 1000);
			if (FAILED(hr)) 
			{
				char temp[1024];
				AMGetErrorText(hr, temp, sizeof(temp));		
				
				throw std::runtime_error(temp);
			}			
		} while (event != EC_END_OF_SEGMENT && event != EC_COMPLETE);
#endif
		m_mediacontrol->Pause();
	}
		long size;

		hr = m_samplegrabber->GetCurrentBuffer(&size, 0);
		if (hr == VFW_E_WRONG_STATE)
		{
			return;
		}
		else if (FAILED(hr)) 
		{
			char temp[1024];
			AMGetErrorText(hr, temp, sizeof(temp));		
			
			throw std::runtime_error(temp);			
		}

		if (size != m_width * m_height * 4)
		{
			throw std::runtime_error("wrong size of sample buffer");
		}

		if (width == m_width && height == m_height)
		{
			m_samplegrabber->GetCurrentBuffer(&size, (long*) frb);
			if (m_tmp_data)
			{
				delete[] m_tmp_data;
				m_tmp_data = 0;
			}
		}
		else
		{
			if (m_tmp_data == 0)
			{
				m_tmp_data = new uint_32[size/4];
			}			
			m_samplegrabber->GetCurrentBuffer(&size, (long*) m_tmp_data);

			ls_scale32(frb, width, height,
				       m_tmp_data, m_width, m_height);			
		}


#if defined (ONE_SHOT)
		//m_samplegrabber->SetOneShot(TRUE);
		//m_mediacontrol->Pause();
#endif	

		m_last_grabtime = time_in_ms();
		m_in_grab_frame = false;
	}

	bool is_open() const
	{
		return m_graph != 0;
	}
	
private:
	IGraphBuilder* m_graph;
    IMediaControl* m_mediacontrol;
    IMediaEvent*   m_event;	
	
	IBaseFilter*    m_grabber_basefilter;
    ISampleGrabber* m_samplegrabber;
	
	IBaseFilter*	m_src;
	IBaseFilter*	m_null_renderer;

	IMediaSeeking*  m_media_seek;
	
	int m_width;
	int m_height;

	uint_32* m_tmp_data;

	unsigned long m_last_grabtime;
	
	Timer* m_timer;
	//SampleCallback m_callback;

	bool m_in_grab_frame;
};

//----------------------------------------------------------------------

DSHOWDriver::DSHOWDriver()
: m_impl(new DSHOWDriverImpl())
{
}

DSHOWDriver::~DSHOWDriver()
{
}

std::list<std::string> DSHOWDriver::supported_extensions()
{
	std::list<std::string> el;
	el.push_back("avi");
	el.push_back("divx");
	el.push_back("mpg");
	el.push_back("mpeg");
	el.push_back("mov");
	el.push_back("wmf");
	el.push_back("rm");
	
	return el;
}

void DSHOWDriver::load_file(const std::string& file_name, VideoInfo& info)
{
	if (m_impl->is_open())
		m_impl->close();

	m_impl->load(file_name, info);
}

void DSHOWDriver::decode_frame(unsigned int frame_number,
							   uint_32* framebuffer,
							   int width, int height)
{
	if (m_impl->is_open())
		m_impl->grab_frame(framebuffer, frame_number, width, height);
}

void DSHOWDriver::close_file()
{
	m_impl->close();
}

bool DSHOWDriver::is_open() const
{
	return m_impl->is_open();
}

