#ifndef INCLUDED_ICONTROLVALUERECEIVER_H
#define INCLUDED_ICONTROLVALUERECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IControlValueReceiver
{
public:
 /**
  *
  */
	virtual void controlValueChanged( int nodeID, int intputIndex, const utils::Buffer& newValue ) = 0;

 /**
  *
  */
	virtual void syncInputValuesStarted(  ) = 0;

 /**
  *
  */
	virtual void syncInputValuesFinished(  ) = 0;

};
#endif
