#include "controllvalueset.h"

namespace model
{

  ControllValueSet::ControllValueSet(const std::string& id,
				     const std::string& name)
    : m_id(id), m_name(name) {}

  std::string ControllValueSet::getID() const
  {
    return m_id;
  }

  std::string ControllValueSet::getName() const
  {
    return m_name;
  }

  void ControllValueSet::setName(const std::string& name)
  {
    m_name = name;
  }

  ControllValueSet::~ControllValueSet()
  {
  }

  void ControllValueSet::setControlValue(int nodeID,int inputIndex,
					 const utils::Buffer& value)
  {
    values[std::make_pair(nodeID,inputIndex)]=value;
  }

  void ControllValueSet::deleteControllValue(int nodeID,int inputIndex)
  {
    std::map<std::pair<int,int>,utils::Buffer>::iterator
      it=values.find(std::make_pair(nodeID,inputIndex));

    if (it!=values.end())
      {
	values.erase(it);
      }
  }

  ControllValueSet::const_iterator ControllValueSet::begin() const
  {
    return values.begin();
  }

  ControllValueSet::const_iterator ControllValueSet::end() const
  {
    return values.end();
  }

  ControllValueSet::const_iterator ControllValueSet::find(std::pair<int,int> pair) const
  {
    return values.find(pair);
  }


}
