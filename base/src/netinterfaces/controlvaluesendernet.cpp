#include "controlvaluesendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/icontrolvaluereceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ControlValueSenderNet::ControlValueSenderNet()
	 : m_rec(0) {}

void ControlValueSenderNet::registerControlValueReceiver(IControlValueReceiver& r)
{
	m_rec = &r;
}

void ControlValueSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "ControlValueSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		int nodeID;
		int intputIndex;
		utils::Buffer newValue;
		bs  >> nodeID >> intputIndex >> newValue;
		m_rec->controlValueChanged( nodeID, intputIndex, newValue );
	 }
	else 	if (command == "0001")
	 {
		m_rec->syncInputValuesStarted(  );
	 }
	else 	if (command == "0002")
	 {
		m_rec->syncInputValuesFinished(  );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at ControlValue";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

