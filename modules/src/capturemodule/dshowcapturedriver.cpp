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

#include "dshowcapturedriver.h"

#include <string>
#include <stdexcept>

#include <cassert>

#include <dshow.h>
#include <qedit.h>

#include "dshowutils.h"
#include "samplecallback.h"

#include "libscale.h"


//----------------------------------------------------------------------

IBaseFilter* get_capture_device(int device_num)
{
    ICreateDevEnum* createDeviceEnum;
    CoCreateInstance(CLSID_SystemDeviceEnum, 0,
					 CLSCTX_INPROC_SERVER,
					 IID_ICreateDevEnum,
					 (void**) &createDeviceEnum);

    if (createDeviceEnum == 0)
	{
        return 0;
	}

    IEnumMoniker* enumMoniker;
    createDeviceEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,
	                                        &enumMoniker, 0);
    if (enumMoniker == 0)
	{
		createDeviceEnum->Release();
        return 0;
	}

    enumMoniker->Reset();

    IBaseFilter* result = 0;
 
	int index = 0;
	IMoniker* moniker;
    while (enumMoniker->Next(1, &moniker, 0) == S_OK)
	{        
		if (index == device_num)
		{
			HRESULT bindToObjectResult =
				moniker->BindToObject(0, 0, IID_IBaseFilter, (void**) &result);
            break;
		}

		moniker->Release();
		++index;
    }

	enumMoniker->Release();
	createDeviceEnum->Release();
	
	return result;
}

//---------------------------------------------------------------------

static BOOL GetFormattedError(LPTSTR dest,int size)
{
	DWORD dwLastError = GetLastError();

	if (!dwLastError)
		return 0;

	BYTE width=0;
	DWORD flags;
	flags  = FORMAT_MESSAGE_MAX_WIDTH_MASK &width;
	flags |= FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS;
	return 0 != FormatMessage(flags,
		0,
		dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		dest,
		size,
		0);
}

//----------------------------------------------------------------------

class DSHOWCaptureDriver::Impl
{
public:
	Impl()
		: /*pEvent(0),*/ m_grabber_base_filter(0), m_graph(0),
		  m_media_control(0),
	      m_sample_grabber(0), m_capture_filter(0),
		  m_width(0), m_height(0)
	{
		CoInitialize(0);
		//CoInitializeEx(0, COINIT_MULTITHREADED);
	}
	
	~Impl()
	{
		destroyFilterGraph();		
		CoUninitialize();
	}
	
	void buildFilterGraph(int device_num)
	{
		HRESULT hr;
		// now look for a capture device		
		m_capture_filter = get_capture_device(device_num);
		if (m_capture_filter == 0)
		{
			throw std::runtime_error("Could not find capture device");			
		}		

		build_grabber_graph(&m_graph, &m_media_control,
			                &m_grabber_base_filter,
							&m_sample_grabber,
							0,
							&m_callback);

		// and add it to the graph
		hr = m_graph->AddFilter(m_capture_filter, L"Capture Device");
		if (FAILED(hr)) 
		{
			char temp[1024];
			AMGetErrorText(hr, temp, sizeof(temp));		
			
			throw std::runtime_error(temp);
		}
		
		
		// finally connect the capture device to the sample grabber

		connect_source_filter(m_graph, m_grabber_base_filter,
                              m_sample_grabber, 0, m_capture_filter,
							  m_width, m_height);
	}
	
	
	void destroyFilterGraph()
	{
		if (m_media_control != 0)
		{
			m_media_control->Stop();
			m_media_control->Release();
			m_media_control = 0;
		}
		
		/*if (pEvent != 0)
		{
			pEvent->Release();
			pEvent = 0;
		}*/
		
		if (m_grabber_base_filter != 0)
		{
			m_grabber_base_filter->Release();
			m_grabber_base_filter = 0;
		}
		
		if (m_sample_grabber != 0)
		{
			m_sample_grabber->Release();
			m_sample_grabber = 0;
		}
		
		if (m_capture_filter != 0)
		{
			m_capture_filter->Release();
			m_capture_filter = 0;
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
	
	void open(int device_num)
	{	
		try
		{
			buildFilterGraph(device_num);
			m_media_control->Run();
		}
		catch (std::exception&)
		{
			close();
			throw;
		}
	}
	
	void grab_frame(uint_32* frb, int width, int height)
	{	  	  
		int size = m_callback.buffer_size();
		unsigned char* samples = m_callback.samples();

		if (samples == 0)
		{
			throw std::runtime_error("no image to capture");
		}

		m_callback.sample_fetched();

		if (size != m_width * m_height * 4)
		{
			throw std::runtime_error("wrong size of sample buffer");
		}

		ls_scale32m(frb, width, height,
                   reinterpret_cast<uint_32*>(samples), m_width, m_height,
				   0, 1);
		
		/*if (FAILED(hr))
		{
			char temp[1024];
			AMGetErrorText(hr,temp, sizeof(temp));
			fprintf(stderr,"%s\n",temp);
			throw std::runtime_error(temp);
		}*/	
	}

	bool is_open() const
	{
		return m_graph != 0;
	}

	int width() const { return m_width; }

	int height() const { return m_height; }

	bool new_sample() const { return m_callback.new_sample(); }

private:
	IGraphBuilder* m_graph;
    IMediaControl* m_media_control;
    //IMediaEvent*   pEvent;	
	
	IBaseFilter*    m_grabber_base_filter;
    ISampleGrabber* m_sample_grabber;
	
	IBaseFilter*	m_capture_filter;
	
	SampleCallback  m_callback;
	
	int m_width;
	int m_height;
};

//----------------------------------------------------------------------

DSHOWCaptureDriver::DSHOWCaptureDriver()
: m_impl(new Impl())
{
}

DSHOWCaptureDriver::~DSHOWCaptureDriver()
{
}


void DSHOWCaptureDriver::open(int device)
{
	if (m_impl->is_open())
		throw std::logic_error("Device already open");
	
	m_impl->open(device);
}

void DSHOWCaptureDriver::close()
{
	if (m_impl->is_open())
		m_impl->close();
}

void DSHOWCaptureDriver::decode_frame(uint_32* framebuffer,
									  int width, int height)
{
	if (!m_impl->is_open())
		throw std::logic_error("Device not open");
	
	m_impl->grab_frame(framebuffer, width, height);
}

void DSHOWCaptureDriver::status(int& width,
								int& height,
								bool& new_sample) const
{
	width      = m_impl->width();
	height     = m_impl->height();
	new_sample = m_impl->new_sample();
}

bool DSHOWCaptureDriver::is_open() const
{
	return m_impl->is_open();
}
