#include "c_outputplug.h"

COutputPlug::COutputPlug(IOutput& out,IInput& in)
 : output(&out), input(&in), data(0)
{
}

COutputPlug::~COutputPlug()
{
  //	output->unPlug(*this->getInput());
}

void COutputPlug::setData(const IType* _data)
{
	data = _data;
}

const IType* COutputPlug::getData() const
{
	return data;
}

IOutput* COutputPlug::getOutput(void) const
{
	return output;
}

IModule* COutputPlug::getModule(void) const
{
	return output->getModule();
}

IInput* COutputPlug::getInput(void) const
{
	return input;
}

/*bool COutputPlug::hasChanged() const
{
	return output->hasChanged();
}*/

bool COutputPlug::isConst() const
{
  return input->isConst();
}
