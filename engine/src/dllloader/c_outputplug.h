#ifndef INCLUDED_OUTPUTPLUG_H
#define INCLUDED_OUTPUTPLUG_H

#include "interfaces/imodule.h"

class IType;

class COutputPlug : public IOutputPlug
{
public:
	COutputPlug(IOutput&,IInput&);
	virtual ~COutputPlug();

	virtual void setData(const IType* data);

	virtual const IType* getData() const;

	virtual IOutput* getOutput() const;

	virtual IModule* getModule() const;

	virtual IInput* getInput() const;

        virtual bool isConst() const;

private:
	IOutput* output;
	IInput* input;
	const IType* data;
};

#endif
