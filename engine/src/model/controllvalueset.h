#ifndef INCLUDED_CONTROLVALUESET_H
#define INCLUDED_CONTROLVALUESET_H

#include <string>
#include <map>
#include "utils/buffer.h"

namespace model
{

  class ControllValueSet 
    {
    public: 
      typedef int NodeID;
      typedef int InputIndex;
      typedef std::pair<NodeID,InputIndex> Control;

      typedef std::map<Control,utils::Buffer>::const_iterator const_iterator;

      /**
       * Create a new control value set for a graph
       */
      ControllValueSet(const std::string& id, const std::string& name);

      /**
       * destroys the set
       */
      ~ControllValueSet();

      /**
       * get the unique ID of the control-value set
       */
      std::string getID() const;

      /**
       * get the name of the control-value set
       */
      std::string getName() const;
      
      /**
       * change Name for the control-value set
       */
      void setName(const std::string& name);

      /**
       * add or change the value for the control
       */
      void setControlValue(NodeID nodeID,InputIndex inputIndex,
			   const utils::Buffer& value);

      /**
       * Removes the control-value pair from the set
       */
      void deleteControllValue(NodeID nodeID,InputIndex inputIndex);

      /**
       * get the iterator of the first control - value pair
       */
      const_iterator begin() const;

      /**
       * get the iterator of the control - value pair behind the last valid one
       */
      const_iterator end() const;

      /**
       * Get the control - value pair or the end() iterator if not found
       * /param key a pair of NodeID and InputIndex
       */
      const_iterator find(Control key) const;
	
    private:
      /**
       * unique id that cant be changed
       */
      const std::string m_id;

      /**
       * Name of the snapshot that is visible to the user
       */
      std::string m_name;

      /**
       * the stored values
       */
      std::map<Control,utils::Buffer> values;
    };

}
#endif
