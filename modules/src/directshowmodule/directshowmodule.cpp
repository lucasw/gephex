#include "directshowmodule.h"

#include <cstdio>


#include <dshow.h>
#include <qedit.h>

typedef struct avishit_ {		

	IGraphBuilder* pGraph;
    IMediaControl* pMediaControl;
    IMediaEvent*   pEvent;	

	IBaseFilter*    pGrabberBaseFilter;
    ISampleGrabber* pSampleGrabber;

	IBaseFilter*	srcFilter;
	IBaseFilter*	pNullRenderer;

} AviShit;


typedef struct _MyInstance {

	StringType oldFileName;
	AviShit shit;	

} MyInstance, *MyInstancePtr;


// Helper functions:
HRESULT GetPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir, IPin **ppPin)
{
    IEnumPins  *pEnum;
    IPin       *pPin;
    pFilter->EnumPins(&pEnum);
    while(pEnum->Next(1, &pPin, 0) == S_OK)
    {
        PIN_DIRECTION PinDirThis;
        pPin->QueryDirection(&PinDirThis);
        if (PinDir == PinDirThis)
        {
            pEnum->Release();
            *ppPin = pPin;
            return S_OK;
        }
        pPin->Release();
    }
    pEnum->Release();
    return E_FAIL;  
}

HRESULT ConnectFilters(IGraphBuilder *pGraph, IBaseFilter *pFirst, IBaseFilter *pSecond)
{
    IPin *pOut = NULL, *pIn = NULL;
    HRESULT hr = GetPin(pFirst, PINDIR_OUTPUT, &pOut);
    if (FAILED(hr))
		return hr;
    hr = GetPin(pSecond, PINDIR_INPUT, &pIn);
    if (FAILED(hr)) 
    {
        pOut->Release();
        return E_FAIL;
     }
    hr = pGraph->Connect(pOut, pIn);
    pIn->Release();
    pOut->Release();
    return hr;
}

int buildFilterGraph(AviShit* shit)
{

  CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                    IID_IGraphBuilder, (void **)&shit->pGraph);

  shit->pGraph->QueryInterface(IID_IMediaControl, (void **)&shit->pMediaControl);
  shit->pGraph->QueryInterface(IID_IMediaEvent, (void **)&shit->pEvent);

  
  HRESULT hr;
  hr = ::CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,IID_IBaseFilter, (LPVOID *)&shit->pGrabberBaseFilter);
  if (FAILED(hr))
  {
	  //TODO: cleanup
	  return 0;
  }

  shit->pGrabberBaseFilter->QueryInterface(IID_ISampleGrabber, (void**)&shit->pSampleGrabber);
  if (shit->pSampleGrabber == NULL)
  {
	//TODO: cleanup
	//return E_NOINTERFACE;
	return 0;
  }

  hr = shit->pGraph->AddFilter(shit->pGrabberBaseFilter,L"Grabber");
  if (FAILED(hr))
  {
	  //TODO: cleanuo
	//return hr;
	  return 0;
  }

  AM_MEDIA_TYPE mt;
  ZeroMemory(&mt,sizeof(AM_MEDIA_TYPE));
  mt.majortype = MEDIATYPE_Video;
  mt.subtype = MEDIASUBTYPE_RGB32;
  mt.formattype = FORMAT_VideoInfo; 
  hr = shit->pSampleGrabber->SetMediaType(&mt);
  if (FAILED(hr)) 
  {
	  //TODO: cleanup
	  //return hr;
	  return 0;
  }

   hr = shit->pSampleGrabber->SetBufferSamples(TRUE);
  if (FAILED(hr)) 
  {
	 //TODO: cleanup
	//return hr; 
	  return 0;
  }

  	
	hr = CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER,
							IID_IBaseFilter, reinterpret_cast<void**>(&shit->pNullRenderer));
	if (FAILED(hr)) 
	{
		char temp[1024];
		AMGetErrorText(hr, temp, 1024);
		fprintf(stderr,"%s\n",temp);
	 //TODO: cleanup
	//return hr; 
	  return 0;
	}

	hr = shit->pGraph->AddFilter(shit->pNullRenderer, L"NullRenderer");
	if (FAILED(hr)) 
	{
		char temp[1024];
		AMGetErrorText(hr, temp, 1024);
		fprintf(stderr,"%s\n",temp);
	 //TODO: cleanup
	//return hr; 
	  return 0;
	}

	return 1;
}


void destroyFilterGraph(AviShit* shit)
{
	if (shit->pMediaControl != 0)
	{
		shit->pMediaControl->Release();
		shit->pMediaControl = 0;
	}

	if (shit->pEvent != 0)
	{
		shit->pEvent->Release();
		shit->pEvent = 0;
	}

	if (shit->pGrabberBaseFilter != 0)
	{
		shit->pGrabberBaseFilter->Release();
		shit->pGrabberBaseFilter = 0;
	}

	if (shit->pSampleGrabber != 0)
	{
		shit->pSampleGrabber->Release();
		shit->pSampleGrabber = 0;
	}

	if (shit->pNullRenderer != 0)
	{
		shit->pNullRenderer->Release();
		shit->pNullRenderer = 0;
	}

	if (shit->srcFilter != 0)
	{
		shit->srcFilter->Release();
		shit->srcFilter = 0;
	}

	if (shit->pGraph != 0)
	{
		shit->pGraph->Release();
		shit->pGraph = 0;
	}
}

