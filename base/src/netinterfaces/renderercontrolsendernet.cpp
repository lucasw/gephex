#include "renderercontrolsendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/irenderercontrolreceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
RendererControlSenderNet::RendererControlSenderNet()
	 : m_rec(0) {}

void RendererControlSenderNet::registerRendererControlReceiver(IRendererControlReceiver& r)
{
	m_rec = &r;
}

void RendererControlSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "RendererControlSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		m_rec->start(  );
	 }
	else 	if (command == "0001")
	 {
		m_rec->stop(  );
	 }
	else 	if (command == "0002")
	 {
		utils::String graphName;
		int nodeID;
		int inputIndex;
		utils::Buffer buf;
		bs  >> graphName >> nodeID >> inputIndex >> buf;
		m_rec->setInputValue( graphName, nodeID, inputIndex, buf );
	 }
	else 	if (command == "0003")
	 {
		utils::String graphName;
		int nodeID;
		int inputIndex;
		bs  >> graphName >> nodeID >> inputIndex;
		m_rec->syncInputValue( graphName, nodeID, inputIndex );
	 }
	else 	if (command == "0004")
	 {
		utils::String graphName;
		bs  >> graphName;
		m_rec->synchronizeInputValues( graphName );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at RendererControl";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

