#include "rendererstatussendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/irendererstatusreceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
RendererStatusSenderNet::RendererStatusSenderNet()
	 : m_rec(0) {}

void RendererStatusSenderNet::registerRendererStatusReceiver(IRendererStatusReceiver& r)
{
	m_rec = &r;
}

void RendererStatusSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "RendererStatusSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		m_rec->started(  );
	 }
	else 	if (command == "0001")
	 {
		m_rec->stopped(  );
	 }
	else 	if (command == "0002")
	 {
		utils::String graphID;
		bs  >> graphID;
		m_rec->renderedGraphChanged( graphID );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at RendererStatus";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