void closeAVI(MyInstancePtr inst)  						
{
	AviShit* shit = &inst->shit;

	destroyFilterGraph(shit);
}

int loadAvi(MyInstancePtr inst,FrameBufferType* out, StringType* filename)
{

	AviShit* shit = &inst->shit;

	if (!buildFilterGraph(shit))
		return 0;

	HRESULT hr;
	unsigned short buffer[1024];
	MultiByteToWideChar(CP_ACP,0,filename->text,strlen(filename->text)+1,buffer,1024);
	
	
	hr = shit->pGraph->AddSourceFilter(buffer, L"Source", &shit->srcFilter);
	if (FAILED(hr)) 
	{
		char temp[1024];
		AMGetErrorText(hr, temp, 1024);
		fprintf(stderr,"%s\n",temp);
	 //TODO: cleanup
	//return hr; 
	  return 0;
	}


	hr = ConnectFilters(shit->pGraph, shit->srcFilter, shit->pGrabberBaseFilter);
	if (FAILED(hr)) 
	{
		char temp[1024];
		AMGetErrorText(hr, temp, 1024);
		fprintf(stderr,"%s\n",temp);
	 //TODO: cleanup
	//return hr; 
	  return 0;
	}

  hr = ConnectFilters(shit->pGraph, shit->pGrabberBaseFilter, shit->pNullRenderer);
	if (FAILED(hr)) 
	{
		char temp[1024];
		AMGetErrorText(hr, temp, 1024);
		fprintf(stderr,"%s\n",temp);	 
	  return 0;
	}


  	AM_MEDIA_TYPE MediaType; 
	ZeroMemory(&MediaType,sizeof(MediaType)); 
	hr = shit->pSampleGrabber->GetConnectedMediaType(&MediaType); 
	if (FAILED(hr)) 
		return hr; 
	// Get a pointer to the video header. 
	VIDEOINFOHEADER *pVideoHeader = reinterpret_cast<VIDEOINFOHEADER*>(MediaType.pbFormat);
	if (pVideoHeader == NULL)
		return E_FAIL; 

	CoTaskMemFree(MediaType.pbFormat);
//	FreeMediaType(MediaType);
	
	// The video header contains the bitmap information. 
	// Copy it into a BITMAPINFO structure. 
	BITMAPINFOHEADER* BitmapInfo = &pVideoHeader->bmiHeader;

	FrameBufferAttributes newAttributes;
	newAttributes.xsize = BitmapInfo->biWidth;
	newAttributes.ysize = BitmapInfo->biHeight;

	framebuffer_changeAttributes(out, &newAttributes);

	//shit->pMediaControl->Run();
	
	return 1;
}


BOOL GetFormattedError(LPTSTR dest,int size)
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


int GrabAVIFrame(InstancePtr inst)
{
	MyInstancePtr my = inst->my;
	AviShit* shit = &my->shit;
	HRESULT hr;

	/*hr = shit->pMediaControl->Run();
	if (FAILED(hr)) 
		return hr; */

	OAFilterState state;
	hr = shit->pMediaControl->GetState(INFINITE, &state);
	if (FAILED(hr)) 
		return hr; 
	if (state != 2)
	{		
		shit->pMediaControl->Run();
	}

	long evCode = 0;
	hr = shit->pEvent->WaitForCompletion(0, &evCode); 
	if (evCode == EC_COMPLETE)
	{
		//TODO! much too slow
		closeAVI(inst->my);
		loadAvi(inst->my ,inst->out_result,inst->in_fileName);
		return S_OK;
	}

	long size = inst->out_result->xsize*inst->out_result->ysize;
	hr = shit->pSampleGrabber->GetCurrentBuffer(&size, (long*)inst->out_result->framebuffer);
	if (FAILED(hr))
	{
		char temp[1024];
		AMGetErrorText(hr,temp, 1024);
		fprintf(stderr,"%s\n",temp);
		return hr;
	}

	return S_OK;
}

int init(logT log_function)
{
	//hdd = DrawDibOpen();
	//AVIFileInit();	
	return 1;
}

void shutDown(void)
{
	//DrawDibClose(hdd);								
	//AVIFileExit();	
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
  AviShit* shit = &my->shit;

  shit->pEvent = 0;
  shit->pGrabberBaseFilter = 0;
  shit->pGraph = 0;
  shit->pMediaControl = 0;
  shit->pNullRenderer = 0;
  shit->pSampleGrabber = 0;
  shit->srcFilter = 0;
  
  CoInitialize(NULL);
 	
	my->oldFileName.text = static_cast<char*>(malloc(1));
	strcpy(my->oldFileName.text,"");
	
	return my;
}

void destruct(MyInstance* my)
{  
	destroyFilterGraph(&my->shit);

//	DeleteObject(my->shit.hBitmap);
	//my->shit.hBitmap = 0;
	//closeAVI(my);

	CoUninitialize();

	free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
	if (strcmp(my->oldFileName.text,inst->in_fileName->text) != 0)
    {
		closeAVI(my);		
		string_assign(&my->oldFileName,inst->in_fileName);
		
		if(!loadAvi(my, inst->out_result,inst->in_fileName))
		{
			fprintf(stderr,"Fehler beim Aviladen...\n");
			return;
		}
    }
	
//	if (my->shit.pgf != 0)
	GrabAVIFrame(inst);

}

