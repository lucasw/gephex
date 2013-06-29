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

#ifndef INCLUDED_MODULE_DATA_DISPATCHER_H
#define INCLUDED_MODULE_DATA_DISPATCHER_H

#include "interfaces/imoduledatareceiver.h"

namespace gui
{

class ModuleDataDispatcher : public IModuleDataReceiver
{
public:
	ModuleDataDispatcher(IModuleDataReceiver& zero_,
						 IModuleDataReceiver& high_);

  virtual void moduleDataSet(int modID, int type, const utils::Buffer&);

  virtual void moduleDataUnSet(int modID, int type);

  virtual void syncDataStarted();
  virtual void syncDataFinished();

private:
	IModuleDataReceiver& zero;
	IModuleDataReceiver& high;
};

}

#endif
