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

#include "frei0r_module.h"

#include <stdexcept>
#include <ctime>

#include "c_input.h"
#include "c_output.h"

#include "c_moduletables.h"
#include "interfaces/itype.h"
#include "interfaces/itypefactory.h"


frei0r_module::frei0r_module(void* instance,
			     const CModuleVTable& vtable,
			     const CModuleAttributes& attributes,
			     const ITypeFactory& tfactory_,
			     const std::vector<IType*>& defaultInputTypes,
			     const std::string& module_class_name,
			     const frei0r_funs_t& frei0r)
  : IModule(-1), m_instance(instance), m_vtable(&vtable),
    inputs(attributes.inputs.size()),outputs(attributes.outputs.size()),
    _isDeterministic(attributes.isDeterministic),
    m_module_class_name(module_class_name),m_frei0r(frei0r)
  
{
  for (unsigned int i = 0; i < attributes.inputs.size(); ++i)
    {
      inputs[i] 
	= IInputPtr( new CInput(attributes.inputs[i],
				attributes.isConstInput[i],
				attributes.isStrongDependency[i],*this,i,
				tfactory_,attributes.fixedAttributes[i],
				*defaultInputTypes[i], *m_vtable, m_instance));
      // add dependecy for the first update
      m_deps.push_back(&*inputs[i]);
    }
	
  for (unsigned int j = 0; j < attributes.outputs.size(); ++j)
    {
      IType* type = tfactory_.buildNew(attributes.outputs[j]);
		
      outputs[j] = IOutputPtr(new COutput(*this,attributes.outputs[j],type,
		                      j,*m_vtable,m_instance));		      
    }
}

frei0r_module::~frei0r_module()
{
  m_vtable->deleteInstance(m_instance);	
}

std::string frei0r_module::module_class_name() const
{
	return m_module_class_name;
}

const std::vector<frei0r_module::IInputPtr>& frei0r_module::getInputs() const
{
  return inputs;
}

const std::vector<frei0r_module::IOutputPtr>& frei0r_module::getOutputs() const
{
  return outputs;
}

bool frei0r_module::isDeterministic() const
{
  // frei0r modules are always nondeterministic
  return false; 
}

IInput* frei0r_module::dependencies()
{
  if (m_deps.empty())
    {
      // update all inputs
      for (std::vector<IModule::IInputPtr>::iterator it = inputs.begin(); 
	   it!=inputs.end(); ++it)
	{
	  (*it)->update();
	}
      
      return 0;
    }
  else
    {
      IInput* in = m_deps.front();
      m_deps.pop_front();
      return in;
    }
}

void frei0r_module::update()
{
  assert(m_deps.empty());
  
  m_vtable->update(m_instance);

  // refill dependecy list for next update
  for (unsigned int i = 0; i < inputs.size(); ++i)
    {
      m_deps.push_back(&*inputs[i]);
    }
  
}
