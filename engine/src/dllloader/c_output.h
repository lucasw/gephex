#ifndef INCLUDED_OUTPUT_H
#define INCLUDED_OUTPUT_H

#include <list>

#include "interfaces/imodule.h"

class COutputPlug;
class IType;

class COutput : public IOutput
{
public:
	COutput(IModule& mod,int _typeID, IType* data);
	virtual ~COutput();

	//virtual void setData(const IType* data); //TODO: remove?

	virtual IModule* getModule() const;

	virtual IOutputPlug* plugIn(IInput&);

	virtual void unPlug(IInput &);

	virtual int getType() const;

  virtual std::list<IInput*> getConnectedInputs() const;

  virtual IInput* getPatchedInput() const;

  
  virtual void setPatchedInput(IInput* in);

  
  virtual void unPatch();

private:
	IModule* m_module;
	int m_typeID;
	std::list<IOutputPlug*> m_plugs;
	IType* m_data;

	IInput* m_patchedInput;

};

#endif
