#include "moduleclassspec.h"

ModuleClassSpec::ModuleClassSpec(const std::string& mClassName,
				 const std::vector<int>& ins,
				 const std::vector<utils::Buffer>& defaultVals,
				 const std::vector<int>& outs)
 : m_moduleClassName(mClassName), m_inputs(ins), m_outputs(outs),
   m_defaultValues(defaultVals)
{
}

ModuleClassSpec::ModuleClassSpec(const ModuleClassSpec& spec)
 : IModuleClassSpec(),m_moduleClassName(spec.m_moduleClassName),
   m_inputs(spec.m_inputs), m_outputs(spec.m_outputs),
   m_defaultValues(spec.m_defaultValues)
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

const std::string& ModuleClassSpec::moduleClassName() const
{
  return m_moduleClassName;
}

const utils::Buffer& ModuleClassSpec::defaultValue(int input) const
{
  return m_defaultValues[input];
}


IModuleClassSpec* ModuleClassSpec::clone() const
{
  return new ModuleClassSpec(*this);
}
