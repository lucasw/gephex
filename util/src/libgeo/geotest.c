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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void poly_print(struct geo_Point* pi, int num_points)
{
  int i;
  for (i = 0; i < num_points; ++i) {
    printf("pi_%i = (%f, %f)\n", i, pi[i].x , pi[i].y );
  }
}

static int test_scalar_prod1(double EPS)
{
  struct geo_Point v1 = {-1, 1/ 2.0}; // (-1, 0.5)
  struct geo_Point v2 = {-3/ 2.0, 3/ 2.0}; // (-1.5, 1.5)

  double expected = 2.25;
  double result = geo_point_scalar_prod(&v1, &v2);
  if (fabs(result - expected) > EPS)
    {
      printf("Result: %f but expected: %f\n", result ,
	     expected );
      return 0;
    }

  return 1;
}

static int test_intersect1(double EPS)
{
  struct geo_Point p1[4];
  struct geo_Point p2[4];
  struct geo_Point pi[8];
  struct geo_Point psoll[4];
  int num_points;
  int ok;

  p1[0].x = 1; p1[0].y = 1;
  p1[1].x = 3; p1[1].y = 1;
  p1[2].x = 3; p1[2].y = 3;
  p1[3].x = 1; p1[3].y = 3;

  p2[0].x = 2; p2[0].y = 2;
  p2[1].x = 4; p2[1].y = 2;
  p2[2].x = 4; p2[2].y = 4;
  p2[3].x = 2; p2[3].y = 4;

  ok = geo_intersect_polygons(pi, &num_points,
			      p1, 4,
			      p2, 4);

  if (!ok)
    return 0;

  
  psoll[0].x = 3; psoll[0].y = 2;
  psoll[1].x = 3; psoll[1].y = 3;
  psoll[2].x = 2; psoll[2].y = 3;
  psoll[3].x = 2; psoll[3].y = 2;

  if (!poly_equals(pi, num_points, psoll, 4, EPS))
  {
    printf("Result:\n");
    poly_print(pi, num_points);
    printf("\nBut expected:\n");
    poly_print(psoll, 4);
    return 0;
  }

  return 1;
}

static int test_intersect2(double EPS)
{
  struct geo_Point p1[4];
  struct geo_Point p2[4];
  struct geo_Point pi[8];
  struct geo_Point psoll[8];
  int num_points;
  int ok;

  p1[0].x = 1; p1[0].y = 1;
  p1[1].x = 3; p1[1].y = 1;
  p1[2].x = 3; p1[2].y = 3;
  p1[3].x = 1; p1[3].y = 3;

  p2[0].x = 2; p2[0].y = 1/ 2.0;
  p2[1].x = 7/ 2.0; p2[1].y = 2;
  p2[2].x = 2; p2[2].y = 7/ 2.0;
  p2[3].x = 1/ 2.0; p2[3].y = 2;

  ok = geo_intersect_polygons(pi, &num_points,
			      p1, 4,
			      p2, 4);

  if (!ok)
    return 0;

  
  psoll[0].x = 1.5; psoll[0].y =   1;
  psoll[1].x = 2.5; psoll[1].y =   1;
  psoll[2].x =   3; psoll[2].y = 1.5;
  psoll[3].x =   3; psoll[3].y = 2.5;
  psoll[4].x = 2.5; psoll[4].y =   3;
  psoll[5].x = 1.5; psoll[5].y =   3;
  psoll[6].x =   1; psoll[6].y = 2.5;
  psoll[7].x =   1; psoll[7].y = 1.5;

  if (!poly_equals(pi, num_points, psoll, 8, EPS))
  {
    printf("Result:\n");
    poly_print(pi, num_points);
    printf("\nBut expected:\n");
    poly_print(psoll, 8);
    return 0;
  }

  return 1;
}

