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

#include <stdio.h>

#include <windows.h>
#include <gl\gl.h>		
#include <gl\glu.h>			

#include "glutil.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

static HDC		 hDC=NULL;
static HGLRC	 hRC=NULL;		
static HWND		 hWnd=NULL;		
static HINSTANCE hInstance;		

static BOOL	keys[256];			
static BOOL	active=TRUE;		
static BOOL	fullscreen=TRUE;	
static BOOL	done=FALSE;

static LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	

static int s_xsize;
static int s_ysize;

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		
{
  if (height == 0)
    {
      height=1;										
    }

  glViewport(0,0,width,height);						

  glMatrixMode(GL_PROJECTION);						
  glLoadIdentity();									

//   Calculate The Aspect Ratio Of The Window
  gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

  glMatrixMode(GL_MODELVIEW);						
  glLoadIdentity();									
}

int InitGL(GLvoid)										
{
  //glShadeModel(GL_SMOOTH);							
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				
  //glClearDepth(1.0f);								
  //glEnable(GL_DEPTH_TEST);							
  //glDepthFunc(GL_LEQUAL);							
  //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  return TRUE;										
}


GLvoid KillGLWindow(GLvoid)								
{
  if (fullscreen)										
    {
      ChangeDisplaySettings(NULL,0);					
      ShowCursor(TRUE);								
    }

  if (hRC)											
    {
      if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
	{
	  MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
	}

      if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
	{
	  MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
	}
      hRC=NULL;										// Set RC To NULL
    }

  if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
    {
      MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
      hDC=NULL;										// Set DC To NULL
    }

  if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
    {
      MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
      hWnd=NULL;										// Set hWnd To NULL
    }

  if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
    {
      MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
      hInstance=NULL;									// Set hInstance To NULL
    }
}


/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(const char* title, int width, int height, int bits, BOOL fullscreenflag)
{
  GLuint		PixelFormat;			// Holds The Results After Searching For A Match
  WNDCLASS	wc;						// Windows Class Structure
  DWORD		dwExStyle;				// Window Extended Style
  DWORD		dwStyle;				// Window Style
  RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
  static	PIXELFORMATDESCRIPTOR pfd;

  WindowRect.left=(long)0;			// Set Left Value To 0
  WindowRect.right=(long)width;		// Set Right Value To Requested Width
  WindowRect.top=(long)0;				// Set Top Value To 0
  WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

  fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag
	

  hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
  wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
  wc.lpfnWndProc	= (WNDPROC) WndProc;					// WndProc Handles Messages
  wc.cbClsExtra		= 0;									// No Extra Window Data
  wc.cbWndExtra		= 0;									// No Extra Window Data
  wc.hInstance		= hInstance;							// Set The Instance
  wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
  wc.hCursor		= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
  wc.hbrBackground	= NULL;									// No Background Required For GL
  wc.lpszMenuName	= NULL;									// We Don't Want A Menu
  wc.lpszClassName	= "OpenGL";								// Set The Class Name	


  if (!RegisterClass(&wc))									// Attempt To Register The Window Class
    {
      MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
      return FALSE;											// Return FALSE
    }
	
  if (fullscreen)												// Attempt Fullscreen Mode?
    {
      DEVMODE dmScreenSettings;								// Device Mode
      memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
      dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
      dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
      dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
      dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
      dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

      // Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
      if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
	{
	  // If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
	  if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
	    {
	      fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
	    }
	  else
	    {
				// Pop Up A Message Box Letting User Know The Program Is Closing.
	      MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
	      return FALSE;									// Return FALSE
	    }
	}
    }

  if (fullscreen)												// Are We Still In Fullscreen Mode?
    {
      dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
      dwStyle=WS_POPUP;										// Windows Style
      ShowCursor(FALSE);										// Hide Mouse Pointer
    }
  else
    {
      dwExStyle = 0;//WS_CHILD;//WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
      dwStyle=WS_POPUP;//WS_OVERLAPPEDWINDOW;							// Windows Style
    }

  AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

  // Create The Window
  if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
				"OpenGL",							// Class Name
				title,								// Window Title
				dwStyle |							// Defined Window Style
				WS_CLIPSIBLINGS |					// Required Window Style
				WS_CLIPCHILDREN,					// Required Window Style
				0, 0,								// Window Position
				WindowRect.right-WindowRect.left,	// Calculate Window Width
				WindowRect.bottom-WindowRect.top,	// Calculate Window Height
				NULL,								// No Parent Window
				NULL,								// No Menu
				hInstance,							// Instance
				NULL)))								// Dont Pass Anything To WM_CREATE
    {
      KillGLWindow();								// Reset The Display
      MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
      return FALSE;								// Return FALSE
    }

  // put window onto 2nd monitor
  /*{
	char buffer[128];
    int r = maximize_window_on_monitor(hWnd, 1, buffer, sizeof(buffer));
	if (!r)
		fprintf(stderr, buffer);
  }*/
	

  pfd.nSize= sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion= 1;
  pfd.dwFlags= PFD_DRAW_TO_WINDOW |	PFD_SUPPORT_OPENGL |
			   PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED;
  pfd.iPixelType= PFD_TYPE_RGBA;
  pfd.cColorBits= bits;
  pfd.cRedBits=0;
  pfd.cRedShift=0;
  pfd.cGreenBits=0;
  pfd.cGreenShift=0;
  pfd.cBlueBits=0;
  pfd.cBlueShift=0;
  pfd.cAlphaBits=0;
  pfd.cAlphaShift=0;
  pfd.cAccumBits=0;
  pfd.cAccumRedBits=0;
  pfd.cAccumGreenBits=0;
  pfd.cAccumBlueBits=0;
  pfd.cAccumAlphaBits=0;
  pfd.cDepthBits=0; //vorher 16
  pfd.cStencilBits=0;
  pfd.cAuxBuffers=0;
  pfd.iLayerType=PFD_MAIN_PLANE;
  pfd.bReserved=0;
  pfd.dwLayerMask=0;
  pfd.dwVisibleMask=0;
  pfd.dwDamageMask=0;

	
  if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
    {
      KillGLWindow();								// Reset The Display
      MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
      return FALSE;								// Return FALSE
    }

  if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
    {
      KillGLWindow();								// Reset The Display
      MessageBox(NULL,"Can't Find A Suitable PixelFormat.",
		         "ERROR",MB_OK | MB_ICONEXCLAMATION);
      return FALSE;								// Return FALSE
    }

  if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
    {
      KillGLWindow();								// Reset The Display
      MessageBox(NULL,"Can't Set The PixelFormat.", "ERROR",
		          MB_OK|MB_ICONEXCLAMATION);
      return FALSE;								// Return FALSE
    }

  if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
    {
      KillGLWindow();								// Reset The Display
      MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
      return FALSE;								// Return FALSE
    }

  if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
    {
      KillGLWindow();								// Reset The Display
      MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
      return FALSE;								// Return FALSE
    }

  ShowWindow(hWnd,SW_SHOW);						// Show The Window
  //SetForegroundWindow(hWnd);						// Slightly Higher Priority
  //SetFocus(hWnd);									// Sets Keyboard Focus To The Window
  ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

  if (!InitGL())									// Initialize Our Newly Created GL Window
    {
      KillGLWindow();								// Reset The Display
      MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
      return FALSE;								// Return FALSE
    }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
  return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
				UINT	uMsg,			// Message For This Window
				WPARAM	wParam,			// Additional Message Information
				LPARAM	lParam)			// Additional Message Information
{
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
	keys[wParam] = TRUE;					// If So, Mark It As TRUE
	return 0;								// Jump Back
      }

    case WM_KEYUP:								// Has A Key Been Released?
      {
	keys[wParam] = FALSE;					// If So, Mark It As FALSE
	return 0;								// Jump Back
      }

    case WM_SIZE:								// Resize The OpenGL Window
      {
	ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
	return 0;								// Jump Back
      }
    }

  // Pass All Unhandled Messages To DefWindowProc
  return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
	
