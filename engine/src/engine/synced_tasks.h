/* This source file is a part of the GePhex Project.

 Copyright (C) 2005

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

#ifndef INCLUDED_SYNCED_TASKS
#define INCLUDED_SYNCED_TASKS

#include <list>

#include "itask.h"

/**
 * wrapper class to register multiple tasks that need to run in sync
 */
class synced_tasks : public ITask
{
 public:
      synced_tasks(const std::list<ITask*>& sub_tasks)
	: m_tasks(sub_tasks)
	{
	}
      
      bool run()
	{
	  bool result = true;
	  for(std::list<ITask*>::iterator it = m_tasks.begin();
	      it !=  m_tasks.end();
	      ++it)
	    {
	      result = result && (*it)->run();
	    }
	  return result;
	}
      
 private:
      std::list<ITask*> m_tasks;
};

#endif
