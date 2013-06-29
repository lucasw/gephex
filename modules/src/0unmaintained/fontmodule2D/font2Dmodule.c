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

#include "font2Dmodule.h"

#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>


typedef struct _MyInstance {
  HDC				hdc;
  HBITMAP			memBM;
  HGLRC				hrc;
  BITMAPINFOHEADER	        bmih;
  HFONT				font;

  FontType*			attrib;
  FontType*			oldAttrib;
  int*				data;
  unsigned int		        base;

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  return 1;
}

void shutDown(void)
{
}

// Resize And Initialize The GL Window
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
  if (height==0)
    {
      height=1;
    }

  // Reset The Current Viewport
  glViewport(0,0,width,height);

  gluOrtho2D(0,width,0,height);
  
  // Select The Projection Matrix  
  //glMatrixMode(GL_PROJECTION);

  // Reset The Projection Matrix
  //glLoadIdentity();
  
  // Calculate The Aspect Ratio Of The Window
  //gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

  // Select The Modelview Matrix
  //glMatrixMode(GL_MODELVIEW);
  
  // Reset The Modelview Matrix
  //glLoadIdentity();
}

int initGL()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
  return TRUE;	
  return 1;
}

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
  MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
  LocalFree( lpMsgBuf );
}

/**
* builds up a new font with user given input vals	
**/
GLvoid buildFont(MyInstancePtr my)
{
  my->base = glGenLists(96);

  my->font = CreateFont(my->attrib->height,
			       my->attrib->width,0,0,
			       my->attrib->weight,
			       my->attrib->italic,
			       my->attrib->underline,	
			       FALSE,			       
			       ANSI_CHARSET,
			       OUT_TT_PRECIS,
			       CLIP_DEFAULT_PRECIS,			
			       ANTIALIASED_QUALITY,			
			       FF_DONTCARE|DEFAULT_PITCH,		
			       my->attrib->name);		

  //select the font into the context
  if(!SelectObject(my->hdc, my->font))
    {
      displayError();
    }

  wglUseFontBitmaps(my->hdc, 32, 96, my->base);
  // Builds 96 Characters Starting At Character 32
  
  //deselect the font from the context
  if (!SelectObject(my->hdc, my->memBM))
    {
      displayError();
    }
}

GLvoid killFont(MyInstancePtr my)
{
  DeleteObject(my->font);
  glDeleteLists(my->base, 96);
}

__inline void assignFont(FontType* dst,const FontType* src)
{
  int lens = strlen(src->name)+1;
  if (dst->name != 0)
    free(dst->name);

  dst->name = (char*)malloc(lens);
  memcpy(dst->name,src->name,lens);

  dst->height = src->height;
  dst->width = src->width;
  dst->italic = src->italic;
  dst->weight = src->weight;
  dst->underline = src->underline;
}


MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  int xres = 640;
  int yres = 480;
    PIXELFORMATDESCRIPTOR pfd;
  GLuint pixelFormat;
  InstancePtr inst = (InstancePtr) malloc(sizeof(Instance));
	
  my->oldAttrib = (FontType*)malloc(sizeof(FontType));
  my->oldAttrib->name = 0;
  my->hdc = CreateCompatibleDC(0);//TODO

  my->bmih.biSize = sizeof (BITMAPINFOHEADER);
  my->bmih.biPlanes = 1;
  my->bmih.biBitCount = 32;
  my->bmih.biWidth = xres;
  my->bmih.biHeight = yres;
  my->bmih.biCompression = BI_RGB;

  my->memBM 
    = CreateDIBSection(my->hdc,
		       (BITMAPINFO*)(&my->bmih),
		       DIB_RGB_COLORS, 
		       (void**)(&(my->data)), NULL, 0);

