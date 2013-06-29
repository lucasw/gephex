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

#include "gfxutil.h"
#include <stdio.h>
//#include "glh_extensions.h"

/*bool initGlUtil()
{
	GLuint pixelFormat;
	
	//dc = wglGetCurrentDC();
	//rc = wglGetCurrentContext();

	if(!WAS_INIT)
	{	
		dc = GetDC(NULL);

		PIXELFORMATDESCRIPTOR pfd;
		pfd.nSize= sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion= 1;
		pfd.dwFlags= PFD_SUPPORT_OPENGL | PFD_SUPPORT_GDI; 
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
		
		if (!(pixelFormat=ChoosePixelFormat(dc,&pfd)))
			// Did Windows Find A Matching Pixel Format?
		{
			//displayError();
			
			MessageBox(NULL,"Can't Find A Suitable PixelFormat.",
				"ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;
		}
		
		if(!SetPixelFormat(dc,pixelFormat,&pfd))
			// Are We Able To Set The Pixel Format?
		{	
			
			MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",
				MB_OK|MB_ICONEXCLAMATION);
			return FALSE;
		}
		
		if (!(rc=wglCreateContext(dc)))
			// Are We Able To Get A Rendering Context?
		{

			MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",
				MB_OK|MB_ICONEXCLAMATION);
			return FALSE;
		}
		
		if(!wglMakeCurrent(dc,rc))
			// Try To Activate The Rendering Context
		{
			MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",
				MB_OK|MB_ICONEXCLAMATION);
			return FALSE;
		}
		WAS_INIT = TRUE;
	}
	return TRUE;
}
*/

/**
*	Function creates an offscreen surface in video memory.
*	Unfortunately this is probably only gonna work on Nvidia cards
*	Install the Nvidia sdk to compile
**/
/*struct GLHardwareSurface*  createGLHardwareSurface(int w, int h, unsigned int mode)
{
	int   iattributes[2*MAX_ATTRIBS]; 
	float fattributes[2*MAX_ATTRIBS]; 
	int   nfattribs = 0; 
	int   niattribs = 0;
	int a;
	int pformat[MAX_PFORMATS]; 
	int format;
	unsigned int nformats; 
	
	if(!WAS_INIT)
	{
		if(!initGlUtil())
		{
			MessageBox(NULL, "Couldn't create rendering context bla...", "error", MB_OK);
			return NULL;
		}
	}	
	
	HDC hdc = wglGetCurrentDC();
	HGLRC hglrc = wglGetCurrentContext();
	struct GLHardwareSurface* createdSurface = 
		(struct GLHardwareSurface*)malloc(sizeof(struct GLHardwareSurface));
	
	

	if( !glh_init_extensions( " WGL_ARB_pbuffer "
		" WGL_ARB_pixel_format " ) )
	{
        //TODO: report error or whatever....
		return NULL;
	}
	
	for ( a = 0; a < 2*MAX_ATTRIBS; a++ )
	{
        iattributes[a] = 0;
        fattributes[a] = 0;
	}
	
    // Since we are trying to create a pbuffer, the pixel format we
    // request (and subsequently use) must be "p-buffer capable".
    iattributes[2*niattribs  ] = WGL_DRAW_TO_PBUFFER_ARB;
    iattributes[2*niattribs+1] = TRUE;
    niattribs++;
	
    iattributes[2*niattribs  ] = WGL_PIXEL_TYPE_ARB;
	iattributes[2*niattribs+1] = WGL_TYPE_RGBA_ARB;
	niattribs++;
	
	
    //iattributes[2*niattribs  ] = WGL_DOUBLE_BUFFER_ARB;
    //iattributes[2*niattribs+1] = TRUE;
	//niattribs++;
	
    iattributes[2*niattribs  ] = WGL_DEPTH_BITS_ARB;
    iattributes[2*niattribs+1] = 1;
    niattribs++;
	
	//if ( mode & GLUT_STENCIL )
	
        iattributes[2*niattribs  ] = WGL_STENCIL_BITS_ARB;
        iattributes[2*niattribs+1] = 1;
        niattribs++;
		
    //if ( mode & GLUT_ACCUM )
	//{
    //    iattributes[2*niattribs  ] = WGL_ACCUM_BITS_ARB;
    //   iattributes[2*niattribs+1] = 1;
    //    niattribs++;
	//}
	
    iattributes[2*niattribs  ] = WGL_SUPPORT_OPENGL_ARB;
    iattributes[2*niattribs+1] = TRUE;
    niattribs++;
	
    format;
    pformat[MAX_PFORMATS];
    nformats;
    if ( !wglChoosePixelFormatARB( hdc, iattributes, fattributes, MAX_PFORMATS, pformat, &nformats ) )
	{
        fprintf( stderr, "pbuffer creation error:  wglChoosePixelFormatARB() failed.\n" );
        return NULL;
	}
	if ( nformats <= 0 )
	{
        fprintf( stderr, "pbuffer creation error:  Couldn't find a suitable pixel format.\n" );
        return NULL;
	}
    format = pformat[0];
	
	iattributes[0] = 0;
    createdSurface->surface = wglCreatePbufferARB( hdc, format, w, h, iattributes );
    if ( createdSurface->surface == NULL)
	{
        DWORD err = GetLastError();
        fprintf( stderr, "pbuffer creation error:  wglCreatePbufferARB() failed\n" );
        if ( err == ERROR_INVALID_PIXEL_FORMAT )
		{
            fprintf( stderr, "error:  ERROR_INVALID_PIXEL_FORMAT\n" );
		}
        else if ( err == ERROR_NO_SYSTEM_RESOURCES )
		{
            fprintf( stderr, "error:  ERROR_NO_SYSTEM_RESOURCES\n" );
		}
        else if ( err == ERROR_INVALID_DATA )
		{
            fprintf( stderr, "error:  ERROR_INVALID_DATA\n" );
		}
        return NULL;
	}
	
    // Get the device context.
    createdSurface->dc = wglGetPbufferDCARB( createdSurface->surface );
    if ( !createdSurface->dc)
	{
        fprintf( stderr, "pbuffer creation error:  wglGetPbufferDCARB() failed\n" );
        return NULL;
	}
	
    // Create a gl context for the p-buffer.
    createdSurface->rc = wglCreateContext( createdSurface->dc );
    if ( !createdSurface->rc )
	{
        fprintf( stderr, "pbuffer creation error:  wglCreateContext() failed\n" );
        return NULL;
	}
	
	return createdSurface;	
}*/


