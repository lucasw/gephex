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

#include "cubesmodule.h"

#define MIN(a,b) ((a<b)?(a):(b))
#define MAX(a,b) ((a>b)?(a):(b))
#define MaxPoint(a,b) ((a.y > b.y) ? a : b)
#define MinPoint(a,b) ((b.y > a.y) ? a : b)
#define MaxPoint3(a,b,c) MaxPoint(MaxPoint(a,b),MaxPoint(b,c))
#define MidPoint3(a,b,c) MaxPoint(MinPoint(a,b),MinPoint(a,c))
#define MinPoint3(a,b,c) MinPoint(MinPoint(a,b),MinPoint(b,c))

#include <vector>

#ifndef M_PI
#define M_PI 3.1415
#endif

#include "basicmath.h"
#include "cube_table.h"

#define WIDTH 640
#define HEIGHT 480
static float	zBuffer[WIDTH*HEIGHT];

typedef struct _MyInstance {

  int dummy; // replace this with your favourite vars

} MyInstance, *MyInstancePtr;


// ---------------------------------------------------------------------------
// Local Structs
// ---------------------------------------------------------------------------
class Vertex 
{
 public:
  Vector Object;
  Vector World;
  Vector Camera;
  Vector normal;
  unsigned int xs, ys;	// screen coords
  float u, v;		// texture coords
  Color color;

  inline void object2world(Matrix m) { World = Object * m; }
  inline void world2camera(Matrix m) { Camera = World * m; }

  void make2D() 
    {
      float f = 256.0f / (Camera.z - 256.0f);
      xs = (int)(Camera.x * f) + WIDTH/2;
      ys = (int)(Camera.y * f) + HEIGHT/2;
    }
};

class Face 
{
 public:
  Vertex v1, v2, v3;
  Vector dUw, dVw, dw;       	// Original field gradients
  Vector TdUw, TdVw, Tdw;   	// transformed gradients

  float Area;

  Vector Normal;
  unsigned int faceColor;

  void rotate(Matrix m) {
    v1.Camera = v1.Camera * m;
    v2.Camera = v2.Camera * m;
    v3.Camera = v3.Camera * m;
  }

  void object2world(Matrix m)
    {
      v1.object2world(m);
      v2.object2world(m);
      v3.object2world(m);
    }

  void world2camera(Matrix m)
    {
      v1.world2camera(m);
      v2.world2camera(m);
      v3.world2camera(m);
    }

  void make2D()
    {
      v1.make2D();
      v2.make2D();
      v3.make2D();
    }

  void getNormal() 
    {
      Vector tmp;

      Vector a = (v2.Camera - v1.Camera);
      Vector b = (v3.Camera - v1.Camera);
										
      tmp.Set(	a.y*b.z-a.z*b.y, 
		a.z*b.x-a.x*b.z, 
		a.x*b.y-a.y*b.x);
													
      tmp.normalize();
      this->Normal = tmp;
    }
};

class Object 
{
 public:
  int numVerts;
  Vertex *verts;

  int numFaces;
  Face *faces;

  void quicksort(int left, int right, Object *o)
    {
      int i = left;
      int j = right;
      // int temp;
      // float m = o->faces[o->facez[(i + j) >> 1]].z;
      do
	{
	  // while (o->faces[o->facez[i]].z < m) i++;
	  // while (o->faces[o->facez[j]].z > m) j--;
	  if (i <= j)
	    {
	      // temp = o->facez[i]; o->facez[i] = o->facez[j]; o->facez[j] = temp;
	      i++;
	      j--;
	    }
	}
      while (!(i > j));

      if (left < j) quicksort(left, j, o);
      if (i < right) quicksort(i, right, o);
    }
};

struct tmpVector 
{
  public:
float x, y, z;
  unsigned int u,v;
  Color color;
};

