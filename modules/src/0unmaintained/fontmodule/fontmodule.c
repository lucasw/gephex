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

#include <stdlib.h>
#include <limits.h>

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include "dllmodule.h"
#include "math.h"
#include "font.xpm"

#include "framebuffertype.h"
#include "numbertype.h"
#include "stringtype.h"

static const char* SPEC = 
"mod_spec { name=mod_font; number_of_inputs=3; number_of_outputs=1; "
"deterministic=true; }";

static const char* INPUT_SPECS[] = 
{
  "input_spec { type=typ_string; const=true; strong_dependency=true; }",
  "input_spec { type=typ_number; const=true; strong_dependency=true; }",
  "input_spec { type=typ_framebuffer; const=true; strong_dependency=true; }"
};

static const char* OUTPUT_SPECS[] = 
{
  "output_spec { type=typ_framebuffer; }"
};


typedef struct Font_
{
	HDC					hdc;
	HBITMAP				memBM;
	HGLRC				hrc;
	int					xPos;
	int					yPos;
	int*				data;
	unsigned int		base;
	BITMAPINFOHEADER	bmih;
	HFONT				font;
} Font;


typedef struct instance_{
	StringType* text;
	NumberType* speed;
	FrameBufferType* source;
	FrameBufferType result;	
	
	Font font;
} Instance, *InstancePtr;


int init(logT log_function)
{

  return 1;
}
/*void shutDown(void)
{

}*/

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	gluOrtho2D(0,640,0,480);

	//glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	//glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	//gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	//glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	//glLoadIdentity();									// Reset The Modelview Matrix
}

int initGL()
{
	//glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	//glClearDepth(1.0f);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
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
	// Process any inserts in lpMsgBuf.
	// ...
	// Display the string.
	MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
	// Free the buffer.
	LocalFree( lpMsgBuf );
}

