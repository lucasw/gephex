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

#include "font3Dmodule.h"


#include <limits.h>
#include <math.h>

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

static logT s_log;

typedef struct GLShit_ {
	HGLRC				hrc;
	unsigned int		base;	
	HFONT				font;
	GLYPHMETRICSFLOAT	gmf[256];
} GLShit;

typedef struct _MyInstance {
	HDC					hdc;
 	HBITMAP				memBM;
	GLShit              glshit;
	int*				data;	
	FontType*			font;

	int                 width;
	int                 height;

	double xrot, yrot, zrot;
	double thickness;
} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;

  return 1;
}

void shutDown(void)
{
}


GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	//gluOrtho2D(0,640,0,480);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int initGL()
{
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	glEnable(GL_LIGHT0);								
	glEnable(GL_LIGHTING);								
	glEnable(GL_COLOR_MATERIAL);						

	glCullFace(GL_BACK); 
    glEnable(GL_CULL_FACE);
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
	
	s_log(0, lpMsgBuf);
	
	LocalFree( lpMsgBuf );
}

void buildFont(HDC hdc, GLShit* gls,
  		       const char* name, int height, int width, int weight,
			   int italic, int underline, double thickness)
{
	gls->base = glGenLists(255);

	gls->font = CreateFont(
		height,
		width,
		0,			
		0,
		weight,
		italic,
		underline,
		FALSE,
		ANSI_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE|DEFAULT_PITCH,
		name);

	//select the font into the context
	{
		HGDIOBJ old;
		old = SelectObject(hdc, gls->font);
		if(!old)
		{
			displayError();
		}
		
		wglUseFontOutlines(	hdc, 0,	255, gls->base, 0.001f, (float) thickness,
			WGL_FONT_POLYGONS, gls->gmf);					
		
		if (!SelectObject(hdc, old))
		{
			displayError();
		}
	}
}



GLvoid killFont(GLShit* gls)
{
	if (gls->font != 0)
	{
	  DeleteObject(gls->font);
	  glDeleteLists(gls->base, 255);
	  gls->font = 0;
	  gls->base = 0;
	}
}


void initGLShit(GLShit* gls)
{
	gls->base = 0;
	gls->font = 0;
	gls->hrc  = 0;
}

/*
 * returns 0 on success
 */
