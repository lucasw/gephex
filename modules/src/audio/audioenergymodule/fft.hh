#ifndef INCLUDED_FFT_HH
#define INCLUDED_FFT_HH

#include <vector>
#include <complex>


namespace math {

// Reorders the elements of vals as they would appear in the call-tree
// of the recursive fft.
// pre:  vals.size() == 2^k
// post: vals_out[i] = vals_in[bitReverse(i)]
template<typename _REAL>
void bitReverse(std::vector<std::complex<_REAL> >& vals);

// Simple recursive fft.
// The size of vals must be a power of 2.
template<typename _REAL>
void fftRecursive(const std::vector<std::complex<_REAL> >& vals,
		       std::vector<std::complex<_REAL> >& rvals, int dir);

// Simple iterative Inplace fft.
// The size of vals must be a power of 2.
template<typename _REAL>
void fftInplace(std::vector<std::complex<_REAL> >& vals,int dir);

// Simple recursive fft for 2 REAL sequences.
// The size of the vals must be a power of 2.
template<typename _REAL>
void fftRealRecursive(const std::vector<_REAL>& vals1,
			   const std::vector<_REAL>& vals2,
			   std::vector<_REAL>& rvals1,
			   std::vector<_REAL>& rvals2, int dir);

// Simple recursive fft for 2 REAL sequences.
// The size of the vals must be a power of 2.
template<typename _REAL>
void fftRealInplace(std::vector<_REAL>& vals1,
			 std::vector<_REAL>& vals2, int dir);

// Simple (quadratic) dft.
template<typename _REAL>
void dft(const std::vector<std::complex<_REAL> >& vals,
	      std::vector<std::complex<_REAL> >& rvals, int dir);

}

#include "fft.cpp"

#endif
