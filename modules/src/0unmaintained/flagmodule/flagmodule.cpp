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

#include "flagmodule.h"
#include "gfxutil.h"

#include <math.h>
#include <limits.h>
//#include <d3d8.h>

#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#define GLH_EXT_SINGLE_FILE
#include "glh_extensions.h"

#define TEX_SIZE 256

GLuint	texture[1];
float points[45][45][3];
int wiggleCount;


typedef struct _MyInstance {
	
	HDC			hdc;
	HBITMAP		memBM;
	HGLRC			hrc;
	BITMAPINFOHEADER	bmih;
	//HDRAWDIB		hdd;
	//GLUquadricObj	*quadratic;
	int*			data;
	//LPDIRECT3DDEVICE device;
	//LPDIRECT3DTEXTURE8 tex;
	struct GLHardwareSurface* buf;
	
} MyInstance, *MyInstancePtr;



GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
    {
		height=1;										// Making Height Equal One
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
	int x, y;
	glEnable(GL_TEXTURE_2D);							
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	glPolygonMode( GL_BACK, GL_FILL );					
	glPolygonMode( GL_FRONT, GL_LINE );					
	
	for(x=0; x<45; x++)
    {
		for(y=0; y<45; y++)
		{
			points[x][y][0]=(float)((x/5.0f)-4.5f);
			points[x][y][1]=(float)((y/5.0f)-4.5f);
			points[x][y][2]=(float)(sin((((x/5.0f)*40.0f)/360.0f)*3.141592654*2.0f));
		}
    }
	/*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glGenTextures(1, &texture[0]);*/
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

int init(logT log_function)
{
	return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
	MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
	
	{
		PIXELFORMATDESCRIPTOR pfd;
		GLuint pixelFormat;
		
		/*inst->out_r->framebuffer = 
		(int*) malloc(sizeof(int)*inst->out_r->xsize*inst->out_r->ysize);*/
		
		/*my->hdc = CreateCompatibleDC(0);//TODO
		my->bmih.biSize = sizeof (BITMAPINFOHEADER);
		my->bmih.biPlanes = 1;
		my->bmih.biBitCount = 32;
		
		my->bmih.biWidth = TEX_SIZE; //TODO
		
		my->bmih.biHeight = TEX_SIZE; //TODO
		my->bmih.biCompression = BI_RGB;
		
		my->memBM 
			= CreateDIBSection(my->hdc,
			(BITMAPINFO*)(&my->bmih),
			DIB_RGB_COLORS, 
			(void**)(&(my->data)), NULL, 0);
		
		//inst->out_r->framebuffer = my->data; //TODO
		
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
			MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",
				MB_OK|MB_ICONEXCLAMATION);
			return 0;
		}*/
		if(!initGlUtil())
			printf("ficken\n");

		const char* extensions =  (const char*)glGetString(GL_EXTENSIONS);
		my->buf = createGLHardwareSurface(TEX_SIZE, TEX_SIZE, 0);

		if(my->buf==NULL)
			printf("Flagmodule couldn't retrieve Hardware surface...");
		

		if (!initGL())
		{				
			displayError();
			MessageBox(NULL,"Initialization Failed.","ERROR",
				MB_OK|MB_ICONEXCLAMATION);
			return NULL;			
		}
		
		//ReSizeGLScene(inst->out_r->xsize,inst->out_r->ysize);  //TODO
		
		glEnable(GL_TEXTURE_2D);
		//glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0,
		//GL_RGBA, GL_UNSIGNED_BYTE, inst->source->framebuffer);
		glGenTextures(1, &texture[0]);	
		
		return my;
  }
}

void destruct(MyInstance* my)
{
	// Add your cleanup here
	if(my->hdc)
		DeleteDC(my->hdc);
	if(my->memBM)
		DeleteObject(my->memBM);
	if(my->buf)
		destroyGLHardwareSurface(my->buf);
	free(my);
}

static float x_rot = 0.;
static float y_rot = 0.;
static float z_rot = 0.;

void update(void* instance)
{
	InstancePtr inst = (InstancePtr) instance;
	MyInstancePtr my = inst->my;
	FrameBufferAttributes attribs;
	int x,y;
	float float_x, float_y, float_xb, float_yb, hold;
	
	framebuffer_getAttributes(inst->in_b, &attribs);
	if(attribs.xsize!=TEX_SIZE||attribs.ysize!=TEX_SIZE)
	{	
		attribs.xsize = TEX_SIZE;
		attribs.ysize = TEX_SIZE;
		framebuffer_changeAttributes(inst->out_r, &attribs);
		
	}
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TEX_SIZE, TEX_SIZE, 0, GL_RGBA,
	       GL_UNSIGNED_BYTE, inst->in_b->framebuffer);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	
	//ReSizeGLScene(inst->out_r->xsize,inst->out_r->ysize);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	
	
	if(!wglMakeCurrent(my->buf->dc,my->buf->rc))
		// Try To Activate The Rendering Context
    {
		displayError();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.",
			"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return;								
    }
	
	/*if (!SelectObject(my->hdc, my->memBM))
    {
		displayError();
    }*/
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();	// Reset The View
	
	glTranslatef(0.0f,0.0f,-12.0f);
	
	glRotatef(x_rot,1.0f,0.0f,0.0f);
	glRotatef(y_rot,0.0f,1.0f,0.0f);  
	glRotatef(z_rot,0.0f,0.0f,1.0f);
	
	
	//DrawDibDraw (my->hdd, my->hdc, 0, 0, 256, 256, &my->bmih, inst->source->framebuffer, 0, 0, inst->source->xsize, inst->source->ysize, 0);
	//Das ist schweinelangsam....aber weiss halt net, wie man das sonst machen sollte hier....
	

	glBegin(GL_QUADS);
	
	for( x = 0; x < 44; x++ )
    {
		for( y = 0; y < 44; y++ )
		{
			float_x = (float)(x)/44.0f;
			float_y = (float)(y)/44.0f;
			float_xb = (float)(x+1)/44.0f;
			float_yb = (float)(y+1)/44.0f;
			
			glTexCoord2f( float_x, float_y);
			glVertex3f( points[x][y][0], points[x][y][1], points[x][y][2] );
			
			glTexCoord2f( float_x, float_yb );
			glVertex3f( points[x][y+1][0], points[x][y+1][1],
				points[x][y+1][2] );
			
			glTexCoord2f( float_xb, float_yb );
			glVertex3f( points[x+1][y+1][0], points[x+1][y+1][1],
				points[x+1][y+1][2] );
			
			glTexCoord2f( float_xb, float_y );
			glVertex3f( points[x+1][y][0], points[x+1][y][1],
				points[x+1][y][2] );
		}
    }
	glEnd();
	
	if( wiggleCount == 2 )
    {
		for( y = 0; y < 45; y++ )
		{
			hold=points[0][y][2];
			for( x = 0; x < 44; x++)
			{
				points[x][y][2] = points[x+1][y][2];
			}
			points[44][y][2]=hold;
		}
		wiggleCount = 0;
    }
	
	wiggleCount++;
	
	glFlush();
	
	/*
	inst->out_r->framebuffer = my->data;*/
	glDrawPixels( TEX_SIZE, TEX_SIZE, GL_RGBA, GL_UNSIGNED_BYTE, inst->out_r->framebuffer);
	
	x_rot += (float)inst->in_x->number/(float)UINT_MAX;
	y_rot += (float)inst->in_y->number/(float)UINT_MAX;
	z_rot += (float)inst->in_z->number/(float)UINT_MAX;
	
}