GLvoid buildFont(InstancePtr inst)								// Build Our Bitmap Font
{
	inst->font.base = glGenLists(96);								// Storage For 96 Characters

	inst->font.font = CreateFont(	-24,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Courier New");					// Font Name

	if(!SelectObject(inst->font.hdc, inst->font.font))
	{
		displayError();
	}

	wglUseFontBitmaps(inst->font.hdc, 32, 96, inst->font.base);							// Builds 96 Characters Starting At Character 32

	if (!SelectObject(inst->font.hdc, inst->font.memBM))
	{
		displayError();
	}
}

GLvoid killFont(InstancePtr inst)
{
	glDeleteLists(inst->font.base, 96);
}

void*  newInstance(void)
{
	PIXELFORMATDESCRIPTOR pfd;
	GLuint pixelFormat;
	InstancePtr inst = (InstancePtr) malloc(sizeof(Instance));
	
	inst->result.xsize = 640;
	inst->result.ysize = 480;
	/*inst->result.framebuffer = 
		(int*) malloc(sizeof(int)*inst->result.xsize*inst->result.ysize);*/

	
	inst->text = 0;
	inst->font.xPos = 320;
	inst->font.yPos = 240;
	inst->font.hdc = CreateCompatibleDC(0);//TODO

	inst->font.bmih.biSize = sizeof (BITMAPINFOHEADER);				
	inst->font.bmih.biPlanes = 1;										
	inst->font.bmih.biBitCount = 32;									
	inst->font.bmih.biWidth = inst->result.xsize;										
	inst->font.bmih.biHeight = inst->result.ysize;									
	inst->font.bmih.biCompression = BI_RGB;

	inst->font.memBM = CreateDIBSection(
		inst->font.hdc, (BITMAPINFO*)(&inst->font.bmih), DIB_RGB_COLORS, 
								(void**)(&(inst->font.data)), NULL, 0);
  
	if (inst->font.memBM == 0)
	{
		displayError();
		//TODO releasen...
		return 0;
	}

    if (SelectObject ( inst->font.hdc, inst->font.memBM ) == 0)
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
	
	if (!(pixelFormat=ChoosePixelFormat(inst->font.hdc,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		displayError();

		MessageBox(NULL,"Can't Find A Suitable PixelFormat.",
					"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return NULL;								// Return FALSE
	}

	if(!SetPixelFormat(inst->font.hdc,pixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{	
		displayError();

		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return NULL;								
	}
	
	if (!(inst->font.hrc=wglCreateContext(inst->font.hdc)))				// Are We Able To Get A Rendering Context?
	{
		displayError();

		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return NULL;								
	}

	if(!wglMakeCurrent(inst->font.hdc,inst->font.hrc))					// Try To Activate The Rendering Context
	{
		displayError();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 0;								
	}

	if (!initGL())									
	{				
		displayError();
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return NULL;								
	}
	
	ReSizeGLScene(inst->result.xsize,inst->result.ysize);  

	buildFont(inst);

	return inst;
}

void deleteInstance(void* instance)
{
	InstancePtr inst = (InstancePtr) instance;
	killFont(inst);
	//free(inst->result.framebuffer);
	DeleteDC(inst->font.hdc);
	DeleteObject(inst->font.memBM);
	free(inst);
}

int setInput(void* instance,int index,void* typePointer)
{	
	InstancePtr inst = (InstancePtr) instance;
	switch(index)
	{
	case 0:
		inst->text = (StringType*) typePointer;
	break;
	case 1:
		inst->speed = (NumberType*) typePointer;
		break;
	case 2:
		inst->source = (FrameBufferType*)typePointer;
	break;
	}
	return 1;
}

void * getOutput (void* instance,int index)
{
	InstancePtr inst = (InstancePtr) instance;
	return &(inst->result);
}

GLvoid glPrint(InstancePtr inst,const char *fmt)
{
	if (fmt == NULL)								
		return;										

	glPushAttrib(GL_LIST_BIT);
	glListBase(inst->font.base - 32);
	glCallLists(strlen(fmt), GL_UNSIGNED_BYTE, fmt);
	glPopAttrib();
};

static float cnt1 = 0.1f;
static float cnt2 = 0.2f;

void update(void* instance)
{
	InstancePtr inst = (InstancePtr)instance;
	if(!wglMakeCurrent(inst->font.hdc,inst->font.hrc))					// Try To Activate The Rendering Context
	{
		displayError();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return;								
	}

	inst->font.xPos = (int) (640. * inst->speed->number / (double) UINT_MAX);

	if (!SelectObject(inst->font.hdc, inst->font.memBM))
	{
		displayError();
	}

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glTranslatef(0.0f, 0.0f, -1.0f);
	/*glRasterPos2f(0,0);
	glDrawPixels(inst->source->xsize, inst->source->ysize, GL_RGBA, 
		GL_UNSIGNED_BYTE, inst->source->framebuffer);*/
	memcpy(inst->font.data,inst->source->framebuffer,640*480*4);
	
	
	glColor3f(1.0f*(float)(cos(cnt1)),1.0f*(float)(sin(cnt2)),1.0f-0.5f*(float)(cos(cnt1+cnt2)));
	glRasterPos2f((float) inst->font.xPos,(float) inst->font.yPos);
 	glPrint(inst,inst->text->text);	// Print GL Text To The Screen

	glFlush();
	//SwapBuffers(inst->font.hdc);
	cnt1+=0.091f;
	cnt2+=0.012f;
	inst->result.framebuffer = inst->font.data;
}

const char* getInputSpec (int index)
{
  return INPUT_SPECS[index];
}

const char* getOutputSpec (int index)
{
  return OUTPUT_SPECS[index];
}

const char* getSpec(void)
{
  return SPEC;
}

int getInfo(char* buf,int bufLen)
{
	static const char* INFO = "info {name=Schrift group=Schrifteffekte inputs=[3 Text{widget_type=text_edit; hidden=true; default_value=Scrolltext;} "
		"Geschwindigkeit Bild] outputs=[1 Bild] type=xpm }";
	char* tmpBuf;
	int reqLen = strlen(INFO) + 1 + getSizeOfXPM(font_xpm);
	if (buf != 0 && reqLen <= bufLen)
    {
		char* offset;
		int i;
		int lines = getNumberOfStringsXPM(font_xpm);
		 
		tmpBuf = malloc(reqLen);
		memcpy(tmpBuf,INFO,strlen(INFO)+1);
		offset = tmpBuf + strlen(INFO)+1;
		for (i = 0; i < lines; ++i)
		{
			
			char* source = font_xpm[i];
			memcpy(offset,source,strlen(source)+1);
			offset += strlen(source) + 1;
		}			
		memcpy(buf,tmpBuf,reqLen);
		free(tmpBuf);
    }
  return reqLen;
}

