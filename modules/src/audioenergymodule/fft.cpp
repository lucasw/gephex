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

#include "fft.hh"
#include <cmath>
#include <cassert>


#ifndef M_PI
#define M_PI 3.1415
#endif

namespace math {

template<typename _REAL>
void fftRecursive(const std::vector<std::complex<_REAL> >& vals,
                  std::vector<std::complex<_REAL> >& rvals,int dir)
{
  assert(dir == 1 || dir == -1);
  int N = vals.size();
  if (N == 1) rvals = vals;
  else
    {
      int N_ = N >> 1;
      std::vector<std::complex<_REAL> > valse(N_);
      std::vector<std::complex<_REAL> > valso(N_);
      for (int i = 0; i < N_; ++i)
	{
	  valse[i] = vals[i << 1];
	  valso[i] = vals[(i << 1)+1];
	}
      
      fftRecursive(valse,valse,dir);
      fftRecursive(valso,valso,dir);

      std::complex<_REAL> W 
		  = std::exp(dir*2*M_PI*std::complex<_REAL>(0,1) / _REAL(N));
      std::complex<_REAL> Wk = 1;

      for (int k = 0; k < N_; ++k)
	{
	  std::complex<_REAL> x = valso[k] * Wk;
	  rvals[k] = valse[k] + x;
	  rvals[k + N_] = valse[k] - x;
	  Wk *= W;
	}

    }
}

template<typename _REAL>
void bitReverse(std::vector<std::complex<_REAL> >& vals)
{
  int n = vals.size();
  int n2 = n >> 1;
  int j = 0;
  for (int i = 0; i < n-1; ++i) 
    {
      if (i < j)
	{
	  std::complex<_REAL> t = vals[i];
	  vals[i] = vals[j];
	  vals[j] = t;
	}
      int k = n2;
      while (k <= j) 
	{
	  j -= k;
	  k >>= 1;
	}
      j += k;
    }
}

template<typename _REAL>
void fftInplace(std::vector<std::complex<_REAL> >& vals, int dir)
{
  assert(dir == 1 || dir == -1);
  bitReverse(vals);
  int n = vals.size();
  
  for (int m = 2; m <= n; m <<= 1)
    {
      std::complex<_REAL> wm = std::exp(dir*2*M_PI*std::complex<_REAL>(0,1) 
				   / _REAL(m));
      std::complex<_REAL> w = 1;
      int m2 = m >> 1;
      for (int j = 0; j < m2; ++j)
	{
	  for (int k = j; k < n; k += m)
	    {
	      int k2 = k + m2;
	      std::complex<_REAL> t = w * vals[k2];
	      std::complex<_REAL> u = vals[k];
	      vals[k] += t;
	      vals[k2] = u - t;
	    }
	  w *= wm;
	}
    }
}


template<typename _REAL>
void fftRealRecursive(const std::vector<_REAL>& vals1,
			   const std::vector<_REAL>& vals2,
			   std::vector<_REAL>& rvals1,
			   std::vector<_REAL>& rvals2, int dir)
{
  assert(vals1.size() == vals2.size());
  assert(vals2.size() == rvals1.size());
  assert(rvals1.size() == rvals2.size());

  int N = vals1.size();
  std::vector<std::complex<_REAL> > cvals(N);
  std::vector<std::complex<_REAL> > rcvals(N);

  // convert the two real sequences into one convex sequence
  for (int i = 0; i < N; ++i)
    {
      cvals[i] = std::complex<_REAL>(vals1[i], vals2[i]);
    }
  
  fftRecursive(cvals,rcvals,dir);

  // convert the std::complex dft-sequence rcvals into the two real
  // dft-sequences rvals1 and rvals2
  for (int i = 0; i < N; ++i)
    {
      rvals1[i] = (rcvals[i] + conj(rcvals[N-i])).real() / 2.0;
      rvals2[i] 
	= (std::complex<_REAL>(0,-1)*(rcvals[i] - conj(rcvals[N-i]))).real()/2.0;
    }
}


template<typename _REAL>
void fftRealInplace(std::vector<_REAL>& vals1,
                    std::vector<_REAL>& vals2, int dir)
{
  assert(dir == 1 || dir == -1);
  assert(vals1.size() == vals2.size());

  int n = vals1.size();
  std::vector<std::complex<_REAL> > cvals(n);

  // convert the two real sequences into one convex sequence
  for (int i = 0; i < n; ++i)
    {
      std::complex<_REAL> t(vals1[i],vals2[i]);
      cvals[i] = t;
    }
  
  fftInplace(cvals,dir);

  // convert the std::complex dft-sequence cvals into the two real
  // dft-sequences vals1 and vals2
  for (int i = 0; i < n; ++i)
    {
      vals1[i] = (cvals[i] + conj(cvals[n-i])).real() / 2.0;
      vals2[i] 
	= (std::complex<_REAL>(0,-1)*(cvals[i] - conj(cvals[n-i]))).real()/2;
    }
}

template<typename _REAL>
void dft(const std::vector<std::complex<_REAL> >& vals,
         std::vector<std::complex<_REAL> >& rvals, int dir)
{
  assert(vals.size() == rvals.size());
  assert(dir == 1 || dir == -1);
  int N = vals.size();

  std::complex<_REAL> W
    = exp(((dir * 2 * M_PI) / N) * std::complex<_REAL> (0,1));
  std::complex<_REAL> Wi = 1;
  std::complex<_REAL> Wij;

  for (int i = 0; i < N; ++i)
    {
      std::complex<_REAL>  sum = vals[0];

      Wij = Wi;
      for (int j = 1; j < N; ++j)
	{
	  sum += vals[j] * Wij;
	  Wij *= Wi;
	}
      rvals[i] = sum;
      Wi *= W;
    }
}

}

