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

#ifndef __basic_h
#define __basic_h

#include <math.h>

#define CLAMPF(x) ((x<0.0f)?0.0f:(x>1.0f?1.0f:x))

class Point {
public:
	float x, y;
	float z;	// dummy;
	int getU() {
		int U=(int)x;
		while(U<0) U+=256;
		return (U)%256; 
	}
	int getV() { 
		int V=(int)y;
		while(V<0) V+=256;
		return (V)%256; 
		// return ((int)fabs(y))%256; 
	}

	Point() { x=0.0f; y=0.0f; }
	Point(float X, float Y) { x=X; y=Y; }
};

class Matrix {
public:
	float d11, d12, d13, d14;
	float d21, d22, d23, d24;
	float d31, d32, d33, d34;
	float d41, d42, d43, d44;

	Matrix() { identity(); }
	void identity() {
		d11=d12=d13=d14=0.0f;
		d21=d22=d23=d24=0.0f;
		d31=d32=d33=d34=0.0f;
		d41=d42=d43=d44=0.0f;
		d11=d22=d33=d44=1.0f;
	}

	Matrix rotate(float x, float y, float z) {
		float sx=sin(x); float sy=sin(y); float sz=sin(z);
		float cx=cos(x); float cy=cos(y); float cz=cos(z);

		d11=cy*cz; 			d12=cy*sz; 			d13=-sy;
		d21=sx*sy*cz-cx*sz; d22=sx*sy*sz+cx*cz; d23=sx*cy;
		d31=cx*sy*cz+sx*sz; d32=cx*sy*sz-sx*cz; d33=cx*cy;
		return *this;
	}
	Matrix translate(float x, float y, float z) {
		identity();
		d41=x; d42=y; d43=z;
		return *this;
	}
	Matrix scale(float x, float y, float z) {
		identity();
		d11=x; d22=y; d33=z;
		return *this;
	}
};

class Vector {
friend class Matrix;
public:
	float x, y, z;
	Vector() { Vector(0.0f, 0.0f, 0.0f); }
	Vector(float _x, float _y, float _z) { x=_x; y=_y; z=_z; }
	void Set(float _x, float _y, float _z) { x=_x; y=_y; z=_z; }
	Vector operator*(const float &c) { return Vector(x *   c, y *   c, z *   c); }
	Vector operator*(const Vector &c) { return Vector(x * c.x, y * c.y , z * c.z); }
	Vector operator+(const Vector &c) { return Vector(x + c.x, y + c.y, z + c.z); }
	Vector operator-(const Vector &c) { return Vector(x - c.x, y - c.y, z - c.z); }
	void normalize() { float len = (float)sqrt(x*x + y*y + z*z); x/=len; y/=len; z/=len; }
	void negate() { x=-x; y=-y; z=-z; }
	float len() { return sqrt(x*x + y*y + z*z); }
	inline Vector operator*(Matrix m)
	{
        Vector r;
        r.x=x*m.d11+ y*m.d21+ z*m.d31+ m.d41;
        r.y=x*m.d12+ y*m.d22+ z*m.d32+ m.d42;
        r.z=x*m.d13+ y*m.d32+ z*m.d33+ m.d43;
        // *this=r;
        return r;
	}
	float operator%(const Vector a) { return ( (x*a.x + y*a.y + z*a.z) ); }		// dot product
};

class Color {
public:
	float a, r, g, b;

	Color() { clear(); }
//	Color(float _a, float _r, float _g, float _b) { a=_a; r=_r; g=_g; b=_b; }
	Color(const float _a, const float _r, const float _g, const float _b) { a=_a; r=_r; g=_g; b=_b; }
	Color(unsigned int i) { 

		unsigned char *t = (unsigned char*)&i; 

		setColor(t[3], t[2], t[1], t[0]);

/*		a=t[3]; 

		r=t[2]; 

		g=t[1]; 

		b=t[0]; 

*/	}
	void clear() { a=r=g=b=0.0f; }

	unsigned int getColor() { 
		unsigned char ac, rc, gc, bc;
		ac = (unsigned char)(255.0*((a>=1.0f)?1.0f:a));
		rc = (unsigned char)(255.0*((r>=1.0f)?1.0f:r));
		gc = (unsigned char)(255.0*((g>=1.0f)?1.0f:g));
		bc = (unsigned char)(255.0*((b>=1.0f)?1.0f:b));
		return (ac<<24) + (rc<<16) + (gc<<8) + bc;
	}

	void setColor(unsigned char _a, unsigned char _r, unsigned char _g, unsigned char _b) {
		float temp = 1 / 255.0f;
		a = temp * _a;
		r = temp * _r;
		g = temp * _g;
		b = temp * _b;
	}

	Color operator*(const float &c) { return Color(a * c, r * c, g * c, b * c); }
	Color operator+(const Color &c) { return Color(a + c.a, r + c.r, g + c.g, b + c.b); }
	Color operator*(const Color &c) { return Color(a * c.a, r * c.r, g * c.g, b * c.b); }
	Color operator-(const Color &c) { return Color(a - c.a, r - c.r, g - c.g, b - c.b); }
	Color operator/(const float &c) { return Color(a / c, r / c, g / c, b / c); }
};

#endif
