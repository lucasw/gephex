#include "modelstatussendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/imodelstatusreceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModelStatusSenderNet::ModelStatusSenderNet()
	 : m_rec(0) {}

void ModelStatusSenderNet::registerModelStatusReceiver(IModelStatusReceiver& r)
{
	m_rec = &r;
}

void ModelStatusSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "ModelStatusSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		utils::String graphID;
		utils::String snapID;
		bs  >> graphID >> snapID;
		m_rec->editGraphChanged( graphID, snapID );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at ModelStatus";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