int build_shit(int xres, int yres, HDC hdc, HBITMAP* memBM, HGLRC *hrc, uint_32** data)
{
	BITMAPINFOHEADER	bmih;
	PIXELFORMATDESCRIPTOR pfd;
	GLuint pixelFormat;


	bmih.biSize        = sizeof (BITMAPINFOHEADER);				
	bmih.biPlanes      = 1;										
	bmih.biBitCount    = 32;									
	bmih.biWidth       = xres;
	bmih.biHeight      = yres;
	bmih.biCompression = BI_RGB;

	*memBM = CreateDIBSection(hdc,
		(BITMAPINFO*)(&bmih),
		DIB_RGB_COLORS, 
		(void**) data,
		NULL, 0);
	
	if (*memBM == 0)
	{
		displayError();		
		return 1;
	}

    if (SelectObject ( hdc, *memBM ) == 0)
	{
		displayError();		
	}

	pfd.nSize= sizeof(pfd);
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
	
	if (!(pixelFormat = ChoosePixelFormat(hdc,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		displayError();

		s_log(0,"Can't Find A Suitable PixelFormat.");					
		return 1;								// Return FALSE
	}

	if(!SetPixelFormat(hdc, pixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{	
		displayError();

		s_log(0, "Can't Set The PixelFormat.");
		return 1;								
	}
	
	if (!(*hrc=wglCreateContext(hdc)))				// Are We Able To Get A Rendering Context?
	{
		displayError();

		s_log(0, "Can't Create A GL Rendering Context.");
		return 1;								
	}

	if(!wglMakeCurrent(hdc, *hrc))					// Try To Activate The Rendering Context
	{
		displayError();
		s_log(0, "Can't Activate The GL Rendering Context.");
		return 1;								
	}

	if (!initGL())									
	{				
		displayError();
		s_log(0, "Initialization Failed.");
		return 1;								
	}
	
	ReSizeGLScene(xres,yres); 
	return 0;
}

void kill_shit(HDC hdc, HBITMAP *memBM, HGLRC *hrc)
{
	if (*hrc)
	{
		// make the rendering context not current 
		wglMakeCurrent (NULL, NULL) ; 
		// delete the rendering context 
		wglDeleteContext (*hrc);
		*hrc = 0;
	}

	if (*memBM)
	{
		SelectObject(hdc, NULL);
		DeleteObject(*memBM);
		*memBM = 0;
	}
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));	
  GLShit* gls = &my->glshit;    

  my->xrot = my->yrot = my->zrot = 0;
  my->thickness = 0;

  my->font = font_newInstance();
	
  my->hdc = CreateCompatibleDC(0);//TODO

  my->memBM = 0;
  my->glshit.hrc = 0;

  my->width  = -1;
  my->height = -1;

  return my;
}

void destruct(MyInstance* my)
{
  font_deleteInstance(my->font);
  killFont(&my->glshit);
  
  kill_shit(my->hdc, &my->memBM, &my->glshit.hrc);

  DeleteDC(my->hdc);  
  free(my);
}


GLvoid glPrint(GLShit* gls, const char *fmt, int size)
{
	unsigned int i;
	float length = 0;

	if (fmt == NULL)									
		return;		

	for (i=0;i<(strlen(fmt));i++)	
	{
		length += gls->gmf[fmt[i]].gmfCellIncX;			
	}

	glTranslatef(-length/2, 0.0f, 0.0f);
	glScalef((float) (size/8.0), (float) (size/8.0), 1.0f);

	glPushAttrib(GL_LIST_BIT);							
	glListBase(gls->base);									
	glCallLists(strlen(fmt), GL_UNSIGNED_BYTE, fmt);	
	glPopAttrib();							
};



BOOL font_changed(FontType* old_font, FontType* new_font)
{
	if (old_font->name == 0)
		return TRUE;
	if( (strcmp(old_font->name,new_font->name) != 0)
		||(old_font->height    != new_font->height)
		||(old_font->weight    != new_font->weight)
		||(old_font->italic    != new_font->italic)
		||(old_font->underline != new_font->underline))
		return TRUE; 
	else 
		return FALSE;
}


void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  
  double x, y, thickness = .0;

  FrameBufferAttributes attrib;
  attrib.xsize = inst->in_b->xsize;
  attrib.ysize = inst->in_b->ysize;
  framebuffer_changeAttributes(inst->out_r, &attrib);

  if (inst->in_b->xsize != my->width || inst->in_b->ysize != my->height)
  {
	  my->width  = inst->in_b->xsize;
	  my->height = inst->in_b->ysize;

      kill_shit(my->hdc,&my->memBM, &my->glshit.hrc);	  
	  
	  if (build_shit(my->width, my->height,
					  my->hdc, 
					  &my->memBM,
				      &my->glshit.hrc,
				      &my->data) != 0)
	  {
		  return;
	  }

	  my->thickness *= -1; /* force build_font */
  }

  assert(my->width == inst->in_b->xsize && my->height == inst->in_b->ysize);
  assert(my->width == inst->out_r->xsize && my->height == inst->out_r->ysize);
  
  if(!wglMakeCurrent(my->hdc, my->glshit.hrc))
  {
	  displayError();
	  s_log(0, "Can't Activate The GL Rendering Context.");
		       
	  return;								
  }
  
  thickness = trim_double(inst->in_block->number, 0, 10);
  
  if (font_changed(my->font, inst->in_font) == TRUE || thickness != my->thickness)
  {
	  killFont(&my->glshit);
	  buildFont(my->hdc, &my->glshit,
		        inst->in_font->name,
				inst->in_font->height,
				inst->in_font->width,
				inst->in_font->weight,
				inst->in_font->italic,
				inst->in_font->underline,
				thickness);

	  font_assign(my->font, inst->in_font);

	  my->thickness = thickness;
	  //printf("buildFont called\n");
  }
  
  x = trim_double(inst->in_pos->x, 0, 1) * 6.0 - 3.0;
  y = trim_double(inst->in_pos->y, 0, 1) * 5.0 - 2.5;

  my->xrot += trim_double(inst->in_xrot->number, 0, 4);
  my->yrot += trim_double(inst->in_yrot->number, 0, 4);
  my->zrot += trim_double(inst->in_zrot->number, 0, 4);
  
  
  if (!SelectObject(my->hdc, my->memBM))
  {
	  displayError();
  }
  
  glClear(GL_DEPTH_BUFFER_BIT);	
  
  //blit bg image
  memcpy(my->data,inst->in_b->framebuffer, my->width * my->height * 4);
  
  glLoadIdentity();  
  glTranslated(x, y, -10.0);
  glRotated(my->xrot, 1.0, 0.0, 0.0);
  glRotated(my->yrot, 0.0, 1.0, 0.0);
  glRotated(my->zrot, 0.0, 0.0, 1.0);
  
  glColor3f(inst->in_color->r, inst->in_color->g, inst->in_color->b);
  glPrint(&my->glshit, inst->in_text->text, inst->in_font->height);
  
  glFlush();
  
  memcpy(inst->out_r->framebuffer, my->data, my->width * my->height * 4);
}

