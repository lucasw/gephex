#include "moduleclassloadercontrolreceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModuleClassLoaderControlReceiverNet::ModuleClassLoaderControlReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

ModuleClassLoaderControlReceiverNet::~ModuleClassLoaderControlReceiverNet()
{}

void ModuleClassLoaderControlReceiverNet::loadModuleClass( const std::string& name )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(name);
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void ModuleClassLoaderControlReceiverNet::unloadModuleClass( const std::string& name )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(name);
	bs.flush();
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void ModuleClassLoaderControlReceiverNet::synchronize(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

