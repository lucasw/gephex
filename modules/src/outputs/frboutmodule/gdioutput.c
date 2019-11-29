/* GDI Output driver.
  Copyright (C) 2003 Georg Seidel
  This file is part of GePhex.

  GePhex is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.
  
  GePhex is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.
    
  You should have received a copy of the GNU General Public
  License along with GePhex; if not, write to the Free
  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  02111-1307 USA.  
      
  You can reach me via email: georg.seidel@web.de
*/
#include "gdioutput.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <windows.h>

#include "outputdriver.h"
#include "multimonitor.h"
#include "libscale.h"

static const char* classname = "GePhex_Output";

#define EPS 0.001

//-----------------------------------------------------------------------

struct DriverInstance {

  HWND       hwnd;
  int        win_xsize;
  int        win_ysize;

  unsigned char*   data;
  int		 data_size;
  ls_adjust_pal pal;
};

//-----------------------------------------------------------------------

static struct DriverInstance* GDI_new_instance(const char* server_name,
											   int xpos, int ypos,
                                               int width, int height, int mmx_supported,
											   char* error_text, int buflen);

static void GDI_destroy(struct DriverInstance* sh);

static int GDI_resize(struct DriverInstance* sh,int width, int height,
		  		      char* error_text, int text_len);

static int GDI_blit(struct DriverInstance* sh,
                    const unsigned char* fb, int width, int height,
					struct blit_params* params,
                    char* error_text, int buflen);

static int GDI_window_pos(struct DriverInstance* self, int* xpos, int* ypos,
	                     char* error_text, int text_len);

static int GDI_frame(struct DriverInstance* self, int frame_visible,
		          	 char* error_text, int text_len);

static int GDI_always_on_top(struct DriverInstance* self, int on_top,
                             char* error_text, int text_len);

static int GDI_to_monitor(struct DriverInstance* self, int monitor,
	                      char* error_text, int text_len);

//-----------------------------------------------------------------------

static LRESULT CALLBACK winproc(HWND hwnd, UINT uMsg, 
                                WPARAM wParam, LPARAM lParam);

static int create_window(HWND* hwnd, int xpos, int ypos,
						 char* error_text, int text_len);

static int kill_window(HWND hwnd);

static int set_top(HWND hwnd, int top_most, char* error_text, int text_len);

static void get_error_text(char* buffer, int len);

static int window_get_rect(HWND hwnd, int* xpos, int* ypos, 
						  int* xsize, int* ysize, char* error_text, int text_len);

static int set_caption(HWND hwnd, int xpos, int ypos, int xsize, int ysize, int caption,
					   char* error_text, int text_len);

static int window_resize(HWND hwnd, int xsize, int ysize, char* error_text, int text_len);

static int calc_win_size(HWND hwnd, int in_xsize, int in_ysize, int* xsize, int* ysize,
						 char* error_text, int text_len);


//-----------------------------------------------------------------------

struct OutputDriver* GDI_get_driver()
{
  struct OutputDriver* drv = (struct OutputDriver*) malloc(sizeof(*drv));

  if (drv == 0)
    return 0;

  drv->new_instance  = GDI_new_instance;
  drv->destroy       = GDI_destroy;
  drv->resize        = GDI_resize;
  drv->blit          = GDI_blit;
  drv->window_pos    = GDI_window_pos;
  drv->frame         = GDI_frame;
  drv->always_on_top = GDI_always_on_top;
  drv->to_monitor    = GDI_to_monitor;

  drv->inst          = 0;
  return drv;
}

