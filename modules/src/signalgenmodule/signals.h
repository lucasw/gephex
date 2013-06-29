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

#ifndef INCLUDED_SIGNALS_H
#define INCLUDED_SIGNALS_H

#include <string>

/**
 * Base class for all signal types.
 * 
 */
class Signal
{
public:
  /**
   * Evaluation of the signal at time t.
   *
   * @param t the time
   * @param f the frequency (must be in [0, inf[)
   * @þaram a the amplitude (must be in [0, inf[)
   * @return the value of the signal at time t
   */
  virtual double operator()(double t, double f, double a) = 0;

  /**
   * The pseudo inverse of the function:
   *
   * For a signal s, a frequency f in ]0, inf[, an amplitude a 
   * in ]0, inf[, a double delta, and a y in [0, a],
   * the following conditions should hold:
   *
   *    a)  s.inv(y, f, a, delta) == t  =>  s(t, f, a) == y
   *
   * and
   *
   *    b)  sign( s'(t, f, a) ) == sign( delta ).
   *         (s' is the derivative of s)
   * 
   * This means that the value and the "direction" of the signal
   * at the time t should be as close as possible to y and delta.
   * If the derivative of s does not exist or the value of y
   * cannot be taken, an approximation or sensible defaults should
   * be chosen.
   * 
   *
   * @param y the value of the signal
   * @param f the frequency (must be in [0, inf[)
   * @param a the amplitude (must be in [0, inf[)
   * @param approximation of the derivative that should be
   *   taken by s
   * @return the time at which the value y is taken
   */
  virtual double inv(double y, double f, double a, double delta) = 0;
};

class SignalFactory
{
public:
  SignalFactory(const std::string& name);

  std::string name() const;

  virtual Signal* create() = 0;

private:
  std::string m_name;
};

class Sinus : public Signal
{
public:
  double operator()(double t, double f, double a);
  double inv(double y, double f, double a, double delta);
};

class SinusFactory : public SignalFactory
{
public:
  SinusFactory();
  Signal* create();
};

class Ramp : public Signal
{
public:
  double operator()(double t, double f, double a);
  double inv(double y, double f, double a, double delta);
};

class RampFactory : public SignalFactory
{
public:
  RampFactory();
  Signal* create();
};

class Triangle : public Signal
{
public:
  double operator()(double t, double f, double a);
  double inv(double y, double f, double a, double delta);
};

class TriangleFactory : public SignalFactory
{
public:
  TriangleFactory();
  Signal* create();
};

class Rectangle : public Signal
{
public:
  double operator()(double t, double f, double a);
  double inv(double y, double f, double a, double delta);
};

class RectangleFactory : public SignalFactory
{
public:
  RectangleFactory();
  Signal* create();
};

class Noise : public Signal
{
public:
  Noise(int n);
  ~Noise();

  double operator()(double t, double f, double a);
  double inv(double y, double f, double a, double delta);

private:
  double* m_values;
  int m_size;
  int m_pos;
};

class NoiseFactory : public SignalFactory
{
public:
  NoiseFactory();
  Signal* create();
};


#endif
