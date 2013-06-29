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

#ifndef INCLUDED_ITASK_H
#define INCLUDED_ITASK_H

/**
 * simple interface for non-preemptive tasks.
 */
class ITask
{
 public:

  /**
   * This method executes one slice of the task. The run method must return
   * control as soon as possible(non-preemptive).
   *
   * \returns the thread finished status. 
   *          It is true if there are task slices left to be executed and 
   *          false if the scheduler mustn't call the run method again.
   */
  virtual bool run() = 0;
};

#endif

