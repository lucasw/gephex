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

#ifndef INCLUDED_LIBGEO_H
#define INCLUDED_LIBGEO_H

#include "basic_types.h"

/**
 * Simple geo library that works with double precision arithmetic.
 */

struct geo_Point {
  double x;
  double y;
};

/**
 * Intersects two lines (p1+lambda*d1) and (p2+lambda*d2).
 * If they are parallel, 0 is returned.
 * Else, *lambda1 contains the value s.t.
 *  (x_intersect, y_intersect) = p1 + *lambda1 * d1.
 */
int geo_intersect_lines(struct geo_Point* p1, struct geo_Point* d1,
			struct geo_Point* p2, struct geo_Point* d2,
			double* lambda, double* mue);

/**
 * Clips a polygon to a line.
 * num_points must point to an int that contains the number of
 * points in poly.
 *
 * orientation is the orientation of poly as returned by
 * geo_poly_get_orientation().
 *
 * After the function call, *num_points contains the new number of points.
 * poly must contain at least place for two extra points.
 */
void geo_clip_poly_with_line(struct geo_Point* poly, int *num_points,
			     struct geo_Point* point,
			     struct geo_Point* dir, double orientation);


/**
 * Intersects r1 with r2 and returns the result in dst.
 * Returns 1 on success and 0 if the intersection area is 0.
 * dst should contain space for max(n1,n2)*2 points (worst case).
 *
 * If the two polygons intersect only along one edge or in one point,
 * 0 is returned.
 *
 * *n contains the number of points of dst at the end.
 */
int geo_intersect_polygons(struct geo_Point* dst, int *n,
			   struct geo_Point* r1, int n1,
			   struct geo_Point* r2, int n2);



/**
 * Intersects the line (p+d*lambda) with a convex poly.
 * Returns 1 if intersection is found, 0 otherwise.
 * If 1 is returned, *lambda1 <= *lambda2 is assured
 */
int geo_intersect_poly_with_line(struct geo_Point* poly, int n,
				 struct geo_Point* p,
				 struct geo_Point* d,
				 double* lambda1, double* lambda2);

/**
 * Returns -1, 0, or 1.
 * 0 is error.
 */
double geo_poly_get_orientation(struct geo_Point* p, int n);


static double geo_point_scalar_prod(struct geo_Point* p1,
				    struct geo_Point* p2)
{
  return p1->x*p2->x + p1->y*p2->y;
}

static void geo_point_sub(struct geo_Point* p1, struct geo_Point* p2,
			  struct geo_Point* dst)
{
  dst->x = p1->x - p2->x;
  dst->y = p1->y - p2->y;
}



int poly_equals(struct geo_Point* p1, int n1,
		struct geo_Point* p2, int n2,
		double EPS);

#endif