// like test_intersect2, but p1 and p2 exchanged
static int test_intersect3(double EPS)
{
  struct geo_Point p1[4];
  struct geo_Point p2[4];
  struct geo_Point pi[8];
  struct geo_Point psoll[8];
  int num_points;
  int ok;

  p1[0].x = 1; p1[0].y = 1;
  p1[1].x = 3; p1[1].y = 1;
  p1[2].x = 3; p1[2].y = 3;
  p1[3].x = 1; p1[3].y = 3;

  p2[0].x =   2; p2[0].y = 0.5;
  p2[1].x = 3.5; p2[1].y =   2;
  p2[2].x =   2; p2[2].y = 3.5;
  p2[3].x = 0.5; p2[3].y =   2;

  ok = geo_intersect_polygons(pi, &num_points,
			      p2, 4,
			      p1, 4);

  if (!ok)
    return 0;

  
  psoll[0].x = 2.5; psoll[0].y =   1;
  psoll[1].x =   3; psoll[1].y = 1.5;
  psoll[2].x =   3; psoll[2].y = 2.5;
  psoll[3].x = 2.5; psoll[3].y =   3;
  psoll[4].x = 1.5; psoll[4].y =   3;
  psoll[5].x =   1; psoll[5].y = 2.5;
  psoll[6].x =   1; psoll[6].y = 1.5;
  psoll[7].x = 1.5; psoll[7].y =   1;

  if (!poly_equals(pi, num_points, psoll, 8, EPS))
  {
    printf("Result:\n");
    poly_print(pi, num_points);
    printf("\nBut expected:\n");
    poly_print(psoll, 8);
    return 0;
  }

  return 1;
}

// the two polygons touch in one point
static int test_intersect4(double EPS)
{
  struct geo_Point p1[4];
  struct geo_Point p2[4];
  struct geo_Point pi[8];
  struct geo_Point psoll[4];
  int num_points;
  int ok;

  p1[0].x = 1; p1[0].y = 1;
  p1[1].x = 3; p1[1].y = 1;
  p1[2].x = 3; p1[2].y = 3;
  p1[3].x = 1; p1[3].y = 3;

  p2[0].x = 3; p2[0].y = 3;
  p2[1].x = 5; p2[1].y = 3;
  p2[2].x = 5; p2[2].y = 5;
  p2[3].x = 3; p2[3].y = 5;

  ok = geo_intersect_polygons(pi, &num_points,
			      p1, 4,
			      p2, 4);

  if (!ok)
    return 1;

  
  psoll[0].x = 3; psoll[0].y = 2;
  psoll[1].x = 3; psoll[1].y = 3;
  psoll[2].x = 2; psoll[2].y = 3;
  psoll[3].x = 2; psoll[3].y = 2;

  if (!poly_equals(pi, num_points, psoll, 0, EPS))
  {
    printf("Result:\n");
    poly_print(pi, num_points);
    printf("\nBut expected:\n");
    poly_print(psoll, 0);
    return 0;
  }

  return 0;
}

// the two polygons touch at one edge
static int test_intersect5(double EPS)
{
  struct geo_Point p1[4];
  struct geo_Point p2[4];
  struct geo_Point pi[8];
  struct geo_Point psoll[4];
  int num_points;
  int ok;

  p1[0].x = 1; p1[0].y = 1;
  p1[1].x = 3; p1[1].y = 1;
  p1[2].x = 3; p1[2].y = 3;
  p1[3].x = 1; p1[3].y = 3;

  p2[0].x = 3; p2[0].y = 1;
  p2[1].x = 5; p2[1].y = 1;
  p2[2].x = 5; p2[2].y = 3;
  p2[3].x = 3; p2[3].y = 3;

  ok = geo_intersect_polygons(pi, &num_points,
			      p1, 4,
			      p2, 4);

  if (!ok)
    return 1;

  
  psoll[0].x = 3; psoll[0].y = 2;
  psoll[1].x = 3; psoll[1].y = 3;
  psoll[2].x = 2; psoll[2].y = 3;
  psoll[3].x = 2; psoll[3].y = 2;

  if (!poly_equals(pi, num_points, psoll, 0, EPS))
  {
    printf("Result:\n");
    poly_print(pi, num_points);
    printf("\nBut expected:\n");
    poly_print(psoll, 0);
    return 0;
  }

  return 0;
}

