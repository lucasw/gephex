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

#include "audioenergymodule.h"

#include <algorithm>
#include <cmath>
#include "fft.hh"

#if defined(_MSC_VER)
#include <minmax.h>
#else
using std::min;
using std::max;
#endif

//--------------------------------------------------------------

static logT s_log;

static const int BLOCK_SIZE = 4;
static const int MIN_BLOCKS = 128;

//--------------------------------------------------------------

class SampleBuffer
{
public:
  SampleBuffer(int block_size)
    : m_size(0), m_num_blocks(0),
      m_block_size(block_size), m_blocks(0)
  {
    assert(m_block_size >= 1);
  }

  ~SampleBuffer()
  {
    if (m_blocks)
      delete[] m_blocks;
  }

  int num_blocks() const { return m_num_blocks; }

  void put(int num_samples, const double* samples)
  {
    int full_blocks = num_samples / m_block_size;		

    int rest = num_samples - full_blocks * m_block_size;
    int needed_blocks = (rest == 0) ? full_blocks : full_blocks + 1;

    if (m_num_blocks + needed_blocks > m_size)
      {
        m_size = m_num_blocks + needed_blocks;
        double* new_blocks = new double[m_size];

        if (m_num_blocks > 0)
          {
            memcpy(new_blocks, m_blocks,
                   m_num_blocks*sizeof(double));
            delete[] m_blocks;
          }
			
        m_blocks = new_blocks;
      }

    for (int i = 0; i < full_blocks; ++i)
      {
        double sum = 0;
        for (int j = 0; j < m_block_size; ++j)
          sum += samples[i*m_block_size + j];

        m_blocks[m_num_blocks + i] = sum / m_block_size;
      }
    if (rest != 0)
      {
        double sum = 0;
        for (int j = m_num_blocks*m_block_size;
             j < num_samples; ++j)
          {
            sum += samples[j];
          }

        m_blocks[m_num_blocks + full_blocks] = sum / rest;
      }

    m_num_blocks += needed_blocks;
  }

  const double* blocks() const { return m_blocks; }

  void consume(int num_blocks)
  {	
    assert(num_blocks <= m_num_blocks && num_blocks >= 0);

    int left = m_num_blocks - num_blocks;

    if (left > 0)
      memmove(m_blocks, m_blocks + num_blocks, left);

    m_num_blocks = left;
  }

private:
  int m_size;
  int m_num_blocks;
  int m_block_size;
  double* m_blocks;

};

//--------------------------------------------------------------

typedef struct _MyInstance {

  SampleBuffer* buffer;

  double flmin[4];
  double flmax[4];

} MyInstance, *MyInstancePtr;

//--------------------------------------------------------------

int init(logT log_function)
{
  s_log = log_function;

  return 1;
}

void shutDown(void)
{
}

template <typename T>
T my_min(T a, T b) {
  return (a < b) ? a : b;
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->buffer = new SampleBuffer(BLOCK_SIZE);

  std::fill(my->flmin,my->flmin+4,0.0);
  std::fill(my->flmax,my->flmax+4,0.0);
  
  return my;
}

void destruct(MyInstance* my)
{
  delete my->buffer;
  free(my);
}

static double get_energy(const std::vector<std::complex<double> >& src,
                         int begin, int end)
{
  int range = end - begin;
  assert(range > 0);
  double sum = 0;

  for (int i = begin; i != end; ++i)
    {
      double re = src[i].real();
      double im = src[i].imag();
      sum += re*re + im*im;
    }

  return sum; // / range;
}

namespace
{
  double adapt(double min, double max, double val)
  {
    if (max==min)
      return 0.5;
    else if (val < min)
      return 0.0;
    else if (val > max)
      return 1.0;
    else
      return (val-min)/(max-min);
  }
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstance* my = (MyInstance*) inst->my;

  int len = inst->in_audio->len;
  const double* samples = inst->in_audio->samples;

  double amp = trim_double(inst->in_amp->number, 0 , 1);

  if (inst->in_audio->channels != 1) {
    s_log(0, "channels not 1!");
    return;
  }

  my->buffer->put(len, samples);

  if (my->buffer->num_blocks() < MIN_BLOCKS)
    return;

  int num_blocks = MIN_BLOCKS;
  while (num_blocks < my->buffer->num_blocks())
    num_blocks*=2;
  
  num_blocks /= 2;

  std::vector<std::complex<double> > src(num_blocks);
  
  const double* blocks = my->buffer->blocks();
  int i;
  for (i = 0; i < num_blocks; ++i) {
    src[i] = std::complex<double>(blocks[i], 0);
  }

  my->buffer->consume(num_blocks);
  //  printf("num_blocks = %i\n", num_blocks);
  //  printf("fill       = %i\n", my->buffer->num_blocks());

  math::fftInplace(src, 1);

  for (i = 0; i < num_blocks/2; ++i) {
    src[i] /= num_blocks/2;
    //out_samples[2*i]   = src[i].real();
    //out_samples[2*i+1] = src[i].imag();
  }

  int b1 = static_cast<int>(0.03 * num_blocks);
  int b2 = static_cast<int>(0.06 * num_blocks);
  int b3 = static_cast<int>(0.16 * num_blocks);
  int b4 = static_cast<int>(0.5  * num_blocks);

  double e[4];
  
  e[0] = get_energy(src,  0, b1);
  e[1] = get_energy(src, b1, b2);
  e[2] = get_energy(src, b2, b3);
  e[3] = get_energy(src, b3, b4);
  
  double f= 0.9 + 0.1 * amp*amp;

  double f_inv= 1.0-f;

  for (i = 0; i != 4; ++i)
    {
      my->flmin[i] = min( e[i], f*my->flmin[i] + f_inv*e[i]);
      my->flmax[i] = max( e[i], f*my->flmax[i] + f_inv*e[i]);
    }
  
  inst->out_e1->number = adapt(my->flmin[0], my->flmax[0],e[0]);
  inst->out_e2->number = adapt(my->flmin[1], my->flmax[1],e[1]);
  inst->out_e3->number = adapt(my->flmin[2], my->flmax[2],e[2]);
  inst->out_e4->number = adapt(my->flmin[3], my->flmax[3],e[3]);
  
}