// ---------------------------------------------------------------------------
// Polyfiller (trifiller)
// ---------------------------------------------------------------------------
inline void DrawScanline(uint_32* buffer, tmpVector p1, tmpVector p2, Color color)
{
  int x=0; float z = p1.z;
  float dz = (p1.z - p2.z) / (p1.x - p2.x);
  unsigned int c = color.getColor();
	
  for(x=(int)p1.x; x<=(int)p2.x; x++)
    {
      if(z>zBuffer[(int)p1.y*WIDTH+x])
	{
	  buffer[(int)p2.y*WIDTH+x] = c;
	}
      zBuffer[(int)p1.y*WIDTH+x] = z;
      z+=dz; 
    }
}

inline void g_tri_solid_z(uint_32* buffer, Vertex *v1, Vertex *v2, Vertex *v3)
{
  int xd1,yd1,xd2,yd2,i;
  float Lx,Rx;  // x
  float Lz,Rz;  // z
  float Lu,Ru;  // u
  float Lv,Rv;  // v
  float zd1,zd2;
  float ud1,ud2;
  float vd1,vd2;
  tmpVector L, R;

  tmpVector p1, p2, p3;
  p1.x = (int)v1->xs;
  p1.y = (int)v1->ys;
  p1.z = v1->Camera.z;

  p2.x = (int)v2->xs;
  p2.y = (int)v2->ys;
  p2.z = v2->Camera.z;

  p3.x = (int)v3->xs;
  p3.y = (int)v3->ys;
  p3.z = v3->Camera.z;

  tmpVector p1d,p2d,p3d;

  p1d = MinPoint3(p1,p2,p3);
  p2d = MidPoint3(p2,p3,p1);
  p3d = MaxPoint3(p3,p1,p2);

  if(p2.y < p1.y)
    {
      p1d=MinPoint3(p2,p1,p3);
      p2d=MidPoint3(p1,p3,p2);
    }

  xd1=(int)(p2d.x-p1d.x);
  yd1=(int)(p2d.y-p1d.y);
  zd1=(int)(p2d.z-p1d.z);
  ud1=(int)(p2d.u-p1d.u);
  vd1=(int)(p2d.v-p1d.v);

  xd2=(int)(p3d.x-p1d.x);
  yd2=(int)(p3d.y-p1d.y);
  zd2=(int)(p3d.z-p1d.z);
  ud2=(int)(p3d.u-p1d.u);
  vd2=(int)(p3d.v-p1d.v);

  if(yd1)
    {
      for(i=(int)p1d.y; i<=(int)(p2d.y-1); i++)
	{
	  Lx = p1d.x + ((i - p1d.y) * xd1) / yd1;
	  Rx = p1d.x + ((i - p1d.y) * xd2) / yd2;

	  Lz = p1d.z + ((i - p1d.y) * zd1) / yd1;
	  Rz = p1d.z + ((i - p1d.y) * zd2) / yd2;

	  Lu = p1d.u + ((i - p1d.u) * ud1) / yd1;
	  Ru = p1d.u + ((i - p1d.u) * ud2) / yd2;

	  Lv = p1d.v + ((i - p1d.v) * vd1) / yd1;
	  Rv = p1d.v + ((i - p1d.v) * vd2) / yd2;

	  if(Lx>Rx) 
	    {
	      L.x = Rx; L.z = Rz; L.u = (unsigned int)Ru; L.v = (unsigned int)Rv;
	      R.x = Lx; R.z = Lz; R.u = (unsigned int)Lu; L.v = (unsigned int)Ru;
	      L.y = i; R.y = i;
	    }
	  else
	    {
	      L.x = Lx; L.z = Lz; L.u = (unsigned int)Lu; L.v = (unsigned int)Lv;
	      R.x = Rx; R.z = Rz; R.u = (unsigned int)Ru; R.v = (unsigned int)Lu;
	      L.y = i; R.y = i;
	    }		

	  if(Lx!=Rx)
	    {
	      DrawScanline(buffer, L, R, v1->color);
	    }
	}
    }

  xd1=(int)(p3d.x-p2d.x);
  yd1=(int)(p3d.y-p2d.y);

  if(yd1)
    {
      for(i=(int)(p2d.y); i<=(int)(p3d.y-1); i++)
	{
	  Lx =   p1d.x   + ((i   - p1d.y)   * xd2) / yd2;
	  Rx =   p2d.x   + ((i   - p2d.y)   * xd1) / yd1;

	  Lz =   p1d.z   + ((i   - p1d.y)   * zd2) / yd2;
	  Rz =   p2d.z   + ((i   - p2d.y)   * zd1) / yd1;

	  Lu = p1d.u + ((i - p1d.u) * ud1) / yd1;
	  Ru = p1d.u + ((i - p1d.u) * ud2) / yd2;

	  Lv = p1d.v + ((i - p1d.v) * vd1) / yd1;
	  Rv = p1d.v + ((i - p1d.v) * vd2) / yd2;

	  if(Lx>Rx) 
	    {
	      L.x = Rx; L.z = Rz; L.u = (unsigned int)Ru; L.v = (unsigned int)Rv;
	      R.x = Lx; R.z = Lz; R.u = (unsigned int)Lu; L.v = (unsigned int)Ru;
	      L.y = i; R.y = i;
	    }
	  else
	    {
	      L.x = Lx; L.z = Lz; L.u = (unsigned int)Lu; L.v = (unsigned int)Lv;
	      R.x = Rx; R.z = Rz; R.u = (unsigned int)Ru; R.v = (unsigned int)Lu;
	      L.y = i; R.y = i;
	    }							

	  if(Lx!=Rx)
	    {
	      DrawScanline(buffer, L, R, v1->color);
	    }
	}
    }
}