int GDI_init(char* error_text, int text_len)
{
    WNDCLASSEX winclass;
    HINSTANCE hInstance    = GetModuleHandle(NULL);	
    
    winclass.cbSize        = sizeof(WNDCLASSEX);
    winclass.style         = 0;
    winclass.lpfnWndProc   = &winproc;
    winclass.cbClsExtra    = 0;
    winclass.cbWndExtra    = 0;
    winclass.hInstance     = hInstance;
    winclass.hIcon         = LoadIcon(NULL,IDI_WINLOGO);
    winclass.hCursor       = LoadCursor(NULL,IDC_NO);
    winclass.hbrBackground = NULL;
    winclass.lpszMenuName  = NULL;
    winclass.lpszClassName = classname;
    winclass.hIconSm       = NULL;
    
    if (!RegisterClassEx(&winclass))
    {        
        get_error_text(error_text, text_len);        
        return 0;
    }

	if (!mm_init(error_text, text_len))
	{
		return 0;
	}
    
    return 1;
}

int GDI_shutdown(char* error_text, int text_len)
{   
	HINSTANCE hInstance = GetModuleHandle(NULL);

    if (!UnregisterClass(classname, hInstance))
    {        
        get_error_text(error_text, text_len);
		return 0;
    }

	return 1;
}


//-----------------------------------------------------------------------


static struct DriverInstance*
GDI_new_instance(const char* server_name,
				 int xpos, int ypos,
                 int width, int height, int mmx_support,
                 char* error_text, int buflen)
{
  struct DriverInstance* sh = (struct DriverInstance*) malloc(sizeof(*sh));

  if (sh == 0) {
	  _snprintf(error_text, buflen, "GDI_new_instance: Could not allocate memory");
	  return 0;
  }

  sh->win_xsize = width;
  sh->win_ysize = height;
  if (!create_window(&sh->hwnd, xpos, ypos, error_text, buflen))
  {
	  free(sh);
	  return 0;
  }

  window_resize(sh->hwnd, sh->win_xsize, sh->win_ysize, error_text, buflen);

  sh->data = 0;

  return sh;
}

static void GDI_destroy(struct DriverInstance* sh)
{
  if (sh->data)  
	  free(sh->data);

  kill_window(sh->hwnd);
  free(sh);
}

static int GDI_resize(struct DriverInstance* sh, int width, int height,
					  char* error_text, int text_len)
{ 
  if (sh->win_xsize != width || sh->win_ysize != height)
    {
      sh->win_xsize = width;
      sh->win_ysize = height;

      if (!window_resize(sh->hwnd, width, height, error_text, text_len))
        return 0;
    }
  return 1;
}