int initOutput(const char* caption, int width, int height, int bpp){
  if (!CreateGLWindow(caption,width,height,bpp,FALSE))
    {
      return 0;
      // Quit If Window Was Not Created
    }
  s_xsize = width;
  s_ysize = height;
  return 1;
}

void resizeOutput(int new_xsize, int new_ysize)
{
  WINDOWPLACEMENT wpl;
  GetWindowPlacement(hWnd, &wpl);
  MoveWindow(hWnd, wpl.ptMaxPosition.x, wpl.ptMaxPosition.y,
			 new_xsize, new_ysize, TRUE);


  ReSizeGLScene(new_xsize, new_ysize);

  s_xsize = new_xsize;
  s_ysize = new_ysize;
}

void updateOutput(const uint_32* framebuffer)
{
  MSG		msg;		
  //glClear(GL_COLOR_BUFFER_BIT );
	
	
  /* Fenster hat message gekriegt? Verarbeiten */
  if(!done){
    if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
      {
	if (msg.message==WM_QUIT)				
	  {
	    KillGLWindow();						
	  }
	else									
	  {
	    TranslateMessage(&msg);				
	    DispatchMessage(&msg);				
	  }
      }
    else										// If There Are No Messages
      {
	// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
	//if (active)								// Program Active?
	//{
	if (keys[VK_ESCAPE])				// Was ESC Pressed?
	  {
	    done=TRUE;						// ESC Signalled A Quit
	  }
	else								// Not Time To Quit, Update Screen
	  {
	    if (!wglMakeCurrent(hDC, hRC))
	      {
		printf("scheisse");
	      }		
	    glDrawPixels(s_xsize, s_ysize, GL_BGRA_EXT, GL_UNSIGNED_BYTE, framebuffer);
	    SwapBuffers(hDC);
	  }
	//}
			
	if (keys[VK_F1])						// Is F1 Being Pressed?
	  {
	    keys[VK_F1]=FALSE;					// If So Make Key FALSE
	    KillGLWindow();						// Kill Our Current Window
	    fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
	    if (!CreateGLWindow("GePhex-Output",640,480,32,fullscreen))
	      {
		printf("Mist..");
					
	      }
	  }
      }
  }
}

void shutdownOutput()
{
  KillGLWindow();
}