//  inst->out_r->framebuffer = my->data; //TODO
  
  if (my->memBM == 0)
    {
      displayError();
      //TODO releasen...
      return 0;
    }

  if (SelectObject ( my->hdc, my->memBM ) == 0)
    {
      displayError();		
    }

  pfd.nSize= sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion= 1;
  pfd.dwFlags= PFD_SUPPORT_OPENGL | PFD_DRAW_TO_BITMAP | PFD_SUPPORT_GDI; 
  pfd.iPixelType= PFD_TYPE_RGBA; 
  pfd.cColorBits= 32; 
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
  pfd.cDepthBits=0;
  pfd.cStencilBits=0; 
  pfd.cAuxBuffers=0; 
  pfd.iLayerType=PFD_MAIN_PLANE; 
  pfd.bReserved=0; 
  pfd.dwLayerMask=0; 
  pfd.dwVisibleMask=0; 
  pfd.dwDamageMask=0; 
	
  if (!(pixelFormat=ChoosePixelFormat(my->hdc,&pfd)))
    // Did Windows Find A Matching Pixel Format?
    {
      displayError();

      MessageBox(NULL,"Can't Find A Suitable PixelFormat.",
		 "ERROR",MB_OK|MB_ICONEXCLAMATION);
      return NULL;
      // Return FALSE
    }

  if(!SetPixelFormat(my->hdc,pixelFormat,&pfd))
    // Are We Able To Set The Pixel Format?
    {	
      displayError();

      MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",
		 MB_OK|MB_ICONEXCLAMATION);
      return NULL;
    }
	
  if (!(my->hrc=wglCreateContext(my->hdc)))
    // Are We Able To Get A Rendering Context?
    {
      displayError();

      MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",
		 MB_OK|MB_ICONEXCLAMATION);
      return NULL;
    }

  if(!wglMakeCurrent(my->hdc,my->hrc))
    // Try To Activate The Rendering Context
    {
      displayError();
      MessageBox(NULL,"Can't Activate The GL Rendering Context.",
		 "ERROR",MB_OK|MB_ICONEXCLAMATION);
      return 0;
    }

  if (!initGL())
    {				
      displayError();
      MessageBox(NULL,"Initialization Failed.","ERROR",
		 MB_OK|MB_ICONEXCLAMATION);
      return NULL;
    }
	
  ReSizeGLScene(xres,yres);   

  my->base = glGenLists(96);


  return my;
}

void destruct(MyInstance* my)
{
   killFont(my);
  free(my->oldAttrib);
 
  DeleteDC(my->hdc);
  DeleteObject(my->memBM);

  free(my);
}


GLvoid glPrint(MyInstancePtr my,const char *fmt)
{
  if (fmt == NULL)
    return;

  glPushAttrib(GL_LIST_BIT);
  glListBase(my->base - 32);
  glCallLists(strlen(fmt), GL_UNSIGNED_BYTE, fmt);
  glPopAttrib();
};

BOOL fontChanged(MyInstancePtr my)
{
	if (my->oldAttrib->name == 0)
		return TRUE;
  if( (strcmp(my->oldAttrib->name,my->attrib->name)!=0)
      ||(my->oldAttrib->height!=my->attrib->height)
      ||(my->oldAttrib->weight!=my->attrib->weight)
      ||(my->oldAttrib->italic!=my->attrib->italic)
      ||(my->oldAttrib->underline!=my->attrib->underline))
    return TRUE; //TODO: test width later too
  else 
    return FALSE;
}

static float cnt1 = 0.1f;
static float cnt2 = 0.2f;

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  int x, y;

  	my->attrib = inst->in_font;

  if(!wglMakeCurrent(my->hdc,my->hrc))
    // Try To Activate The Rendering Context
    {
      displayError();
      MessageBox(NULL,"Can't Activate The GL Rendering Context.",
		 "ERROR",MB_OK|MB_ICONEXCLAMATION);
      return;								
    }

  if(fontChanged(my)==TRUE)
    {
      killFont(my);
      buildFont(my);
      assignFont(my->oldAttrib, my->attrib);
    }


  //my->xPos  = (my->xPos + (int)((inst->speed->number / (double) UINT_MAX)*20))%(640+strlen(my->attrib->name));
  x = (int) ((double)inst->in_pos->x/(double)UINT_MAX * inst->out_r->xsize);
  y = (int) ((double)inst->in_pos->y/(double)UINT_MAX * inst->out_r->ysize);

  if (!SelectObject(my->hdc, my->memBM))
    {
      displayError();
    }

  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
  //glTranslatef(0.0f, 0.0f, -1.0f);
  /*glRasterPos2f(0,0);
    glDrawPixels(inst->in_b->xsize, inst->in_b->ysize, GL_RGBA, 
    GL_UNSIGNED_BYTE, inst->in_b->framebuffer);*/
  memcpy(my->data,inst->in_b->framebuffer,640*480*4);
	
	
  //gl switches colors, so we do to, cuz we are clev0r m0thafux0rz
  glColor3f(inst->in_color->b, inst->in_color->g, inst->in_color->r);
  glRasterPos2f((float) x,(float) y);
  glPrint(my,inst->in_text->text);	// Print GL Text To The Screen

  glFlush();
	
  inst->out_r->framebuffer = my->data; //TODO
}

