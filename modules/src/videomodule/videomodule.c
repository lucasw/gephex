#include "videomodule.h"
#include <windows.h>
#include <vfw.h>
#include <stdio.h>

static HDRAWDIB hdd;

typedef struct avishit_ {
	AVISTREAMINFO		psi;	
	PAVISTREAM		pavi;	
	PGETFRAME			pgf;
	int				mpf;	
	HBITMAP			hBitmap;
	HDC				hdc;
	int				lastframe;
	uint_32*		data;
	int				width;
	int				height;
} AviShit;


typedef struct _MyInstance {

	StringType oldFileName;
	AviShit shit;
	int frameCounter;

} MyInstance, *MyInstancePtr;


int createDIB(HDC* p_hdc,
			  HBITMAP* p_hBitmap,
			  uint_32** p_data,
			  int xsize, int ysize)
{
	BITMAPINFOHEADER	bmih;
	
	bmih.biSize = sizeof (BITMAPINFOHEADER);				
	bmih.biPlanes = 1;										
	bmih.biBitCount = 32;									
	bmih.biWidth = xsize;
	bmih.biHeight = ysize;
	bmih.biCompression = BI_RGB;

	*p_hdc = CreateCompatibleDC(0);
	
	*p_hBitmap = CreateDIBSection (*p_hdc, (BITMAPINFO*)&bmih,
								   DIB_RGB_COLORS, (void**) p_data, NULL, 0);

	SelectObject (*p_hdc, *p_hBitmap);

	return 1;
}

void destroyDIB(HBITMAP* p_hBitmap,
				HDC* p_hdc)
{
	DeleteObject(*p_hBitmap);
	*p_hBitmap = 0;

	SelectObject(*p_hdc, 0); //TODO
}

int loadAvi(MyInstancePtr inst, StringType* filename)
{
	
	// Opens The AVI Stream
	if (AVIStreamOpenFromFile(&inst->shit.pavi, filename->text,
		streamtypeVIDEO, 0, OF_READ, NULL) !=0)
	{		
		fprintf(stderr,"Failed To Open The AVI Stream");
		return 0;
	}
	
	AVIStreamInfo(inst->shit.pavi, &inst->shit.psi, sizeof(inst->shit.psi));					
	inst->shit.width=inst->shit.psi.rcFrame.right-inst->shit.psi.rcFrame.left;				
	inst->shit.height=inst->shit.psi.rcFrame.bottom-inst->shit.psi.rcFrame.top;				
	
	inst->shit.lastframe=AVIStreamLength(inst->shit.pavi);						
	
	inst->shit.mpf=AVIStreamSampleToTime(inst->shit.pavi,inst->shit.lastframe)
		/inst->shit.lastframe;	

	inst->shit.pgf = AVIStreamGetFrameOpen(inst->shit.pavi, NULL);						
	if (inst->shit.pgf==NULL)
	{
		fprintf(stderr,"Failed To Open The AVI Frame");
		//TODO: CloseAviStreamOpenFromFile...
		return 0;
	}
		
	createDIB(&inst->shit.hdc, &inst->shit.hBitmap,
			  &inst->shit.data, inst->shit.width, inst->shit.height);
	
	return 1;
}

void CloseAVI(MyInstancePtr inst)  						
{
	if (inst->shit.pgf != 0)
	{
		AVIStreamGetFrameClose(inst->shit.pgf);
		inst->shit.pgf = 0;
		AVIStreamRelease(inst->shit.pavi);							

		destroyDIB(&inst->shit.hBitmap, &inst->shit.hdc);
	}
}



void GrabAVIFrame(InstancePtr inst, int frame)							
{
	MyInstancePtr my = inst->my;
	char* pdata;
	LPBITMAPINFOHEADER lpbi;									// Holds The Bitmap Header Information
	lpbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(my->shit.pgf, frame%my->shit.lastframe);	// Grab Data From The AVI Stream

	if ( lpbi == 0 )
	{
		fprintf(stderr,"Could not AVIStreamGetFrame()!\n");		
	}
	else
	{
		// Pointer To Data Returned By AVIStreamGetFrame:
		pdata= ((char *)lpbi) + lpbi->biSize + lpbi->biClrUsed * sizeof(RGBQUAD);
	
		//Convert Data To Requested Bitmap Format
		DrawDibDraw (hdd, my->shit.hdc, 0, 0, my->shit.width, my->shit.height,
					 lpbi,pdata, 0, 0, my->shit.width, my->shit.height, 0);
	
		inst->out_result->framebuffer = my->shit.data;

		//inst->out_result->framebuffer = (uint_32*) pdata;
		//inst->out_result->data = (uint_32*) pdata;
		
	}
}

int init(logT log_function)
{
	hdd = DrawDibOpen();
	AVIFileInit();
	return 1;
}

void shutDown(void)
{
	DrawDibClose(hdd);								
	AVIFileExit();				
}


MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

 	my->frameCounter = -1;
	my->oldFileName.text = malloc(1);
	strcpy(my->oldFileName.text,"");

	my->shit.pgf = 0;

	//createDIB(&my->shit.hdc, &my->shit.hBitmap, &my->shit.data, WIDTH, HEIGHT);
	
	
	return my;
}

void destruct(MyInstance* my)
{  	
	CloseAVI(my);

	//destroyDIB(&my->shit.hBitmap, &my->shit.hdc);
	free(my);
}

void update(void* instance)
{
//  FrameBufferAttributes attribs;

  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

	if (strcmp(my->oldFileName.text,inst->in_fileName->text) != 0)
    {
		CloseAVI(my);		
		string_assign(&my->oldFileName,inst->in_fileName);
		my->frameCounter = -1;
		if(!loadAvi(my, inst->in_fileName))
		{
			fprintf(stderr,"Fehler beim Aviladen...\n");
			return;
		}

		//attribs.xsize = my->shit.height;
		//attribs.ysize = my->shit.width;
		//framebuffer_changeAttributes(inst->out_result, &attribs);
		inst->out_result->xsize = my->shit.width;
		inst->out_result->ysize = my->shit.height;
		inst->out_result->size = 0;
		inst->out_result->data = 0;

    }
	
	if (my->shit.pgf != 0)
		GrabAVIFrame(inst,++my->frameCounter);

}

