#include "enginecontrolsendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/ienginecontrolreceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
EngineControlSenderNet::EngineControlSenderNet()
	 : m_rec(0) {}

void EngineControlSenderNet::registerEngineControlReceiver(IEngineControlReceiver& r)
{
	m_rec = &r;
}

void EngineControlSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "EngineControlSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		m_rec->disconnect(  );
	 }
	else 	if (command == "0001")
	 {
		m_rec->shutDown(  );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at EngineControl";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

