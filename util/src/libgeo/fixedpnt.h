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

#ifndef INCLUDED_FIXEDPNT_H
#define INCLUDED_FIXEDPNT_H

/**
 * Utility functions for 16:16 bit fixedpoint arithmetic.
 *
 */

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "basic_types.h"

#define FIXEDPNT_SCALE 65536.
#define FIXEDPNT_SHIFT 16
#define FIXEDPNT_ONE (1 << FIXEDPNT_SHIFT)

static int_32 fixed_times(int_32 f1, int_32 f2)
{
 int_32 tt;
#if defined(COMP_GCC) && defined(CPU_I386)
 asm
 ("mov   %2, %%ebx        \n"
  "imull %%ebx            \n"
  "shrd  $16,%%edx,%0     \n"
 :"=a"(tt)
 :"0"(f1),"r"(f2)
 :"ebx","edx","memory"
 );
#elif defined(COMP_VC) && defined(CPU_I386)
 _asm{
   mov eax, f1
     mov ebx, f2
     imul ebx
     shrd eax, edx, 16
     mov tt, eax
 }
#else
 int_64 temp = f1 * f2; //TODO: wrong
 tt = temp >> 16;
#endif
 return tt;
}

static int_32 fixed_div (int_32 lhs, int_32 rhs)
{
 int_32 tt;
#if defined(COMP_GCC) && defined(CPU_I386)
 asm
 ("cdq                  \n"
  "shld $16,%%eax,%%edx \n"
  "sal  $16,%%eax       \n"
  "idivl %2             \n"
 :"=a"(tt)
 :"0"(lhs),"r"(rhs)
 :"edx","memory"
 );
#elif defined(COMP_VC) && defined(CPU_I386)
 _asm{
   mov eax, lhs
     mov ebx, rhs
     cdq
     shld edx, eax, 16
     sal eax, 16
     idiv ebx
     mov tt, eax
 }
#else
 int_64 temp = lhs << 16; //TODO: wrong
 tt = (int_32) (temp / rhs);
#endif
 return tt;
}

#endif
