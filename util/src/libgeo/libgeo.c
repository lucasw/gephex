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

#include "libgeo.h"

#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>


static double sign(double d)
{
  return d >= 0 ? 1 : -1;
}

int geo_intersect_lines(struct geo_Point* p1, struct geo_Point* d1,
			struct geo_Point* p2, struct geo_Point* d2,
			double* lambda, double* mue)
{
  /*const double EPS = 0.0000001;
  double d1x = d1->x / FIXEDPNT_SCALE;
  double d1y = d1->y / FIXEDPNT_SCALE;
  double d2x = d2->x / FIXEDPNT_SCALE;
  double d2y = d2->y / FIXEDPNT_SCALE;
  double p1x = p1->x / FIXEDPNT_SCALE;
  double p1y = p1->y / FIXEDPNT_SCALE;
  double p2x = p2->x / FIXEDPNT_SCALE;
  double p2y = p2->y / FIXEDPNT_SCALE;


  double delta = d1x*d2y - d1y*d2x;
  if (fabs(delta) < EPS)
      return 0;

  *lambda = ((p2x - p1x)*d2y - (p2y - p1y)*d2x) / delta;

  if (fabs(d2x) > EPS)
    *mue = (p1x - p2x + *lambda*d1x) / d2x;
  else
    *mue = (p1y - p2y + *lambda*d1y) / d2y;
*/
  const double EPS = 0.000001;

  double delta = d1->x * d2->y - d1->y * d2->x;

  if (fabs(delta) < EPS)
    return 0;

  *lambda = ((p2->x - p1->x)*d2->y - (p2->y - p1->y)*d2->x) / delta;

  if (!mue)
    return 1;

  if (fabs(d2->x) > fabs(d2->y))
    *mue = (p1->x - p2->x + *lambda * d1->x) / d2->x;
  else
    *mue = (p1->y - p2->y + *lambda * d1->y) / d2->y;

  return 1;
}

void geo_clip_poly_with_line(struct geo_Point* poly, int *num_points,
			     struct geo_Point* point,
			     struct geo_Point* dir,
			     double orientation)
{
  const double EPS = 0.000001;
  int p1, n;
  struct geo_Point normal = { -dir->y, dir->x };
  struct geo_Point* new_poly = (struct geo_Point*) malloc((*num_points *2) * sizeof(*new_poly));
  int index = 0;

  n = *num_points;
  for (p1 = 0; p1 < n; ++p1)
    {
      int p2 = (p1 + 1) % n;
      struct geo_Point diff;
      double side1, side2;

      geo_point_sub(poly+p1, point, &diff);
      side1 = geo_point_scalar_prod(&diff, &normal);
      geo_point_sub(poly+p2, point, &diff);
      side2 = geo_point_scalar_prod(&diff, &normal);

      if (sign(side1) == orientation)
	{
	  memcpy(new_poly+index, poly+p1, sizeof(*poly));
	  ++index;
	}

      if (sign(side1) != sign(side2) && fabs(side2) > EPS)
	{
	  // points on different sides of (point+lambda*dir)
	  // => (point+lambda*dir) intersects [p1,p2]
	  double lambda;
	  int ok;
	  geo_point_sub(poly+p2, poly+p1, &diff);

	  ok = geo_intersect_lines(poly + p1, &diff, point, dir, &lambda, 0);
	  assert(ok); //lines must intersect here
	  assert(0 <= lambda && lambda <= 1.0); // must be between p1 and p2

	  // this test assures that corner points are not included twice
	  if (!((lambda < EPS          && sign(side1) == orientation) ||
		((lambda > 1.0-EPS)    && sign(side2) == orientation)))
	    {
	      new_poly[index].x = (poly[p1].x 
				   + lambda * diff.x);
	      
	      new_poly[index].y = (poly[p1].y 
				   + lambda * diff.y);
	      ++index;
	    }
	}
    }

  *num_points = index;
  memcpy(poly, new_poly, sizeof(*poly)*index);
  free(new_poly);
}
			

double geo_poly_get_orientation(struct geo_Point* p, int n)
{
  struct geo_Point diff, normal;
  geo_point_sub(p + 1, p + 0, &diff);
  normal.x = -diff.y;
  normal.y = diff.x;

  geo_point_sub(p + 2, p + 0, &diff);
  
  return sign(geo_point_scalar_prod(&normal, &diff));
}

int geo_intersect_polygons(struct geo_Point* dst, int *n,
			   struct geo_Point* r1, int n1,
			   struct geo_Point* r2, int n2)
{
  int num_points = n1;
  int i;
  double orientation = geo_poly_get_orientation(r1, n1);

  memcpy(dst, r1, sizeof(*r1)* num_points);

  for (i = 0; i < n2; ++i)
    {
      int next_i;
      struct geo_Point delta;

      next_i = (i+1) % 4;

      geo_point_sub(r2 + next_i, r2 + i, &delta);
      
      geo_clip_poly_with_line(dst, &num_points, r2 + i, &delta, orientation);

      // is the poly degenerate?
      if (num_points <= 2) {
	*n = 0;
	return 0;
      }
    }

  *n = num_points;
  return 1;
}


/**
 * Intersects the line (p+d*lambda) with a convex poly.
 *
 * If the polygon is not convex and there are more than two
 * intersections, than just 2 are returned.
 *
 * Returns 1 if intersection is found, 0 otherwise.
 * If 1 is returned, *lambda1 <= *lambda2 is assured
 */
int geo_intersect_poly_with_line(struct geo_Point* poly, int n,
				 struct geo_Point* p,
				 struct geo_Point* d,
				 double* lambda1, double* lambda2)
{
  double EPS = 0.000001;
  int i;
  double lambda[2];
  int lambda_index = 0;

  for (i = 0; i < n; ++i)
    {
      int next_i = (i+1) % n;
      struct geo_Point diff;
      int ok;
      double mue, lam;

      geo_point_sub(poly+next_i, poly+i, &diff);
      ok = geo_intersect_lines(poly+i, &diff, p, d, &mue, &lam);
      if (ok && mue >= 0 && mue < 1.0-EPS && lambda_index < 2)
	{
	  lambda[lambda_index] = lam;
	  lambda_index++;
	}
    }

  if (lambda_index == 0)
    return 0;
  else if (lambda_index == 1)
    {
      *lambda1 = *lambda2 = lambda[0];
    }
  else if (lambda_index == 2)
    {
      if (lambda[0] < lambda[1])
	{
	  *lambda1 = lambda[0];
	  *lambda2 = lambda[1];
	}
      else
	{
	  *lambda1 = lambda[1];
	  *lambda2 = lambda[0];
	}
    }
  else
    assert(!"Mist hier!!!");

  return 1;
}


int poly_equals(struct geo_Point* p1, int n1,
		struct geo_Point* p2, int n2,
		double EPS)
{
  int i;
  if (n1 != n2)
    return 0;

  for (i = 0; i < n1; ++i)
    {
      if (fabs(p1[i].x - p2[i].x) > EPS || fabs(p1[i].y - p2[i].y) > EPS)
	{
	  return 0;
	}
    }

  return 1;
}
