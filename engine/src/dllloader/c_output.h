#ifndef INCLUDED_OUTPUT_H
#define INCLUDED_OUTPUT_H

#include <list>

#include "interfaces/imodule.h"

#include "utils/autoptr.h"

class COutputPlug;

class COutputVTable;

class COutput : public IOutput
{
public:
	COutput(IModule& mod,int _typeID, IType* data, int index,
			const COutputVTable& vtable, void* instance);
	virtual ~COutput();

	//virtual void setData(const IType* data); //TODO: remove?

	virtual IModule* getModule() const;

	virtual utils::AutoPtr<IOutputPlug> plugIn(IInput&);

	virtual void unPlug(IInput &);

	virtual int getType() const;

  virtual std::list<IInput*> getConnectedInputs() const;

  virtual IInput* getPatchedInput() const;

  
  virtual void setPatchedInput(IInput* in);

  
  virtual void unPatch();

private:
	IModule* m_module;
	int m_typeID;
	typedef utils::AutoPtr<IOutputPlug> IOutputPlugPtr;
	typedef std::list<IOutputPlugPtr> PlugList;
	PlugList m_plugs;
	IType* m_data;

	IInput* m_patchedInput;

	int m_index;
	const COutputVTable* m_vtable;
	void* m_instance;
};

#endif
