#ifndef INCLUDED_CONTROLVALUERECEIVERNET_H
#define INCLUDED_CONTROLVALUERECEIVERNET_H

#include "interfaces/icontrolvaluereceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class ControlValueReceiverNet : public IControlValueReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	ControlValueReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~ControlValueReceiverNet();

	void controlValueChanged( int nodeID, int intputIndex, const utils::Buffer& newValue );

	void syncInputValuesStarted(  );

	void syncInputValuesFinished(  );

};
#endif