// the two polygons are identical
static int test_intersect6(double EPS)
{
  struct geo_Point p1[4];
  struct geo_Point p2[4];
  struct geo_Point pi[8];
  struct geo_Point psoll[4];
  int num_points;
  int ok;

  p1[0].x = 1; p1[0].y = 1;
  p1[1].x = 3; p1[1].y = 1;
  p1[2].x = 3; p1[2].y = 3;
  p1[3].x = 1; p1[3].y = 3;

  p2[0].x = 1; p2[0].y = 1;
  p2[1].x = 3; p2[1].y = 1;
  p2[2].x = 3; p2[2].y = 3;
  p2[3].x = 1; p2[3].y = 3;

  ok = geo_intersect_polygons(pi, &num_points,
			      p1, 4,
			      p2, 4);

  if (!ok)
    return 0;

  
  psoll[0].x = 1; psoll[0].y = 1;
  psoll[1].x = 3; psoll[1].y = 1;
  psoll[2].x = 3; psoll[2].y = 3;
  psoll[3].x = 1; psoll[3].y = 3;

  if (!poly_equals(pi, num_points, psoll, 4, EPS))
  {
    printf("Result:\n");
    poly_print(pi, num_points);
    printf("\nBut expected:\n");
    poly_print(psoll, 4);
    return 0;
  }

  return 1;
}


// like test_intersect1, but different orientation
static int test_intersect7(double EPS)
{
  struct geo_Point p1[4];
  struct geo_Point p2[4];
  struct geo_Point pi[8];
  struct geo_Point psoll[4];
  int num_points;
  int ok;

  p1[0].x = 1; p1[0].y = 1;
  p1[1].x = 1; p1[1].y = 3;
  p1[2].x = 3; p1[2].y = 3;
  p1[3].x = 3; p1[3].y = 1;

  p2[0].x = 2; p2[0].y = 2;
  p2[1].x = 2; p2[1].y = 4;
  p2[2].x = 4; p2[2].y = 4;
  p2[3].x = 4; p2[3].y = 2;


  ok = geo_intersect_polygons(pi, &num_points,
			      p1, 4,
			      p2, 4);

  if (!ok)
    return 0;


  psoll[0].x = 2; psoll[0].y = 3;
  psoll[1].x = 3; psoll[1].y = 3;  
  psoll[2].x = 3; psoll[2].y = 2;
  psoll[3].x = 2; psoll[3].y = 2;



  if (!poly_equals(pi, num_points, psoll, 4, EPS))
  {
    printf("Result:\n");
    poly_print(pi, num_points);
    printf("\nBut expected:\n");
    poly_print(psoll, 4);
    return 0;
  }

  return 1;
}

static int test_intersect_line1(double EPS)
{
  struct geo_Point p1[4];
  struct geo_Point p;
  struct geo_Point d;
  double l1_soll, l2_soll, l1, l2;
  int ok;

  p1[0].x = 1; p1[0].y = 1;
  p1[1].x = 3; p1[1].y = 1;
  p1[2].x = 3; p1[2].y = 3;
  p1[3].x = 1; p1[3].y = 3;

  p.x =       0; p.y = 2;
  d.x = 4; d.y =       0;

  ok = geo_intersect_poly_with_line(p1, 4,
				    &p, &d,
				    &l1, &l2);

  if (!ok)
    return 0;

  
  l1_soll = 0.25;
  l2_soll = 0.75;


  if (fabs(l1 - l1_soll) > EPS || fabs(l2 - l2_soll) > EPS)
  {
    printf("Result       l1=%f,\t l2=%f\n", l1 , l2 );
    printf("But expected l1=%f,\t l2=%f\n", l1_soll ,
	   l2_soll );
    return 0;
  }

  return 1;
}