//=============================================================================
//
// METABALL FUNCTIONS
//
//=============================================================================
template <typename type=double>
class point_3d
{
  public:
  type x, y, z;
};

template <typename type=double>
class TVertex
{
  private :
  type z;
  public :
  point_3d<type> vert;
  point_3d<type> normal;
};

#define MB_DETAIL	24
#define MB_CLEAR
#define MB_METABALLS	1.0f

TVertex<float>	 *g_pVertex;		
int							 g_dwVertices;	
point_3d<int>		 *g_pFace;			
int							 g_dwFaces;		
int							 *g_pVertexGrid;	
float						 *g_pPotGrid;		
float						 mbx1, mbx2, mby1, mby2, mbz1, mbz2;	
int					 		 mbnx, mbny, mbnz;				
int						 	 mbnx_x_mbny, mbnx_x_mbny_x_mbnz;
float						 mbk;						
float						 mbt;				

int edge[12*4] = { 0,0,0,0, 0,0,1,0, 0,0,0,1, 0,0,1,1,
		   1,0,0,0, 1,1,0,0, 1,0,0,1, 1,1,0,1,
		   2,0,0,0, 2,1,0,0, 2,0,1,0, 2,1,1,0 };

int g_dwMoveCam, g_dwZoomCam;
int g_dwCurX, g_dwCurY, g_dwMetaballWidth, g_dwMetaballHeight;
float g_fMetaballRadius, g_fMetaballPhi, g_fMetaballTheta;

#define GRIDX		10
#define GRIDY		10
#define STARTX		0.15f
#define STARTY		0.15f
#define STOPX		0.85f
#define STOPY		0.85f

#define f(i,j,k) g_pPotGrid[(i)+(j)*(mbnx+1)+(k)*(mbnx_x_mbny+mbnx+mbny+1)]

void InitMetaballs(void)
{
  g_dwMoveCam = 0;
  g_dwZoomCam = 0;
  g_fMetaballTheta = 0.0f;
  g_fMetaballPhi = (float)(M_PI / 2.0);
  g_fMetaballRadius = 10.0f;
}

Vertex t1, t2, t3, t4;

