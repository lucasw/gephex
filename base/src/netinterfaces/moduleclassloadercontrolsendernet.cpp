#include "moduleclassloadercontrolsendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/imoduleclassloadercontrolreceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModuleClassLoaderControlSenderNet::ModuleClassLoaderControlSenderNet()
	 : m_rec(0) {}

void ModuleClassLoaderControlSenderNet::registerModuleClassLoaderControlReceiver(IModuleClassLoaderControlReceiver& r)
{
	m_rec = &r;
}

void ModuleClassLoaderControlSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "ModuleClassLoaderControlSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		utils::String name;
		bs  >> name;
		m_rec->loadModuleClass( name );
	 }
	else 	if (command == "0001")
	 {
		utils::String name;
		bs  >> name;
		m_rec->unloadModuleClass( name );
	 }
	else 	if (command == "0002")
	 {
		m_rec->synchronize(  );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at ModuleClassLoaderControl";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

