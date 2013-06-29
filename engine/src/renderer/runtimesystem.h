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

#ifndef INCLUDED_RUNTIMESYSTEM_H
#define INCLUDED_RUNTIMESYSTEM_H

#include <list>
#include <string>
#include <map>
#include "utils/autoptr.h"

class ITypeFactory;

class IModule;

class IControlValueReceiver;
class IModuleStatisticsReceiver;

namespace utils {
  class ILogger;
  class Buffer;
}

namespace renderer
{

  class IModuleFactory;

  class ModuleControlBlock;
  class IModuleFactory;

  class RuntimeSystem
  {
  public:
    RuntimeSystem(const IModuleFactory&, const ITypeFactory&,
				  utils::AutoPtr<utils::ILogger>& logger);
    virtual ~RuntimeSystem ();

    virtual void connect(int m1,int outputIndex,int m2,int inputIndex);

    virtual void disconnect(int m1,int inputIndex);

    virtual void update(IControlValueReceiver* cvr,
			IModuleStatisticsReceiver* msr);

    virtual void deleteModule(int);	

    virtual void addModule(const std::string& moduleClassName, int moduleID);

    virtual void setInputValue(int moduleID,int inputIndex,
			       const utils::Buffer& buf,
			       IControlValueReceiver* cvr);

    virtual void syncInputValue(int nodeID, int inputIndex,
				IControlValueReceiver* cvr) const;

    virtual void synchronizeInputValues(IControlValueReceiver* cvr) const;

    typedef utils::AutoPtr<ModuleControlBlock> ModuleControlBlockPtr;
    typedef std::map<int, ModuleControlBlockPtr> ControlBlockMap;
  private:
    ControlBlockMap m_modules; // ID -> IModule*
    std::list<ModuleControlBlockPtr> m_sinks; // Liste aller Senken
    int m_time;
    int frameCount;

    ModuleControlBlockPtr getControlBlock(IModule*);

    const IModuleFactory& moduleFactory;
    const ITypeFactory& typeFactory;
	utils::AutoPtr<utils::ILogger>& m_logger;
  };

} // end of namespace renderer

#endif