static int GDI_blit(struct DriverInstance* sh,
                    const unsigned char* fb,
                    int width, int height,
                    struct blit_params* params,
                    char* error_text, int text_len)
{
  
  HDC hdc;
  PAINTSTRUCT PtStr;
  BITMAPINFO bitmapinfo;
  int result = 1;
    
  int win_xpos;
  int win_xsize;

  int needs_adjust = (fabs(params->brightness-0.5) > EPS 
                      || fabs(params->contrast-1.0) > EPS
                      || fabs(params->gamma-1.0) > EPS);

  const unsigned char* bfb;
  int raster_op;

  if (needs_adjust)
  {
	  int size = width*height*4;
	  if (sh->data == 0)
	  {
		  sh->data_size = size;
		  sh->data = malloc(size);
	  }
	  else if (sh->data_size < size)
	  {
		  free(sh->data);
		  sh->data_size = size;
		  sh->data = malloc(size);
	  }
	  ls_set_adjustment(sh->pal, params->brightness, params->contrast,
                     params->gamma, params->invert);

	  ls_cpy_adjust((uint_32*)sh->data, (const uint_32*)fb, width, height, sh->pal);
	  bfb = sh->data;
  }
  else
  {
	  if (sh->data)
	  {
		  free(sh->data);
		  sh->data = 0;
	  }

	  bfb = fb;
  }

  if (params->mirrorx) {
  	    win_xpos  = sh->win_xsize;
		win_xsize = -sh->win_xsize;
	}
	else {
		win_xpos  = 0;
		win_xsize = sh->win_xsize;
	}

	bitmapinfo.bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	bitmapinfo.bmiHeader.biWidth		= width;
	if (params->mirrory)
		bitmapinfo.bmiHeader.biHeight   = height; // - = top-down 
	else
		bitmapinfo.bmiHeader.biHeight	= -height; // - = top-down 
	bitmapinfo.bmiHeader.biPlanes		= 1;
	bitmapinfo.bmiHeader.biBitCount     = 32;
	bitmapinfo.bmiHeader.biCompression  = BI_RGB;
	bitmapinfo.bmiHeader.biSizeImage    = 0;
	bitmapinfo.bmiHeader.biClrUsed      = 0;//256;
	bitmapinfo.bmiHeader.biClrImportant = 0;//256;
		
	InvalidateRgn(sh->hwnd,0,FALSE); //TODO
    hdc = BeginPaint(sh->hwnd,&PtStr);

	if (params->invert && !needs_adjust)
		raster_op = NOTSRCCOPY;
	else
		raster_op = SRCCOPY;

	result = StretchDIBits(hdc,
		                   win_xpos, 0, win_xsize, sh->win_ysize, 
		                   0, 0, width, height, bfb,
		                   &bitmapinfo, DIB_RGB_COLORS, raster_op);	

    if (result == GDI_ERROR) {
		get_error_text(error_text, text_len);
	}
	    
    EndPaint(sh->hwnd, &PtStr);

	{
		MSG msg;
		
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))   
		{
			if (msg.message==WM_QUIT)               
			{
				//kill_window(inst);
			}
			else
			{
				TranslateMessage(&msg);             
				DispatchMessage(&msg);              
			}
		}
	}

	return result;
}

static int GDI_window_pos(struct DriverInstance* self, int* xpos, int* ypos,
  	                      char* error_text, int text_len)
{
	return window_get_rect(self->hwnd, xpos, ypos, 0, 0, error_text, text_len);
}

static int GDI_frame(struct DriverInstance* self, int frame_visible,
 		          	 char* error_text, int text_len)
{
	int x, y;	
	int result;

	result = window_get_rect(self->hwnd, &x, &y, 0, 0, error_text, text_len);
	if (!result)
		return 0;

	return set_caption(self->hwnd,x,y,self->win_xsize,self->win_ysize,
		               frame_visible, error_text, text_len);
}

static int GDI_always_on_top(struct DriverInstance* self, int on_top,
                             char* error_text, int text_len)
{
	return set_top(self->hwnd, on_top, error_text, text_len);
}

static int GDI_to_monitor(struct DriverInstance* self, int monitor,
	                      char* error_text, int text_len)
{
	int x = 0;
	int y = 0;

	window_get_rect(self->hwnd, &x, &y, 0, 0, error_text, text_len);

	if (!mm_move_to_monitor(self->hwnd, monitor, error_text, text_len))
		return 0;

    SetWindowPos(self->hwnd, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOREPOSITION);

	return 1;
}

//-----------------------------------------------------------------------

static int create_window(HWND* hwnd, int xpos, int ypos,
						 char* error_text, int text_len)
{
    HINSTANCE hInstance  = GetModuleHandle(NULL);
    const char* progname = "GE-PHEX Output";

     *hwnd = CreateWindow(
            classname,
            progname,
			WS_POPUP|WS_VISIBLE,
			xpos,
            ypos,
            1,
            1,
            NULL,
            NULL,
            hInstance,
            NULL);                
    
	if (*hwnd == 0)
        {   			
            get_error_text(error_text, text_len);            
            return 0;
        }	    
    
	ShowWindow(*hwnd,SW_SHOW);
    
    return 1;
}

static int kill_window(HWND hwnd)
{
    return DestroyWindow(hwnd);
}

static void get_error_text(char* buffer, int len)
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
    _snprintf(buffer, len, "%s", (LPCTSTR) lpMsgBuf);
    LocalFree( lpMsgBuf );
}

