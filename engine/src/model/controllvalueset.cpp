#include "controllvalueset.h"

namespace model
{

  ControlValueSet::ControlValueSet(const std::string& id,
                                   const std::string& name)
    : m_id(id), m_name(name) {}

  std::string ControlValueSet::getID() const
  {
    return m_id;
  }

  std::string ControlValueSet::getName() const
  {
    return m_name;
  }

  void ControlValueSet::setName(const std::string& name)
  {
    m_name = name;
  }

  ControlValueSet::~ControlValueSet()
  {
  }

  void ControlValueSet::setControlValue(int nodeID,int inputIndex,
                                        const utils::Buffer& value)
  {
    values[std::make_pair(nodeID,inputIndex)] = value;
  }

  void ControlValueSet::deleteControlValue(int nodeID,int inputIndex)
  {
    ControlMap::iterator it = values.find(std::make_pair(nodeID, inputIndex));

    if (it != values.end())
      {
	values.erase(it);
      }
  }

  ControlValueSet::const_iterator ControlValueSet::begin() const
  {
    return values.begin();
  }

  ControlValueSet::const_iterator ControlValueSet::end() const
  {
    return values.end();
  }

  ControlValueSet::const_iterator
  ControlValueSet::find(const Control& pair) const
  {
    return values.find(pair);
  }


}
