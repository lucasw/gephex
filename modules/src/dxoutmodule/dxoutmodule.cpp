#include "dxoutmodule.h"

#include <cstdio>

#include <windows.h>
#include <ddraw.h>
#include "../../../util/include/gfxutil.h"

#include "dualmonitor.h"

typedef struct _MyInstance {

  int*		 framebuf;
  HDC		 hdc;
  HBITMAP	 old;
  HBITMAP	 our;
  HWND		 hWnd;
  int		 width;
  int		 height;
  NumberType last;

  IDirectDraw7* pDD;

} MyInstance, *MyInstancePtr;


LRESULT CALLBACK winproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static const char* classname = "GE-PHEX_DX_OUTPUT_WINDOW";
static HINSTANCE hInstance = 0;

int init(logT log_function)
{
  WNDCLASSEX winclass;
	
  hInstance  = GetModuleHandle(NULL);
	
  winclass.cbSize = sizeof(WNDCLASSEX);
  winclass.style  = CS_DBLCLKS;
  winclass.lpfnWndProc = &winproc;
  winclass.cbClsExtra = 0;
  winclass.cbWndExtra = 0;
  winclass.hInstance = hInstance;
  winclass.hIcon = LoadIcon(NULL,IDI_WINLOGO);
  winclass.hCursor = LoadCursor(NULL,IDC_NO);
  winclass.hbrBackground = NULL;
  winclass.lpszMenuName = NULL;
  winclass.lpszClassName = classname;
  winclass.hIconSm = NULL;
	
  if (!RegisterClassEx(&winclass))
    {
	  WindowHandler::displayError();
      return 0;
    }

  return 1;
}

void shutDown(void)
{	
  if (!UnregisterClass(classname,hInstance))
    {
	  WindowHandler::displayError();
    }
}


int createWindow(MyInstance* inst, int preview)
{

	if(FAILED(WindowHandler::create(inst->width, inst->height, preview)))
		MessageBox(NULL, "Couldn't initialize windowHandle", "FICKEN", MB_OK);

	inst->hWnd = WindowHandler::hWnd();	

	if(preview)
		MaximizeWindowOnMonitor(inst->hWnd,1);

	ShowWindow(inst->hWnd,SW_SHOW);
	
	return 1;
}

void killWindow(MyInstance* inst)
{
	if(!WindowHandler::destroy())
		MessageBox(NULL, "Destruction of Window fucked up", "Ficken", MB_OK);;
}

int createFramebuffer(MyInstance* inst)
{
  if (inst->hdc == 0 )
    {      
	  BITMAPINFO bitmapinfo;	  
	  inst->hdc=CreateCompatibleDC(NULL);	

      bitmapinfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
      bitmapinfo.bmiHeader.biWidth=inst->width;
      bitmapinfo.bmiHeader.biHeight=inst->height; // - = top-down 
      bitmapinfo.bmiHeader.biPlanes=1;
      bitmapinfo.bmiHeader.biBitCount=32;
      bitmapinfo.bmiHeader.biCompression=BI_RGB;
      bitmapinfo.bmiHeader.biSizeImage=0;
      bitmapinfo.bmiHeader.biClrUsed=0;//256;
      bitmapinfo.bmiHeader.biClrImportant=0;//256;*/
      inst->our=CreateDIBSection(inst->hdc,&bitmapinfo,DIB_RGB_COLORS,(void**)&inst->framebuf,0,0);	  
      
      inst->old= (HBITMAP) SelectObject(inst->hdc,inst->our);      
    }
	
  return 1;
}

int killFramebuffer(MyInstance* inst)
{
  int result = (SelectObject(inst->hdc,inst->old) == 0);
  result = result && DeleteDC(inst->hdc);
  result = result && DeleteObject(inst->our);
  inst->hdc = 0;
  inst->our = 0;
  return result;
}

void blit(InstancePtr inst)
{
  HDC hdc;
  PAINTSTRUCT PtStr;
	
  InvalidateRgn(inst->my->hWnd,0,FALSE); //TODO
  hdc = BeginPaint(inst->my->hWnd,&PtStr);
    
  memcpy(inst->my->framebuf,inst->in_in->framebuffer,
		inst->in_in->xsize*inst->in_in->ysize*sizeof(int));
	
  BitBlt(hdc,0,0,inst->my->width,inst->my->height,inst->my->hdc,0,0,SRCCOPY);
	
  EndPaint(inst->my->hWnd,&PtStr);
}



MyInstance* construct()
{
  HRESULT hr;
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
  int result;

  my->width = 640;
  my->height = 480;
  my->our = 0;
  my->old = 0;
  my->framebuf = 0;
  my->hdc = 0;
  my->hWnd = 0;
  my->last.number = 0;
	
  result = createWindow(my, FALSE);
  
  if (result == 0)
    {
      free(my);
      return 0;
    }
  
  result = createFramebuffer(my);
  
  if (result == 0)
    {
      killWindow(my);
      free(my);
      return 0;
    }
  
  
  hr = DirectDrawCreateEx( NULL, (void **)&my->pDD, IID_IDirectDraw7, NULL );
  if (FAILED(hr))
  {
	 killFramebuffer(my);
	 killWindow(my);
     free(my);
     return 0;
  }

  hr = my->pDD->SetCooperativeLevel( my->hWnd, DDSCL_NORMAL );
  if (FAILED(hr))
  {
	 my->pDD->Release();
	 killFramebuffer(my);
	 killWindow(my);
     free(my);
     return 0;
  }

  //my->pDD->SetDisplayMode(640, 480, 32,0,0); 
  if (FAILED(hr))
  {
	 my->pDD->Release();
	 killFramebuffer(my);
	 killWindow(my);
     free(my);
     return 0;
  }
  
  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  if (!killFramebuffer(my))
    {
      fprintf(stderr,"Konnte Framebuffer nicht loeschen");
    }
  
  killWindow(my);

  free(my);
}

void update(void* instance)
{
	InstancePtr inst = (InstancePtr) instance;
	MyInstancePtr my = inst->my;
	// Add your effect here!
	MSG msg;
	
	//printf("last number: %d, prev number: %d\n", inst->in_preview->number, my->last.number);
	if(inst->in_preview->number != my->last.number)
	{
		//killFramebuffer(my);
		killWindow(my);
		createWindow(my, inst->in_preview->number);
		//createFramebuffer(my);
		my->last.number = inst->in_preview->number;
	}

	if (inst->in_in->xsize != my->width || inst->in_in->ysize != my->height)
	{
		killWindow(my);
		killFramebuffer(my);
		my->width = inst->in_in->xsize;
		my->height = inst->in_in->ysize;
		createWindow(my, inst->in_preview->number);
		createFramebuffer(my);
	}
		
	blit(inst);
	
	if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
    {
		if (msg.message==WM_QUIT)				
		{
			//killFramebuffer(inst);
			//killWindow(inst);
		}
		else
		{
			TranslateMessage(&msg);				
			DispatchMessage(&msg);				
		}
    }
}

LRESULT CALLBACK winproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int active; //TODO
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}
			
			return 0;								// Return To The Message Loop
		}
		
	case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
			case SC_SCREENSAVE:					// Screensaver Trying To Start?
			case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}
		
	case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		
	case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			//			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}
		
	case WM_KEYUP:								// Has A Key Been Released?
		{
			//			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}
		
	case WM_SIZE:								// Resize The OpenGL Window
		{
			//			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
		
	case WM_PAINT:
		{
			//blit(instance);
		}
	}
	
	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

