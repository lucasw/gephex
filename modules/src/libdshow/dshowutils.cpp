#include "dshowutils.h"

#include <stdexcept>

// Helper functions:
static HRESULT GetPin(IBaseFilter *filter, PIN_DIRECTION PinDir,
					  IPin **pin)
{
    IEnumPins  *en;
    IPin       *current;
    filter->EnumPins(&en);
	
    while (en->Next(1, &current, 0) == S_OK)
    {
        PIN_DIRECTION PinDirThis;
        current->QueryDirection(&PinDirThis);
        if (PinDir == PinDirThis)
        {
            en->Release();
            *pin = current;
            return S_OK;
        }
        current->Release();
    }
    en->Release();
    return E_FAIL;  
}

static HRESULT ConnectFilters(IGraphBuilder *graph,
							  IBaseFilter *lhs,
							  IBaseFilter *rhs)
{
	HRESULT hr = S_OK;
    IPin *out = 0;
	IPin *in  = 0;
	
    hr = GetPin(lhs, PINDIR_OUTPUT, &out);
	
    if (FAILED(hr))
		return hr;
	
    hr = GetPin(rhs, PINDIR_INPUT, &in);
	
    if (FAILED(hr)) 
    {
        out->Release();
        return hr;
	}
	
    hr = graph->Connect(out, in);
    in->Release();
    out->Release();
    return hr;
}


void build_grabber_graph(IGraphBuilder**  graph,
						 IMediaControl**  mediacontrol,
						 IBaseFilter**    grabber_basefilter,
						 ISampleGrabber** samplegrabber,
						 IBaseFilter**    null_renderer,
						 ISampleGrabberCB* callback)
{
	HRESULT hr;
	
	// first build the graph itself
	CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER, 
		IID_IGraphBuilder, (void **)graph);
	
	(*graph)->QueryInterface(IID_IMediaControl, (void **)mediacontrol);
	//(*graph)->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
	
	// now create a sample grabber		
	hr = ::CoCreateInstance(CLSID_SampleGrabber, 0,
		CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, 
		(void**) grabber_basefilter);
	
	if (FAILED(hr))
	{
		char temp[1024];
		AMGetErrorText(hr, temp, sizeof(temp));		
		
		throw std::runtime_error(temp);
	}
	
	(*grabber_basefilter)->QueryInterface(IID_ISampleGrabber,
		(void**) samplegrabber);
	if (*samplegrabber == 0)
	{			
		throw std::runtime_error("Could not quere ISampleGrabber"
			" interface");
	}
	
	// and add it to the graph
	hr = (*graph)->AddFilter(*grabber_basefilter, L"Grabber");
	if (FAILED(hr))
	{
		char temp[1024];
		AMGetErrorText(hr, temp, sizeof(temp));		
		
		throw std::runtime_error(temp);
	}
	
	// set the media type of the sample grabber to RGB32
	AM_MEDIA_TYPE mt;
	ZeroMemory(&mt, sizeof(mt));
	mt.majortype  = MEDIATYPE_Video;
	mt.subtype    = MEDIASUBTYPE_RGB32;
	mt.formattype = FORMAT_VideoInfo; 
	hr = (*samplegrabber)->SetMediaType(&mt);
	if (FAILED(hr)) 
	{
		char temp[1024];
		AMGetErrorText(hr, temp, sizeof(temp));		
		
		throw std::runtime_error(temp);
	}		
	
	
	(*samplegrabber)->SetOneShot(FALSE);
	if (callback)
	{
		(*samplegrabber)->SetBufferSamples(FALSE);
		(*samplegrabber)->SetCallback(callback, 1);
	}
	else
	{
		(*samplegrabber)->SetBufferSamples(TRUE);
	}
	
	if (null_renderer)
	{
		hr = CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER,
			IID_IBaseFilter, reinterpret_cast<void**>(null_renderer));
		if (FAILED(hr)) 
		{
			char temp[1024];
			AMGetErrorText(hr, temp, sizeof(temp));
			
			throw std::runtime_error(temp);
		}
		
		
		hr = (*graph)->AddFilter(*null_renderer, L"NullRenderer");
		if (FAILED(hr)) 
		{
			char temp[1024];
			AMGetErrorText(hr, temp, sizeof(temp));
			
			throw std::runtime_error(temp);		
		}

	}

}

void connect_source_filter(IGraphBuilder* graph,
					       IBaseFilter* grabber_basefilter,
					       ISampleGrabber* samplegrabber,
						   IBaseFilter* null_renderer,
					       IBaseFilter* src,
					       int& width, int& height)
{
	HRESULT hr;
				
	// finally connect the capture device to the sample grabber
	hr = ConnectFilters(graph, src, grabber_basefilter);
	if (FAILED(hr)) 
	{
		char temp[1024];
		AMGetErrorText(hr, temp, sizeof(temp));		
		
		throw std::runtime_error(temp);
	}

	if (null_renderer)
	{
		hr = ConnectFilters(graph, grabber_basefilter, null_renderer);
		if (FAILED(hr)) 
		{
			char temp[1024];
			AMGetErrorText(hr, temp, sizeof(temp));
			
			throw std::runtime_error(temp);		
		}
	}
	
	// query media type of the capture device
	AM_MEDIA_TYPE MediaType; 
	ZeroMemory(&MediaType,sizeof(MediaType)); 
	hr = samplegrabber->GetConnectedMediaType(&MediaType); 
	if (FAILED(hr))
	{
		char temp[1024];
		AMGetErrorText(hr, temp, sizeof(temp));		
		
		throw std::runtime_error(temp);
	}
	
	// Get a pointer to the video header. 
	VIDEOINFOHEADER *pVideoHeader = reinterpret_cast<VIDEOINFOHEADER*>(MediaType.pbFormat);
	if (pVideoHeader == 0)
	{
		CoTaskMemFree(MediaType.pbFormat);
		throw std::runtime_error("videoinfoheader is 0");
	}
	
	// The video header contains the bitmap information. 
	// Copy it into a BITMAPINFO structure. 
	BITMAPINFOHEADER* BitmapInfo = &pVideoHeader->bmiHeader;	
	
	width  = BitmapInfo->biWidth;
	height = BitmapInfo->biHeight;	
	
	//	FreeMediaType(MediaType);
	CoTaskMemFree(MediaType.pbFormat);
	//m_media_control->Run();	
}

