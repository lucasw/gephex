#include "moduleclassspec.h"

#include <stdexcept>

ModuleClassSpec::ModuleClassSpec(const std::string& mClassName,
				 const std::vector<int>& ins,
				 const std::vector<utils::Buffer>& defaultVals,
                                 const std::vector<std::string>& inIDs,
				 const std::vector<int>& outs,
                                 const std::vector<std::string>& outIDs)
  : m_moduleClassName(mClassName),
    m_inputs(ins),
    m_defaultValues(defaultVals), 
    m_inIDs(inIDs),
    m_outputs(outs),
    m_outIDs(outIDs)
{
}

ModuleClassSpec::ModuleClassSpec(const ModuleClassSpec& spec)
 : IModuleClassSpec(),
   m_moduleClassName(spec.m_moduleClassName),
   m_inputs(spec.m_inputs),
   m_defaultValues(spec.m_defaultValues),
   m_inIDs(spec.m_inIDs),
   m_outputs(spec.m_outputs),
   m_outIDs(spec.m_outIDs)
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

int ModuleClassSpec::indexFromInputID(const std::string& id) const
{
  for (int i = 0; i < m_inIDs.size(); ++i)
    {
      if (id == m_inIDs[i])
        return i;
    }
  throw std::invalid_argument("No such input id");
}

int ModuleClassSpec::indexFromOutputID(const std::string& id) const
{
  for (int i = 0; i < m_outIDs.size(); ++i)
    {
      if (id == m_outIDs[i])
        return i;
    }
  throw std::invalid_argument("No such output id");
}

std::string ModuleClassSpec::inputID(int index) const
{
  if (index < 0 || index >= m_inIDs.size())
    throw std::invalid_argument("No such input index");

  return m_inIDs[index];
}

std::string ModuleClassSpec::outputID(int index) const
{
  if (index < 0 || index >= m_outIDs.size())
    throw std::invalid_argument("No such output index");

  return m_outIDs[index];
}