void ComputeMetaballs(void)
{
  int i, j, k;
  float x, y, z;
  float deltax, deltay, deltaz;
  float tx1, ty1, tz1;
  float tx2, ty2, tz2;
  float tx3, ty3, tz3;
  float tx4, ty4, tz4;
  int index;

  t1.Camera.x = tx1 = (float)sin(mbt * 2.1) * 2.5f;
  t1.Camera.y = ty1 = (float)sin(mbt * 1.3) * 2.5f;
  t1.Camera.z = tz1 = (float)sin(mbt * 3.1) * 2.5f;
  t2.Camera.x = tx2 = (float)sin(mbt * 2.5) * 2.0f;
  t2.Camera.y = ty2 = (float)sin(mbt * 2.7) * 2.0f;
  t2.Camera.z = tz2 = (float)sin(mbt * 1.4) * 2.0f;
  t3.Camera.x = tx3 = (float)sin(mbt * 3.3) * 1.0f;
  t3.Camera.y = ty3 = (float)sin(mbt * 1.1) * 1.0f;
  t3.Camera.z = tz3 = (float)sin(mbt * 1.7) * 1.0f;
  t4.Camera.x = tx4 = (float)cos(mbt * 5.2) * 1.0f;
  t4.Camera.y = ty4 = (float)cos(mbt * 3.7) * 1.5f;
  t4.Camera.z = tz4 = (float)cos(mbt * 4.1) * 1.5f;

  deltax = (mbx2 - mbx1) / mbnx;
  deltay = (mby2 - mby1) / mbny;
  deltaz = (mbz2 - mbz1) / mbnz;
  z = mbz1;

  for (k=0; k<=mbnz; k++) 
    {
      y = mby1;
      for (j=0; j<=mbny; j++) 
	{
	  x = mbx1;
	  for (i=0; i<=mbnx; i++) 
	    {
	      index = i+j*(mbnx+1)+k*(mbnx+1)*(mbny+1);
	      g_pPotGrid[index] = 0.0;
	      g_pPotGrid[index] += 
		MB_METABALLS * MB_METABALLS / ((x - tx1) * (x - tx1) + (y + ty1) * (y + ty1) + (z - tz1) * (z - tz1)) +
		MB_METABALLS * MB_METABALLS / ((x - tx2) * (x - tx2) + (y + ty2) * (y + ty2) + (z - tz2) * (z - tz2)) +
		MB_METABALLS * MB_METABALLS / ((x - tx3) * (x - tx3) + (y + ty3) * (y + ty3) + (z - tz3) * (z - tz3)) +
		MB_METABALLS * MB_METABALLS / ((x - tx4) * (x - tx4) + (y + ty4) * (y + ty4) + (z - tz4) * (z - tz4));
	      x += deltax;
	    }
	  y += deltay;
	}
      z += deltaz;
    }
}

void MetaballsInitMarchingCubes(float x1, float x2, float y1, float y2, float z1, float z2, int m, int n,
				int p, float pot)
{
  int i, j, k;

  g_pVertexGrid = new int[3 * m * n * p];
  g_pVertex = new TVertex<float>[3 * m * n * p];
  g_pFace = new point_3d<int>[4 * m * n * p];
  g_pPotGrid = new float[4 * (m + 1) * (n + 1) * (p + 1)];

  mbx1 = x1;
  mbx2 = x2;
  mbnx = m;
  mby1 = y1; 
  mby2 = y2; 
  mbny = n;
  mbz1 = z1; 
  mbz2 = z2; 
  mbnz = p;
  mbnx_x_mbny = mbnx * mbny;
  mbnx_x_mbny_x_mbnz = mbnx * mbny * mbnz;
  mbk  = pot;
  mbt  = 0.0;
  for (k=0; k<=mbnz; k++)
    {
      for (j=0; j<=mbny; j++)
	{
	  for (i=0; i<=mbnx; i++)
	    {
	      g_pPotGrid[i + j * (mbnx + 1) + k * (mbnx + 1) * (mbny + 1)] = 0.0;
	    }
	}
    }
}

