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

#include "signals.h"

#include <cmath>
#include <cassert>

#include "crandgen.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static const int    NOISE_SIZE    = 33;

//-----------------------------------------------------------------------------

double Sinus::operator()(double t, double f, double amp)
{
  return (amp*0.5*(1.0+sin(2*M_PI*f*t)));
}

double Sinus::inv(double val, double f, double amp, 
                        double delta_val)
{
  double inv;
  double arg = 2.0*val/amp - 1;

  if (arg < -1)
    arg = -1;
  else if (arg > 1)
    arg = 1;

  assert(-1 <= arg && arg <= 1);

  if (arg >= 0)
    {
      if (delta_val >= 0)
        {
          inv = asin(arg);

          assert(0 <= inv && inv <= M_PI/2.0);
        }
      else
        {
          inv = (M_PI/2.0 - asin(arg)) + M_PI/2.0;
          
          assert(M_PI/2.0 <= inv && inv <= M_PI);
        }
    }
  else if (arg < 0)
    {
      if (delta_val < 0)
        {
          inv = (-M_PI/2.0 - asin(arg)) + 3.*M_PI/2.;

          assert(M_PI <= inv && inv <= 3.*M_PI/2.0);
        }
      else
        {
          inv = asin(arg) + 2.*M_PI;

          assert(3.*M_PI/2 <= inv && inv <= 2.*M_PI);
        }
    }

  return inv / (2*M_PI * f);
}

//-----------------------------------------------------------------------------

double Triangle::operator()(double t, double f, double amp)
{
  double T = 1.0 / f;
  double time = fmod(t, T);
  double aa = 2.0 * amp;
    
  if (time < 0.5*T)
    return (aa * f * time);
  else
    return aa * (1 - f*time);
}

double Triangle::inv(double val, double f, double amp,
                     double delta_val)
{
  double T = 1.0 / f;
  double tmp = val / (2.0*amp);

  if (delta_val >= 0)
      return T * tmp;
  else
      return T * (1 - tmp);
}

//-----------------------------------------------------------------------------

double Ramp::operator()(double t, double f, double amp)
{
  double time = fmod(t, 1.0 / f);
  return (amp * f * time);
}

double Ramp::inv(double val, double f, double amp,
                 double delta_val)
{
  return val / (amp*f);
}

//-----------------------------------------------------------------------------

double Rectangle::operator()(double t, double f, double amp)
{
  double T = 1.0 / f;
  double time = fmod(t, T);
    
  if (time < 0.5*T)
    return amp;
  else
    return 0;
}

double Rectangle::inv(double val, double f, double amp, double delta_val)
{
  if (delta_val >= 0)
    return 0;
  else
    return 1.0 / (2*f);
}

//-----------------------------------------------------------------------------

static void noise_fill_data(int size, double* values, int& pos,
                            double f, double amp)
{
  int n = size;
  int k = (int) (log(size) / log(2));
  double sigma = 1;
  double a;
  if (f < 0.999)
    a = amp / (1 + (1-f) - (1-pow(f,k+1)));
  else
    a = amp / (k+1);
    
  values[0] = values[n-1]; // use old value
  values[n-1] = (rnd_mt19937() / (double) 0xFFFFFFFF)*a*sigma;
    
  do {
    int i;
        
    n >>= 1;
    sigma *= f;
    for (i = n; i < size; i += n) {
      if ((i & ((n<<1)-1)) == 0)
        continue; //don't calculate values that have been calculated before
      values[i] = (rnd_mt19937() / (double) 0xFFFFFFF)*a*sigma 
        + 0.5*(values[i-n] + values[i+n]);
    }
        
  } while (n > 1);
    
  pos = 0;
}

Noise::Noise(int n)
  : m_values(new double[n]), m_size(n), m_pos(n)
{
  m_values[n-1] = 0;
}

Noise::~Noise()
{
  delete[] m_values;
}

double Noise::operator()(double t, double f, double amp)
{
  if (m_pos >= m_size)
    {
      noise_fill_data(m_size, m_values, m_pos, f, amp/2.0);
      //      s_log(3, "Calculating next values");
    }
    
  return m_values[m_pos++];
}

double Noise::inv(double val, double f, double amp, double delta_val)
{
  return 0; //TODO
}

//-----------------------------------------------------------------------------

SignalFactory::SignalFactory(const std::string& name)
  : m_name(name) {}
std::string SignalFactory::name() const { return m_name; }

SinusFactory::SinusFactory() : SignalFactory("sinus") {}
Signal* SinusFactory::create() { return new Sinus(); }

RampFactory::RampFactory() : SignalFactory("ramp") {}
Signal* RampFactory::create() { return new Ramp(); }

TriangleFactory::TriangleFactory() : SignalFactory("triangle") {}
Signal* TriangleFactory::create() { return new Triangle(); }

RectangleFactory::RectangleFactory() : SignalFactory("rectangle") {}
Signal* RectangleFactory::create() { return new Rectangle(); }

NoiseFactory::NoiseFactory() : SignalFactory("noize") {}
Signal* NoiseFactory::create() { return new Noise(NOISE_SIZE); }

//-----------------------------------------------------------------------------
