#include "c_output.h"
#include "c_outputplug.h"

#include "interfaces/itype.h"

#include "c_moduletables.h"

COutput::COutput(IModule& mod,int _typeID, IType* _data, int index,
				 const COutputVTable& vtable, void* instance)
  : m_module(&mod), /*isChanged(true),*/ m_typeID(_typeID), m_plugs(),
    m_data(_data), m_patchedInput(0), m_index(index),
	m_vtable(&vtable), m_instance(instance)
{
	m_vtable->setOutput(m_instance,m_index,m_data->getPointer());
}

COutput::~COutput()
{
  delete m_data;
}

/*void COutput::setData(const IType* _data) //TODO: remove?
{
  	data = _data;
	for (PlugList::iterator i = plugs.begin();
	     i != plugs.end(); ++i)
	  {
	    (*i)->setData(_data);
	    }
	//TODO set data of all outputplugs and copy if needed
}*/

IModule* COutput::getModule() const
{
	return m_module;
}

utils::AutoPtr<IOutputPlug> COutput::plugIn(IInput& in)
{
	IOutputPlugPtr plug (new COutputPlug(*this,in));
	m_plugs.push_back(plug);
	plug->setData(m_data);
	return plug;
}

void COutput::unPlug(IInput& in)
{
	for (PlugList::iterator it = m_plugs.begin();
	it != m_plugs.end(); ++it)
    {
		IOutputPlugPtr current = *it;
		if (current->getInput() == &in)
		{
			m_plugs.erase(it);
			break;
		}
    }
}

int COutput::getType() const
{
	return m_typeID;
}

std::list<IInput*> COutput::getConnectedInputs() const
{
  std::list<IInput*> inputs;
  
  for (PlugList::const_iterator it = m_plugs.begin();
       it != m_plugs.end(); ++it)
    {
      IOutputPlugPtr current = *it;
      inputs.push_back(current->getInput());
    }

  return inputs;
}


IInput* COutput::getPatchedInput() const
{
	return m_patchedInput;
}

void COutput::setPatchedInput(IInput* in)
{	
	m_patchedInput = in;
	for (PlugList::iterator it = m_plugs.begin();
	it != m_plugs.end(); ++it)
	{
		(*it)->setData(in->getData());		
    }

	m_vtable->setOutput(m_instance,m_index,in->getData()->getPointer());
}

void COutput::unPatch()
{
	if (m_patchedInput != 0)
	{
		m_patchedInput = 0;
		for (PlugList::iterator it = m_plugs.begin();
		it != m_plugs.end(); ++it)
		{
			(*it)->setData(m_data);
		}
	}
	m_vtable->setOutput(m_instance,m_index,m_data->getPointer());
}
