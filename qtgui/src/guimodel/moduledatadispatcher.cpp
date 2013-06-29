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

#include "moduledatadispatcher.h"

namespace gui
{

	ModuleDataDispatcher::ModuleDataDispatcher(IModuleDataReceiver& zero_,
						 IModuleDataReceiver& high_)
		: zero(zero_), high(high_)
	{
	}

  void ModuleDataDispatcher::moduleDataSet(int modID, int type,
		const utils::Buffer& b)
  {
	  if (type < 1024)
		  zero.moduleDataSet(modID,type,b);
	  else
		  high.moduleDataSet(modID,type,b);
  }

  void ModuleDataDispatcher::moduleDataUnSet(int modID, int type)
  {
	  if (type < 1024)
		  zero.moduleDataUnSet(modID,type);
	  else
		  high.moduleDataUnSet(modID,type);
  }

  void ModuleDataDispatcher::syncDataStarted()
  {
    zero.syncDataStarted();
    high.syncDataStarted();
  }

  void ModuleDataDispatcher::syncDataFinished()
  {
    zero.syncDataFinished();
    high.syncDataFinished();
    //TODO
  }

} // end of namespace gui
