#include "font3Dmodule.h"


#include <limits.h>
#include <math.h>

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>


typedef struct _MyInstance {
	HDC					hdc;
	HBITMAP				memBM;
	HGLRC				hrc;
	int*				data;
	unsigned int		base;
	BITMAPINFOHEADER	bmih;
	HFONT				font;
	GLYPHMETRICSFLOAT	gmf[256];
	FontType*			attrib;
	FontType*			oldAttrib;
} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  return 1;
}

void shutDown(void)
{
}


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
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	glEnable(GL_LIGHT0);								
	glEnable(GL_LIGHTING);								
	glEnable(GL_COLOR_MATERIAL);						
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

GLvoid buildFont(MyInstancePtr my, float thickness)							
{
	my->base = glGenLists(96);						

	my->font = CreateFont(my->attrib->height*(-1),
								 my->attrib->width,	
								 0,							
								 0,
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

	/*BOOL wglUseFontOutlines(
	  HDC  hdc,         // device context of the outline font
	DWORD  first,     // first glyph to be turned into a display list
	DWORD  count,     // number of glyphs to be turned into display 
                    // lists
	DWORD  listBase,  // specifies the starting display list
	FLOAT  deviation, // specifies the maximum chordal deviation from 
                    // the true outlines
	FLOAT  extrusion, // extrusion value in the negative z direction
	int  format,      // specifies line segments or polygons in 
                    // display lists
	LPGLYPHMETRICSFLOAT  lpgmf 
	                    // address of buffer to receive glyph metric data
	);
	*/

	//wglUseFontOutlines(	my->hdc, 0,	255, my->base, 0.0f, 0.2f, WGL_FONT_POLYGONS, my->gmf);					
	wglUseFontOutlines(	my->hdc, 0,	255, my->base, 0.0f, thickness, WGL_FONT_POLYGONS, my->gmf);					

	if (!SelectObject(my->hdc, my->memBM))
	{
		displayError();
	}
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


GLvoid killFont(MyInstancePtr my)
{
	DeleteObject(my->font);
	glDeleteLists(my->base, 96);
}


MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
	PIXELFORMATDESCRIPTOR pfd;
	GLuint pixelFormat;
	int xres = 640;
	int yres = 480; //TODO

	my->oldAttrib = (FontType*)malloc(sizeof(FontType));
	my->oldAttrib->name = 0;
	
	my->hdc = CreateCompatibleDC(0);//TODO

	my->bmih.biSize = sizeof (BITMAPINFOHEADER);				
	my->bmih.biPlanes = 1;										
	my->bmih.biBitCount = 32;									
	my->bmih.biWidth = xres;
	my->bmih.biHeight = yres;
	my->bmih.biCompression = BI_RGB;

	my->memBM = CreateDIBSection(
		my->hdc, (BITMAPINFO*)(&my->bmih), DIB_RGB_COLORS, 
								(void**)(&(my->data)), NULL, 0);
  
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
	
	if (!(pixelFormat=ChoosePixelFormat(my->hdc,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		displayError();

		MessageBox(NULL,"Can't Find A Suitable PixelFormat.",
					"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return NULL;								// Return FALSE
	}

	if(!SetPixelFormat(my->hdc,pixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{	
		displayError();

		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return NULL;								
	}
	
	if (!(my->hrc=wglCreateContext(my->hdc)))				// Are We Able To Get A Rendering Context?
	{
		displayError();

		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return NULL;								
	}

	if(!wglMakeCurrent(my->hdc,my->hrc))					// Try To Activate The Rendering Context
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
	
	ReSizeGLScene(xres,yres); 

  return my;
}

void destruct(MyInstance* my)
{
  killFont(my);
	//free(inst->result.framebuffer);
	DeleteDC(my->hdc);
	DeleteObject(my->memBM);
  free(my);
}


GLvoid glPrint(MyInstancePtr my,const char *fmt)
{
	unsigned int i;
	float length = 0;

	if (fmt == NULL)									
		return;		

	for (i=0;i<(strlen(fmt));i++)	
	{
		length+=my->gmf[fmt[i]].gmfCellIncX;			
	}

	glTranslatef(-length/2,0.0f,0.0f);					

	glPushAttrib(GL_LIST_BIT);							
	glListBase(my->base);									
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
		return TRUE; 
	else 
		return FALSE;
}

static float xrot=0, yrot=0, zrot=0;

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

	
	float x, y, thickness = .0f;

	my->attrib = inst->in_font;

	if(!wglMakeCurrent(my->hdc,my->hrc))
	{
		displayError();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return;								
	}

	thickness = (float)inst->in_block->number/(double)UINT_MAX * 5.0;

	if(fontChanged(my) == TRUE)
	{
		killFont(my);
		buildFont(my, thickness);
		assignFont(my->oldAttrib, my->attrib);
		//printf("buildFont called\n");
	}

	
	x = (float)inst->in_pos->x/(double)UINT_MAX * 6.0 -3.0;
	y = (float)inst->in_pos->y/(double)UINT_MAX * 5.0 -2.5;
	xrot += (double)inst->in_xrot->number/(double)UINT_MAX * 4.;
	yrot += (double)inst->in_yrot->number/(double)UINT_MAX * 4.;
	zrot += (double)inst->in_zrot->number/(double)UINT_MAX * 4.;
	

	if (!SelectObject(my->hdc, my->memBM))
	{
		displayError();
	}

	glClear(GL_DEPTH_BUFFER_BIT);	
	
	//blit bg image
	memcpy(my->data,inst->in_b->framebuffer,640*480*4);
	
	glLoadIdentity();								
	glTranslatef(x,y,-10.0f);					
	glRotatef(xrot,1.0f,0.0f,0.0f);					
	glRotatef(yrot,0.0f,1.0f,0.0f);					
	glRotatef(zrot,0.0f,0.0f,1.0f);					
	
	glColor3f(inst->in_color->b, inst->in_color->g, inst->in_color->r);
	glPrint(my, inst->in_text->text);					
	
	glFlush();

	inst->out_r->framebuffer = my->data;
}