void MarchingCubesMetaballs(void)
{
  float deltax,deltay,deltaz;
  float x,y,z;
  float ax,ay,az,bx,by,bz,nx,ny,nz,n;
  float f1,f2;
  int i,j,k,l;
  int v1,v2,v3;
  float coef;
  int index;
  int eindex;	

  g_dwVertices = 0;
  g_dwFaces = 0;
  ComputeMetaballs();

  deltax = (mbx2 - mbx1) / mbnx;
  deltay = (mby2 - mby1) / mbny;
  deltaz = (mbz2 - mbz1) / mbnz;
  z = mbz1;

  for (k=0; k<mbnz; k++) 
    {
      y = mby1;
      for (j=0; j<mbny; j++) 
	{
	  x = mbx1;
	  for (i=0; i<mbnx; i++) 
	    {
	      index = i + j * (mbnx + 1) + k * (mbnx_x_mbny + mbnx + mbny + 1);
	      f1 = g_pPotGrid[index];
	      f2 = g_pPotGrid[index+1];
	      if ( ((f1 >= mbk) && (f2 < mbk)) || ((f1 < mbk) && (f2 >= mbk)))
		{
		  g_pVertexGrid[i + j * mbnx + k * mbnx_x_mbny + 0] = g_dwVertices;
		  g_pVertex[g_dwVertices].normal.x = (0.0f);
		  g_pVertex[g_dwVertices].normal.y = (0.0f);
		  g_pVertex[g_dwVertices].normal.z = (0.0f);

		  coef = (mbk - f1) / (f2 - f1);

		  g_pVertex[g_dwVertices].vert.x = (x + deltax * coef);
		  g_pVertex[g_dwVertices].vert.y = (y);
		  g_pVertex[g_dwVertices].vert.z = (z);

		  g_dwVertices++;
		}

	      f1 = g_pPotGrid[index];
	      f2 = g_pPotGrid[index + mbnx + 1];

	      if (((f1 >= mbk) && (f2 < mbk)) || ((f1 < mbk) && (f2 >= mbk))) 
		{
		  g_pVertexGrid[i+j*mbnx+k*mbnx_x_mbny+mbnx_x_mbny_x_mbnz] = g_dwVertices;
		  g_pVertex[g_dwVertices].normal.x = (0.0f);
		  g_pVertex[g_dwVertices].normal.y = (0.0f);

		  g_pVertex[g_dwVertices].normal.z = (0.0f);

		  coef = (mbk - f1) / (f2 - f1);

		  g_pVertex[g_dwVertices].vert.x = (x);
		  g_pVertex[g_dwVertices].vert.y = (y + deltay * coef);
		  g_pVertex[g_dwVertices].vert.z = (z);
					
		  g_dwVertices++;
		}

	      f1 = g_pPotGrid[index];
	      f2 = g_pPotGrid[index + mbnx_x_mbny + mbnx + mbny + 1];

	      if (((f1 >= mbk) && (f2 < mbk)) || ((f1 < mbk) && (f2 >= mbk)) ) 
		{
		  g_pVertexGrid[i+j*mbnx+k*mbnx_x_mbny+mbnx_x_mbny_x_mbnz+mbnx_x_mbny_x_mbnz] = g_dwVertices;
		  g_pVertex[g_dwVertices].normal.x = (0.0f);
		  g_pVertex[g_dwVertices].normal.y = (0.0f);

		  g_pVertex[g_dwVertices].normal.z = (0.0f);

		  coef = (mbk-f1) / (f2-f1);

		  g_pVertex[g_dwVertices].vert.x = (x);
		  g_pVertex[g_dwVertices].vert.y = (y);
		  g_pVertex[g_dwVertices].vert.z = (z + deltaz * coef);

		  g_dwVertices++;
		} 	
	      x += deltax;
	    }
	  y += deltay;
	}
      z += deltaz;
    }

  z = mbz1;

  for (k=0; k<mbnz-1; k++) 
    {
      y = mby1;
      for (j=0; j<mbny-1; j++)
	{
	  x = mbx1;
	  for (i=0; i<mbnx-1; i++) 
	    {
	      index  = ((f(i  ,j  ,k  ) >= mbk)?0x01:0x00);
	      index |= ((f(i+1,j  ,k  ) >= mbk)?0x02:0x00);
	      index |= ((f(i  ,j+1,k  ) >= mbk)?0x04:0x00);
	      index |= ((f(i+1,j+1,k  ) >= mbk)?0x08:0x00);
	      index |= ((f(i  ,j  ,k+1) >= mbk)?0x10:0x00);
	      index |= ((f(i+1,j  ,k+1) >= mbk)?0x20:0x00);
	      index |= ((f(i  ,j+1,k+1) >= mbk)?0x40:0x00);
	      index |= ((f(i+1,j+1,k+1) >= mbk)?0x80:0x00);
	      index *= 12;

	      for (l=0; l<4; l++)
		{
		  if (g_pMetaballTriangle[index+l*3] != g_pMetaballTriangle[index+l*3+1])
		    {
		      eindex = g_pMetaballTriangle[index + l * 3] * 4;
		      g_pFace[g_dwFaces].x = (g_pVertexGrid[i + edge[eindex + 1] + (j + edge[eindex + 2]) * mbnx + 
							   (k + edge[eindex + 3]) * mbnx_x_mbny + edge[eindex] * mbnx_x_mbny_x_mbnz]);
		      v1 = g_pFace[g_dwFaces].x;

		      eindex = g_pMetaballTriangle[index + l * 3 + 1] * 4;
		      g_pFace[g_dwFaces].y = (g_pVertexGrid[i + edge[eindex + 1] + (j + edge[eindex + 2]) * mbnx + 
							   (k + edge[eindex + 3]) * mbnx_x_mbny + edge[eindex] * mbnx_x_mbny_x_mbnz]);
		      v2 = g_pFace[g_dwFaces].y;

		      eindex = g_pMetaballTriangle[index + l * 3 + 2] * 4;
		      g_pFace[g_dwFaces].z = (g_pVertexGrid[i + edge[eindex + 1] + (j + edge[eindex + 2]) * mbnx + 
							   (k + edge[eindex + 3]) * mbnx_x_mbny + edge[eindex] * mbnx_x_mbny_x_mbnz]);
		      v3 = g_pFace[g_dwFaces].z;

		      ax = g_pVertex[v2].vert.x - g_pVertex[v1].vert.x;
		      ay = g_pVertex[v2].vert.y - g_pVertex[v1].vert.y;
		      az = g_pVertex[v2].vert.z - g_pVertex[v1].vert.z;
		      bx = g_pVertex[v3].vert.x - g_pVertex[v1].vert.x;
		      by = g_pVertex[v3].vert.y - g_pVertex[v1].vert.y;
		      bz = g_pVertex[v3].vert.z - g_pVertex[v1].vert.z;
		      nx = ay * bz - az * by;
		      ny = az * bx - ax * bz;
		      nz = ax * by - ay * bx;
		      n = sqrt(nx * nx + ny * ny + nz * nz);
		      if (n != 0.0f)
			{
			  n = 1.0f / n;
			  nx *= n;
			  ny *= n;
			  nz *= n;
			}

		      g_pVertex[v1].normal.x = (g_pVertex[v1].normal.x + nx);
		      g_pVertex[v1].normal.y = (g_pVertex[v1].normal.y + ny);
		      g_pVertex[v1].normal.z = (g_pVertex[v1].normal.z + nz);

		      g_pVertex[v2].normal.x = (g_pVertex[v2].normal.x + nx);
		      g_pVertex[v2].normal.y = (g_pVertex[v2].normal.y + ny);
		      g_pVertex[v2].normal.z = (g_pVertex[v2].normal.z + nz);

		      g_pVertex[v3].normal.x = (g_pVertex[v3].normal.x + nx);
		      g_pVertex[v3].normal.y = (g_pVertex[v3].normal.y + ny);
		      g_pVertex[v3].normal.z = (g_pVertex[v3].normal.z + nz);

		      g_dwFaces++;
		    }
		}
	      x += deltax;
	    }
	  y += deltay;
	}
      z += deltaz;
    }

  for (i=0; i<g_dwVertices; i++) 
    {
      n = sqrt(g_pVertex[i].normal.x * g_pVertex[i].normal.x +
	       g_pVertex[i].normal.y * g_pVertex[i].normal.y +
	       g_pVertex[i].normal.z * g_pVertex[i].normal.z);

      if (n != 0.0f) 
	{
	  n = 1.0f / n;
	  g_pVertex[i].normal.x = (g_pVertex[i].normal.x * n);
	  g_pVertex[i].normal.y = (g_pVertex[i].normal.y * n);
	  g_pVertex[i].normal.z = (g_pVertex[i].normal.z * n);
	}
    }
}

