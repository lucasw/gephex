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

#ifndef INCLUDED_MODULE_CLASS_MODEL_H
#define INCLUDED_MODULE_CLASS_MODEL_H

#include <list>

#include "interfaces/imoduleclassinforeceiver.h"

namespace utils {
	class Buffer;
}

namespace gui
{
  class IModuleClassView;
  
  class ModuleClassModel : public IModuleClassInfoReceiver
  {
  public:
    virtual ~ModuleClassModel();

    void registerModuleClassView(IModuleClassView&);
    void unregisterModuleClassViews();
    
    void moduleClassLoaded(const std::string& moduleClassName,
			   const utils::Buffer&);

    void moduleClassUnloaded(const std::string& moduleClassName);

    void syncStarted();
    void syncFinished();
    
  private:
	  std::list<IModuleClassView*> views;
    
  };
}
#endif
