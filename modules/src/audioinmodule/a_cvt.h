#ifndef INCLUDED_A_CVT_H
#define INCLUDED_A_CVT_H

#include <stdint.h>

void a_cvt_16le_to_double_mono(const int16_t* src,
			       double* dst,
			       int num_samples);

void a_cvt_double_to_16le_mono(const double* src,
			       int16_t* dst,
			       int num_samples);

#endif
