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

#include "builtin_functions.h"

#include <math.h>

double add_fun(double lhs, double rhs) {
  return lhs + rhs;
}

double sub_fun(double lhs, double rhs) {
  return lhs - rhs;
}

double mul_fun(double lhs, double rhs) {
  return lhs * rhs;
}

double div_fun(double lhs, double rhs) {
  if (fabs(rhs) < 0.00000001)
    return 0;

  return lhs / rhs;
}

double mod_fun(double lhs, double rhs) {
  if (fabs(rhs) < 0.0000000001)
    return 0;
  else
    return fmod(lhs,rhs);
}

double pow_fun(double lhs, double rhs) {
  return pow(lhs, rhs);
}

double neg_fun(double lhs) {
  return -lhs;
}

double abs_fun(double lhs) {
  return fabs(lhs);
}