void RenderMetaballs(Object *o, float off, float totalTime)
{
  int i;

  std::vector<Face> balls;
  balls.clear();

  mbt += off;
  MarchingCubesMetaballs();

  for (i=0; i<g_dwFaces; i++)
    {
      Face tmp1;

      tmp1.v1.Object.x = g_pVertex[g_pFace[i].x].vert.x; 
      tmp1.v1.Object.y = g_pVertex[g_pFace[i].x].vert.y;
      tmp1.v1.Object.z = g_pVertex[g_pFace[i].x].vert.z;
      tmp1.v1.u = (g_pVertex[g_pFace[i].x].normal.x + 1.0f) / 2.0f;
      tmp1.v1.v = (g_pVertex[g_pFace[i].x].normal.y + 1.0f) / 2.0f;
																						
      tmp1.v2.Object.x = g_pVertex[g_pFace[i].y].vert.x;
      tmp1.v2.Object.y = g_pVertex[g_pFace[i].y].vert.y;
      tmp1.v2.Object.z = g_pVertex[g_pFace[i].y].vert.z;
      tmp1.v2.u = (g_pVertex[g_pFace[i].y].normal.x + 1.0f) / 2.0f;
      tmp1.v2.v = (g_pVertex[g_pFace[i].y].normal.y + 1.0f) / 2.0f;

      tmp1.v3.Object.x = g_pVertex[g_pFace[i].z].vert.x;
      tmp1.v3.Object.y = g_pVertex[g_pFace[i].z].vert.y;
      tmp1.v3.Object.z = g_pVertex[g_pFace[i].z].vert.z;
      tmp1.v3.u = (g_pVertex[g_pFace[i].z].normal.x + 1.0f) / 2.0f;
      tmp1.v3.v = (g_pVertex[g_pFace[i].z].normal.y + 1.0f) / 2.0f;

      balls.push_back(tmp1);
    } 
	
  o->numFaces=balls.size();

  // if(o->faces) delete o->faces;
  // o->faces = new Face[o->numFaces]; 

  for(unsigned int j=0; j<balls.size();j++) 
    {
      o->faces[j] = balls[j];
    }
}