static int test_intersect_line2(double EPS)
{
  struct geo_Point p1[4];
  struct geo_Point p;
  struct geo_Point d;
  double l1_soll, l2_soll, l1, l2;
  int ok;

  p1[0].x = 2; p1[0].y = 1/ 2.0;
  p1[1].x = 7/ 2.0; p1[1].y = 2;
  p1[2].x = 2; p1[2].y = 7/ 2.0;
  p1[3].x = 1/ 2.0; p1[3].y = 2;

  p.x =       0; p.y = 3/ 2.0;
  d.x = 4; d.y =       0;

  ok = geo_intersect_poly_with_line(p1, 4,
				    &p, &d,
				    &l1, &l2);

  if (!ok)
    return 0;

  
  l1_soll = 0.25;
  l2_soll = 0.75;


  if (fabs(l1 - l1_soll) > EPS || fabs(l2 - l2_soll) > EPS)
  {
    printf("Result       l1=%f,\t l2=%f\n", l1 , l2 );
    printf("But expected l1=%f,\t l2=%f\n", l1_soll ,
	   l2_soll );
    return 0;
  }

  return 1;
}

// goes through two corner points
static int test_intersect_line3(double EPS)
{
  struct geo_Point p1[4];
  struct geo_Point p;
  struct geo_Point d;
  double l1_soll, l2_soll, l1, l2;
  int ok;

  p1[0].x = 2; p1[0].y = 1/ 2.0;
  p1[1].x = 7/ 2.0; p1[1].y = 2;
  p1[2].x = 2; p1[2].y = 7/ 2.0;
  p1[3].x = 1/ 2.0; p1[3].y = 2;

  p.x =       0; p.y = 2;
  d.x = 4; d.y =       0;

  ok = geo_intersect_poly_with_line(p1, 4,
				    &p, &d,
				    &l1, &l2);

  if (!ok)
    return 0;

  
  l1_soll =  1./8.;
  l2_soll =  7./8.;


  if (fabs(l1 - l1_soll) > EPS || fabs(l2 - l2_soll) > EPS)
  {
    printf("Result       l1=%f,\t l2=%f\n", l1 , l2 );
    printf("But expected l1=%f,\t l2=%f\n", l1_soll ,
	   l2_soll );
    return 0;
  }

  return 1;
}
int main(int argc, char* argv[])
{
  double EPS = 0.0000000001;

  if (!test_scalar_prod1(EPS))
    printf("test scalar_prod1 failed!\n");
  else
    printf("test scalar_prod1 successful!\n");  
  
  if (!test_intersect1(EPS))
    printf("test intersect1 failed!\n");
  else
    printf("test intersect1 successful!\n");

  if (!test_intersect2(EPS))
    printf("test intersect2 failed!\n");
  else
    printf("test intersect2 successful!\n");

  if (!test_intersect3(EPS))
    printf("test intersect3 failed!\n");
  else
    printf("test intersect3 successful!\n");

  if (!test_intersect4(EPS))
    printf("test intersect4 failed!\n");
  else
    printf("test intersect4 successful!\n");

  if (!test_intersect5(EPS))
    printf("test intersect5 failed!\n");
  else
  printf("test intersect5 successful!\n");

  if (!test_intersect6(EPS))
    printf("test intersect6 failed!\n");
  else
    printf("test intersect6 successful!\n");

  if (!test_intersect7(EPS))
    printf("test intersect7 failed!\n");
  else
    printf("test intersect7 successful!\n");

  if (!test_intersect_line1(EPS))
    printf("test intersect_line1 failed!\n");
  else
    printf("test intersect_line1 successful!\n");

  if (!test_intersect_line2(EPS))
    printf("test intersect_line2 failed!\n");
  else
    printf("test intersect_line2 successful!\n");

  if (!test_intersect_line3(EPS))
    printf("test intersect_line3 failed!\n");
  else
    printf("test intersect_line3 successful!\n");

  return 0;
}

