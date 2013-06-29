/* Pseudo random number generators for plain C.
   Copyright (C) 2003 Georg Seidel
   This file is part of GePhex.

   GePhex is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   GePhex is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public
   License along with GePhex; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  
 
   You can reach me via email: georg.seidel@web.de
 */

#ifndef INCLUDED_C_RAND_GEN_H
#define INCLUDED_C_RAND_GEN_H

#include "basic_types.h"

/*
 *
 * This is a linear congruential generator.
 * The general form is:
 *
 *   x[n+1] = (a * x[n] + c) mod m
 *
 * This generator has the parameters a = 3039177861, c = 0, m = 2^32.
 * It produces numbers in the range [RND_LCG1_MIN, RAND_LCG1_MAX]
 * (hopefully uniformly distributed).
 *
 * Please note that for performance reasons, the generator is *not*
 * reentrant. It uses the global variable lcg1_xn for its seed and to
 * store its current state.
 *
 * So to initialize the seed before using rnd_lcg1, just do something
 * like that:
 *
 *   rnd_lcg1_xn = <YOUR SEED>;
 *   your_var1 = rnd_lcg1_xn();
 *   ...
 *   your_varx = rnd_lcg1_xn();
 *
 *
 * Got the parameters for this LCG from:
 * http://crypto.mat.sbg.ac.at/results/karl/server/node4.html
 *
 * Original results from:
 *  D.E. Knuth.
 *  The Art of Computer Programming, volume 2: Seminumerical Algorithms.
 *  Addison-Wesley, Reading, MA, 2nd edition, 1981.
 *
 */

#define RND_LCG1_MAX UINT32_MAX
#define RND_LCG1_MIN 1

static uint_32 rnd_lcg1_xn = 1;

__inline static uint_32 rnd_lcg1()
{
  rnd_lcg1_xn *= 3039177861U;

  return rnd_lcg1_xn;
}


/*
 * This is an implementation of the Mersenne Twister.
 *
 * It is from http://www.math.keio.ac.jp/~matumoto/MT2002/emt19937ar.html.
 * Below are the original copyrights and conditions.
 * I just changed the names of the macros and functions and removed 
 * the init_array and main functions.
 *
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT
   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   Any feedback is very welcome.
   http://www.math.keio.ac.jp/matumoto/emt.html
   email: matumoto@math.keio.ac.jp
*/

/* Period parameters */  
#define RND_MT_N 624
#define RND_MT_M 397
#define RND_MT_MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define RND_MT_UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define RND_MT_LOWER_MASK 0x7fffffffUL /* least significant r bits */

static uint_32 rnd_mt[RND_MT_N]; /* the array for the state vector  */
static int rnd_mti=RND_MT_N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void rnd_mt_init(uint_32 s)
{
    rnd_mt[0]= s & 0xffffffffUL;
    for (rnd_mti=1; rnd_mti<RND_MT_N; rnd_mti++) {
        rnd_mt[rnd_mti] = 
          (1812433253UL * (rnd_mt[rnd_mti-1] ^ (rnd_mt[rnd_mti-1] >> 30)) 
           + rnd_mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        rnd_mt[rnd_mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* generates a random number on [0,0xffffffff]-interval */
uint_32 rnd_mt19937(void)
{
    uint_32 y;
    static uint_32 mag01[2]={0x0UL, RND_MT_MATRIX_A};
    /* mag01[x] = x * RND_MT_MATRIX_A  for x=0,1 */

    if (rnd_mti >= RND_MT_N) { /* generate RND_MT_N words at one time */
        int kk;

        if (rnd_mti == RND_MT_N+1) /* if rnd_mt_init() has not been called, */
          rnd_mt_init(5489UL); /* a default initial seed is used */

        for (kk=0;kk<RND_MT_N-RND_MT_M;kk++) {
            y = (rnd_mt[kk]&RND_MT_UPPER_MASK)
              |(rnd_mt[kk+1]&RND_MT_LOWER_MASK);
            rnd_mt[kk] = rnd_mt[kk+RND_MT_M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<RND_MT_N-1;kk++) {
            y = (rnd_mt[kk]&RND_MT_UPPER_MASK)
              |(rnd_mt[kk+1]&RND_MT_LOWER_MASK);
            rnd_mt[kk] = rnd_mt[kk+(RND_MT_M-RND_MT_N)] ^ (y >> 1)
              ^ mag01[y & 0x1UL];
        }
        y = (rnd_mt[RND_MT_N-1]&RND_MT_UPPER_MASK)
          |(rnd_mt[0]&RND_MT_LOWER_MASK);

        rnd_mt[RND_MT_N-1] = rnd_mt[RND_MT_M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        rnd_mti = 0;
    }
  
    y = rnd_mt[rnd_mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7)  & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

#endif