/**
*	Call this function to get rid of a created pbuffer
**/
/*void destroyGLHardwareSurface(struct GLHardwareSurface* which)
{
	if ( which->surface)
    {
        wglDeleteContext( which->rc);
        wglReleasePbufferDCARB( which->surface, which->dc);
        wglDestroyPbufferARB( which->surface);
	}
}*/

/*
void createGLSoftwareSurface(unsigned int* frameBuffer, HBITMAP* surface,
							 int w, int h)
{

}*/

void WindowHandler::displayError()
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

HRESULT WindowHandler::create(int w, int h, bool popup)
{
	if(WAS_INIT)
		return S_OK;

	m_width = w;
	m_height = h;
	
	HINSTANCE hInstance  = GetModuleHandle(NULL);
	const char* progname = "GE-PHEX Output";
	const char* classname = "GE-PHEX_DX_OUTPUT_WINDOW";
	
	if(!popup)
	{
		m_hWnd=CreateWindow(
			classname,
			progname,
			WS_POPUP,
			CW_USEDEFAULT,
			0,
			m_width,
			m_height,
			NULL,
			NULL,
			hInstance,
			NULL);
		
		if (m_hWnd == 0)
		{
			displayError();
			return E_FAIL;
		}
		
		//MaximizeWindowOnMonitor(inst->hWnd,1);
	}
	else
	{
		m_hWnd=CreateWindowEx(
			WS_EX_TOPMOST,
			classname,
			progname,
			WS_POPUP|WS_CAPTION|WS_THICKFRAME|WS_BORDER|WS_OVERLAPPED|WS_VISIBLE,
			CW_USEDEFAULT,
			0,
			m_width,
			m_height,
			NULL,
			NULL,
			hInstance,
			NULL);
		
		if (m_hWnd == 0)
		{
			displayError();
			return E_FAIL;
		}
	}
	//ShowWindow(m_hWnd,SW_SHOW);	

	WAS_INIT = true;
	return S_OK;
}

HRESULT WindowHandler::destroy()
{
	WAS_INIT = false;
	if(m_device)
		m_device->Release();

	if(m_d3dInterface)
		m_d3dInterface->Release();

	return DestroyWindow(m_hWnd);
}

LPDIRECT3DDEVICE8 WindowHandler::getDirectXDevice()
{
	// window handle am start?
	if(!WAS_INIT)
		return NULL;

	if(NULL == m_device)
	{
		if( NULL == ( m_d3dInterface = Direct3DCreate8( D3D_SDK_VERSION ) ) )
		{
			printf("\nCreating failed...\n");
			return NULL;
		}
		
	
		D3DDISPLAYMODE d3ddm;
		
		if( FAILED( m_d3dInterface->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
		{
			printf("\nAdapter wants to fuck us...\n");
			return NULL;
		}
			
	
		d3ddm.Height = m_height;
		d3ddm.Width = m_width;
		d3ddm.Format = D3DFMT_A8R8G8B8;
		//d3ddm.RefreshRate = 0;

		D3DPRESENT_PARAMETERS d3dpp; 
		ZeroMemory( &d3dpp, sizeof(d3dpp) );
		d3dpp.Windowed   = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = d3ddm.Format;		
		d3dpp.BackBufferCount = 1;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE; 
		d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	
		if(FAILED(m_d3dInterface->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,
									m_hWnd,
									D3DCREATE_MIXED_VERTEXPROCESSING,
									&d3dpp,&m_device)))
		{
									
			return NULL;
		}
									
	}

	return m_device;
}

HWND WindowHandler::hWnd()
{
	if(WAS_INIT)
		return m_hWnd;

	else
		displayError();

	return NULL;
}

HWND WindowHandler::m_hWnd = NULL;

LPDIRECT3DDEVICE8 WindowHandler::m_device = NULL;
LPDIRECT3D8 WindowHandler::m_d3dInterface = NULL;

int WindowHandler::m_width = 0;
int WindowHandler::m_height = 0;

bool WindowHandler::WAS_INIT = false;


/*DirectXHandler::~DirectXHandler()
{
	
    if( device != NULL)
        device->Release();
    if( d3dInterface != NULL)
        d3dInterface->Release();

}*/