#include "moduleclassspec.h"


ModuleClassSpec::ModuleClassSpec(int mClassID, const std::vector<int>& ins,const std::vector<int>& outs)
 : m_moduleClassID(mClassID), m_inputs(ins), m_outputs(outs)
{
}

	//std::string identifier() const;
const std::vector<int>& ModuleClassSpec::inputs() const
{
	return m_inputs;
}

const std::vector<int>& ModuleClassSpec::outputs() const
{
	return m_outputs;
}

const int ModuleClassSpec::moduleClassID() const
{
	return m_moduleClassID;
}

IModuleClassSpec* ModuleClassSpec::clone() const
{
	return new ModuleClassSpec(*this);
}