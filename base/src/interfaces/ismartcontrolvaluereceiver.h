#ifndef INCLUDED_ISMARTCONTROLVALUERECEIVER_H
#define INCLUDED_ISMARTCONTROLVALUERECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class ISmartControlValueReceiver
{
public:
  /**
   *
   */
	virtual void controlValueChanged( const std::string& graphName, int nodeID, int intputIndex, const utils::Buffer& newValue ) = 0;

  /**
   *
   */
	virtual void syncInputValuesStarted( const std::string& graphName ) = 0;

  /**
   *
   */
	virtual void syncInputValuesFinished( const std::string& graphName ) = 0;

};
#endif