inline void solid_face(uint_32 *buffer, Face *f)
{
  g_tri_solid_z(buffer, &f->v1, &f->v2, &f->v3);
}

// ---------------------------------------------------------------------------
// Main Part
// ---------------------------------------------------------------------------

static Object balls;	


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

  // Add your initialization here

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  // Add your effect here!

  int xsize, ysize; 
	uint_32 *dst;
  xsize = inst->out_r->xsize;
  ysize = inst->out_r->ysize;
  dst = inst->out_r->framebuffer;
	
  memset(dst, 0, WIDTH*HEIGHT*4);
  for (int indexI=0; indexI<WIDTH*HEIGHT; indexI++) { zBuffer[indexI]=-999999999.0f; }

  RenderMetaballs(&balls, .1f, .1f);				// render first frame

	// object 2 world
	float angle = (inst->in_offset_r->number/(float)(UINT_MAX))*360;
	Matrix o2w; o2w.rotate(angle, angle, angle);

	// world 2 camera
	Matrix w2c; w2c.identity(); w2c.scale(25.0, 25.0, 25.0);
	Vector light = Vector(10.0f, 10.0f, 10.0f) * o2w;

	for(signed int i=0; i<balls.numFaces;i++)
	{
		balls.faces[i].object2world(o2w);
		balls.faces[i].world2camera(w2c);
		balls.faces[i].make2D();
		balls.faces[i].getNormal();

		if((Vector(0, 0, -1)%balls.faces[i].Normal)<0)
		{
			int color = (int)(0xff * (1.0 - cos(Vector(0,0,1)%balls.faces[i].Normal)));
			balls.faces[i].v1.color = color << 16 | color << 8 | color;

			solid_face(dst, &balls.faces[i]);		// flatshaded
			// wire_face(pixel, &balls.faces[i]); // wireframe
			// triangle(pixel, &balls.faces[i]);	// envmapped
			// _t_tri(pixel, balls.faces[i]);
		}
	}

}

