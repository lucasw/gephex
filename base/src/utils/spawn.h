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

#ifndef INCLUDED_SPAWN_H
#define INCLUDED_SPAWN_H

#include <vector>
#include <string>

namespace utils
{
	/**
	 * Executes an executable in a new process.
	 * The calling process is not suspended but returns immediately.
         *
         * Note that it is possible that execution of the file fails
         * without an exception thrown.
         *
         * If exec_name is not an absolute path it is searched in the
         * current path (as set by the os's environment variables).
         *
         * \param exec_name the filename of the executable that is executed
         * \param args a vector of arguments that are passed to the
         *             binary. Don't pass the exec_name as first parameter -
         *             this is already done internally. If an argument
         *             contains whitespace it's your responsibility to
         *             quote them.
	 *
	 * \throws std::runtime_error if forking or execution of the 
         *                            binary fails	
	 */
	void spawn(const std::string& exec_name,
                   const std::vector<std::string>& args);
}

#endif
