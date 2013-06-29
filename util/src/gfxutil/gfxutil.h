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

#ifndef INCLUDED_GFXUTIL_H
#define INCLUDED_GFXUTIL_H

#include <windows.h>
/*#include "GL/gl.h"
#include "GL/wglext.h"
#include <GL/glext.h>*/
#include <d3d8.h>

/*#define MAX_PFORMATS 256
#define MAX_ATTRIBS  32

static bool WAS_INIT = FALSE;
static HDC  dc = NULL;		// Handle to a device context.
static HGLRC rc = NULL;		// Handle to a GL rendering context.

struct GLHardwareSurface
{
	HPBUFFERARB surface;
    unsigned int mode;      // Flags indicating the type of pbuffer.
    int          width;
    int          height;
	HDC			 dc;
	HGLRC		 rc;
};

bool initGlUtil();
struct GLHardwareSurface* createGLHardwareSurface(int width, int height, unsigned int mode);
void destroyGLHardwareSurface(struct GLHardwareSurface*);
*/



/* DIRECTX Init and stuff */
class WindowHandler
{
private:
	static HWND m_hWnd;

	static LPDIRECT3DDEVICE8 m_device ;
	static LPDIRECT3D8 m_d3dInterface ;

	static int m_width;
	static int m_height;

	static bool WAS_INIT ;

public:
	
	WindowHandler();
	//~WindowHandler();
	static void displayError();
	static HRESULT create(int width, int height, bool popup);
	static HRESULT destroy();
	static LPDIRECT3DDEVICE8 getDirectXDevice();
	static HWND hWnd();
};

			
#endif
