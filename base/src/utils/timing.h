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

#ifndef INCLUDED_TIMING_H
#define INCLUDED_TIMING_H

namespace utils {

  /**
   * This class provides basic timing functionality.
   */
  class Timing
  {
  public:
    /**
     * Returns the current system time in ms.
     * @return the system time in millis.
     */
    static unsigned long getTimeInMillis();

    /**
     * Suspends the process for a given amount of time.
     * Depending on the OS, the resolution may be higher
     * than on ms (f.e on Linux/i368, the suspend time
     * is at least 10ms).
     * @param millis the time to suspend in ms
     */
    static void sleep(unsigned long millis);
  };

}

#endif
