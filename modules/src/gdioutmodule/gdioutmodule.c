#include "gdioutmodule.h"

#include <stdio.h>
#include <windows.h>

#include "dualmonitor.h"

typedef struct _MyInstance {

  uint_32*		 framebuf;
  HDC		 hdc;
  HBITMAP	 old;
  HBITMAP	 our;
  HWND		 hWnd;
  int		 width;
  int		 height;
  NumberType last;

  FrameBufferType* scaledFrb;

} MyInstance, *MyInstancePtr;


LRESULT CALLBACK winproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static const char* classname = "GE-PHEX_GDI_OUTPUT_WINDOW";
static HINSTANCE hInstance = 0;

void displayError()
{
  LPVOID lpMsgBuf;
  FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
		);
  fprintf(stderr,"Fehler: %s\n",(LPCTSTR)lpMsgBuf);
  LocalFree( lpMsgBuf );
}


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
      displayError();
      return 0;
    }

  return 1;
}

void shutDown(void)
{	
  if (!UnregisterClass(classname,hInstance))
    {
      displayError();
    }
}


int createWindow(MyInstance* inst, int preview)
{
  HINSTANCE hInstance  = GetModuleHandle(NULL);
  const char* progname = "GE-PHEX Output";

  if(preview == 0)
    {
      inst->hWnd=CreateWindow(
			      classname,
			      progname,
			      WS_POPUP/*WS_SYSMENU|WS_CAPTION|WS_BORDER|WS_OVERLAPPED|WS_VISIBLE|WS_MINIMIZEBOX*/,
			      CW_USEDEFAULT,
			      0,
			      inst->width,
			      inst->height,
			      NULL,
			      NULL,
			      hInstance,
			      NULL);
	
      if (inst->hWnd == 0)
	{
	  displayError();
	  return 0;
	}
	
      MaximizeWindowOnMonitor(inst->hWnd,1);
    }
  else
    {
      inst->hWnd=CreateWindowEx(
				WS_EX_TOPMOST,
				classname,
				progname,
				WS_POPUP|WS_CAPTION|WS_THICKFRAME|WS_BORDER|WS_OVERLAPPED|WS_VISIBLE,
				CW_USEDEFAULT,
				0,
				inst->width,
				inst->height,
				NULL,
				NULL,
				hInstance,
				NULL);
	  
      if (inst->hWnd == 0)
	{
	  displayError();
	  return 0;
	}
    }
  ShowWindow(inst->hWnd,SW_SHOW);
	
  return 1;
}

int killWindow(MyInstance* inst)
{
  return DestroyWindow(inst->hWnd);
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
      inst->our=CreateDIBSection(inst->hdc,&bitmapinfo,DIB_RGB_COLORS,&inst->framebuf,0,0);	  
      
      inst->old=SelectObject(inst->hdc,inst->our);      
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

  MyInstance* my = inst->my;
  FrameBufferAttributes attribs;
	
  InvalidateRgn(inst->my->hWnd,0,FALSE); //TODO
  hdc = BeginPaint(inst->my->hWnd,&PtStr);

  if (inst->my->height != inst->in_in->ysize
      || inst->my->width != inst->in_in->xsize)
    {
      //input needs to be scaled

      if (my->scaledFrb == 0)
	my->scaledFrb = framebuffer_newInstance();
	  
      attribs.xsize = inst->my->width;
      attribs.ysize = inst->my->height;

      framebuffer_convertType(my->scaledFrb, inst->in_in, &attribs);

      memcpy(my->framebuf,my->scaledFrb->framebuffer,
	     inst->my->width*inst->my->height*sizeof(uint_32));	  
    }
  else
    {
      if (my->scaledFrb != 0)
	{
	  framebuffer_deleteInstance(my->scaledFrb);
	  my->scaledFrb = 0;
	}

      memcpy(my->framebuf,inst->in_in->framebuffer,
	     inst->in_in->xsize*inst->in_in->ysize*sizeof(uint_32));
    }
  
	
  BitBlt(hdc,0,0,inst->my->width,inst->my->height,inst->my->hdc,0,0,SRCCOPY);
	
  EndPaint(inst->my->hWnd,&PtStr);
}



MyInstance* construct()
{
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

  my->scaledFrb = 0;
	
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


  return my;
}

void destruct(MyInstance* my)
{
  if (my->scaledFrb != 0)
    {
      framebuffer_deleteInstance(my->scaledFrb);
      my->scaledFrb = 0;
    }

  if (!killFramebuffer(my))
    {
      fprintf(stderr,"Konnte Framebuffer nicht loeschen");
    }
  
  if (!killWindow(my))
    {
      fprintf(stderr,"Konnte Fenster nicht schliessen");
    }
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  // Add your effect here!
  MSG msg;

  int new_xsize, new_ysize;
	
  //printf("last number: %d, prev number: %d\n", inst->in_preview->number, my->last.number);
  if(inst->in_preview->number != my->last.number)
    {
      //killFramebuffer(my);
      killWindow(my);
      createWindow(my, inst->in_preview->number);
      //createFramebuffer(my);
      my->last.number = inst->in_preview->number;
    }

  if (inst->in_xsize->number == 0 || inst->in_ysize->number == 0)
    {
      new_xsize = inst->in_in->xsize;
      new_ysize = inst->in_in->ysize;
    }
  else
    {
      new_xsize = inst->in_xsize->number;
      new_ysize = inst->in_ysize->number;		
    }
  if (new_xsize != my->width || new_ysize != my->height)
    {
      killWindow(my);
      killFramebuffer(my);
      my->width = new_xsize;
      my->height = new_ysize;
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
  switch (uMsg)			// Check For Windows Messages
    {
    case WM_ACTIVATE:		// Watch For Window Activate Message
      {
	if (!HIWORD(wParam))	// Check Minimization State
	  {
	    active=TRUE;	// Program Is Active
	  }
	else
	  {
	    active=FALSE;	// Program Is No Longer Active
	  }
			
	return 0;		// Return To The Message Loop
      }
		
    case WM_SYSCOMMAND:		// Intercept System Commands
      {
	switch (wParam)		// Check System Calls
	  {
	  case SC_SCREENSAVE:	// Screensaver Trying To Start?
	  case SC_MONITORPOWER:	// Monitor Trying To Enter Powersave?
	    return 0;		// Prevent From Happening
	  }
	break;			// Exit
      }
		
    case WM_CLOSE:		// Did We Receive A Close Message?
      {
	PostQuitMessage(0);	// Send A Quit Message
	return 0;
      }
		
    case WM_KEYDOWN:	        // Is A Key Being Held Down?
      {
	// keys[wParam] = TRUE;
	// If So, Mark It As TRUE
	return 0;
      }
		
    case WM_KEYUP:             // Has A Key Been Released?
      {
	//  keys[wParam] = FALSE;
	// If So, Mark It As FALSE
	return 0;
      }
		
    case WM_SIZE:             // Resize the Window
      {
	//ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));
	// LoWord=Width, HiWord=Height
	return 0;
      }
		
    case WM_PAINT:
      {
	//blit(instance);
      }
    }
	
  // Pass All Unhandled Messages To DefWindowProc
  return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
