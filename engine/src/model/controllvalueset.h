#ifndef CONTROLLVALUESET_H
#define CONTROLLVALUESET_H

#include <string>
#include <map>
#include "utils/buffer.h"
/*
namespace utils
{
  class Buffer;
} */

namespace model
{

  class ControllValueSet 
    {
    public: 
      ControllValueSet(const std::string& id, const std::string& name);
      ~ControllValueSet();

      std::string getID() const;

      std::string getName() const;
      void setName(const std::string& name);

      void setControlValue(int nodeID,int inputIndex,
			   const utils::Buffer& value);

      void deleteControllValue(int nodeID,int inputIndex);

      typedef std::map<std::pair<int,int>,utils::Buffer>::const_iterator const_iterator;
      const_iterator begin() const;
      const_iterator end() const;
      const_iterator find(std::pair<int,int>) const;
	

    //std::map<std::pair<int,int>,utils::Buffer> values;
    private:
      std::map<std::pair<int,int>,utils::Buffer> values;
      std::string m_id;
      std::string m_name;
    };

}
#endif


