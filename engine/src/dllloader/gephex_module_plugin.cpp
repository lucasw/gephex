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

#include "gephex_module_plugin.h"

#include <stdexcept>

#include "utils/sharedlibrary.h"
#include "utils/ilogger.h"
#include "c_moduletables.h"
#include "gephex_module_class.h"


  // Default functions
  int Dinit(void (*)(int,const char*, const char*))
  {
    return 1;
  }
	
  void DshutDown()
  {
  }
	
  void DparseInput(void*,const char*,int)
  {
    throw std::runtime_error("Operation parseInput() not supported by this"
			     "module!");
  }
	
  void* DgetInputAttributes(int)
  {
    return 0;
  }


//TODO: Fehlerbehandlung!
CModuleFunctionTable loadModule(utils::SharedLibrary& sl)
{
  CModuleFunctionTable ft;
		
    ft.init = (initT) sl.loadSymbol("initSO");
		
    ft.shutDown = (shutDownT) sl.loadSymbol("shutDown");
    
    ft.newInstance = (newInstanceT) sl.loadSymbol("newInstance");
    
    ft.deleteInstance = (deleteInstanceT) sl.loadSymbol("deleteInstance");
    
    ft.getSpec = (getSpecT) sl.loadSymbol("getSpec");
    
    ft.getOutputSpec = (getOutputSpecT) sl.loadSymbol("getOutputSpec");
    
    ft.getInputSpec = (getInputSpecT) sl.loadSymbol("getInputSpec");
		
    ft.getInfo = (getInfoT) sl.loadSymbol("getInfo");
		
    ft.setOutput = (setOutputT) sl.loadSymbol("setOutput");
		
    ft.setInput = (setInputT) sl.loadSymbol("setInput");
		
    ft.update = (updateT) sl.loadSymbol("update");
		
    ft.parseInput = (parseInputT) sl.loadSymbol("parseInput");
		
    ft.strongDependenciesCalculated = (strongDependenciesCalculatedT)
      sl.loadSymbol("strongDependenciesCalculated");
    
    ft.getInputAttributes = (getInputAttributesT)
      sl.loadSymbol("getInputAttributes");
	
    ft.getPatchLayout = (getPatchLayoutT)
      sl.loadSymbol("getPatchLayout");
	
    // check for missing functions 
    if (ft.newInstance == 0 ||
	ft.deleteInstance == 0 ||
	ft.update == 0 ||
	ft.getSpec == 0 ||
	ft.getInfo == 0) 
      throw std::runtime_error("missing function in module plugin");
    
    // add defaults
    if (ft.init == 0)
      ft.init = Dinit;
		
    if (ft.shutDown == 0)
      ft.shutDown = DshutDown;
    
    if (ft.parseInput == 0)
      ft.parseInput = DparseInput;
    
    if (ft.getInputAttributes == 0)
      ft.getInputAttributes = DgetInputAttributes;

    return ft;
  }


gephex_module_plugin::gephex_module_plugin(utils::SharedLibrary& sl,
					   NameResolver& resolver)
{
  // extract the module plugin functions
  CModuleFunctionTable ft( loadModule(sl) );
	
  // construct new module class
  IModuleClass* cm = new CModuleClass(ft, resolver);
	
  m_module_classes.push_back(cm);
}
  
gephex_module_plugin::~gephex_module_plugin()
{
}


std::list<IModuleClass*>& gephex_module_plugin::get_module_classes()
{
  return m_module_classes;
}