static int window_resize(HWND hwnd, int xsize, int ysize, char* error_text, int text_len) {

	int win_xsize = xsize;
	int win_ysize = ysize;
  
	if (!calc_win_size(hwnd, xsize, ysize, &win_xsize, &win_ysize, error_text, text_len))
		return 0;

	if (!SetWindowPos(hwnd, 0, 0, 0, win_xsize, win_ysize,
			          SWP_NOOWNERZORDER|SWP_NOMOVE)) {			
			get_error_text(error_text, text_len);
			return 0;
	}

	return 1;
}

static int calc_win_size(HWND hwnd, int in_xsize, int in_ysize, int* xsize, int* ysize,
						  char* error_text, int text_len)
{
	int style = GetWindowLong(hwnd, GWL_STYLE);
	RECT r;

	r.top    = 0;
	r.left   = 0;
	r.right  = in_xsize;
	r.bottom = in_ysize;

	if (!AdjustWindowRect(&r, style, FALSE)) {		
		get_error_text(error_text, text_len);
		return 0;
	}

	*xsize = r.right  - r.left;
	*ysize = r.bottom - r.top;
	return 1;
}

static int set_top(HWND hwnd, int top_most, char* error_text, int text_len)
{
	HWND insert_after;
	
	if (top_most)
		insert_after = HWND_TOPMOST;
	else
		insert_after = HWND_NOTOPMOST;
	
	if (!SetWindowPos(hwnd, insert_after, 0, 0, 0, 0,
		              SWP_NOMOVE|SWP_NOSIZE|SWP_NOCOPYBITS|SWP_NOACTIVATE))
	{
		get_error_text(error_text, text_len);
		return 0;
	}
	return 1;
}

static LRESULT CALLBACK winproc(HWND hwnd, UINT uMsg, WPARAM wParam,
						 LPARAM lParam)
{    
    switch (uMsg)           // Check For Windows Messages
    {
       
    case WM_SYSCOMMAND:     // Intercept System Commands
        {
            switch (wParam)     // Check System Calls
            {
             case SC_SCREENSAVE: // Screensaver Trying To Start?
            //case SC_MONITORPOWER:   // Monitor Trying To Enter Powersave?
                return 0;       // Prevent From Happening
            }            
        } break;
	}
    
    // Pass All Unhandled Messages To DefWindowProc
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

static int window_get_rect(HWND hwnd, int* xpos, int* ypos,
						   int* xsize, int* ysize,
						  char* error_text, int text_len)
{
	RECT r;
	if (!GetWindowRect(hwnd, &r))
	{		
		get_error_text(error_text, text_len);
		return 0;
	}

	*xpos = r.left;
	*ypos = r.top;
	if (xsize)
		*xsize = r.right - r.left;
	if (ysize)
		*ysize = abs(r.top - r.bottom);

	return 1;
}

static int set_caption(HWND hwnd, int xpos, int ypos, int xsize, int ysize, int caption,
					   char* error_text, int text_len)
{
		int style = GetWindowLong(hwnd, GWL_STYLE);
		int win_xpos  = max(0, xpos);
		int win_ypos  = max(0, ypos);
		int win_xsize = xsize;
		int win_ysize = ysize;

		if (caption) {
			style |= WS_CAPTION;
		}
		else 
			style &= ~WS_CAPTION;			

		if (!SetWindowLong(hwnd, GWL_STYLE,  style)) {			
			get_error_text(error_text, text_len);
			return 0;
		}

		if (!calc_win_size(hwnd, xsize, ysize, &win_xsize, &win_ysize,
			               error_text, text_len)) {
			return 0;
		}
		
		if (!SetWindowPos(hwnd, 0, win_xpos, win_ypos, win_xsize, win_ysize,
			              SWP_FRAMECHANGED|SWP_NOOWNERZORDER)) {
			get_error_text(error_text, text_len);
			return 0;
		}

		return 1;
}
