#include "moduleconstructiondumbreceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModuleConstructionDumbReceiverNet::ModuleConstructionDumbReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

ModuleConstructionDumbReceiverNet::~ModuleConstructionDumbReceiverNet()
{}

void ModuleConstructionDumbReceiverNet::moduleAdded( const std::string& moduleClassName, int modID )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(moduleClassName) << ' '  << modID;
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void ModuleConstructionDumbReceiverNet::modulesConnected( int moduleID1, int outputIndex, int moduleID2, int inputIndex )
{
	utils::Buffer temp_buf_(64);
	utils::OBufferStream bs(temp_buf_);
	bs << moduleID1 << ' '  << outputIndex << ' '  << moduleID2 << ' '  << inputIndex;
	bs.flush();
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void ModuleConstructionDumbReceiverNet::modulesDisconnected( int moduleID, int inputIndex )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << moduleID << ' '  << inputIndex;
	bs.flush();
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

void ModuleConstructionDumbReceiverNet::moduleDeleted( int moduleID )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << moduleID;
	bs.flush();
	m_tagger->setTag( "0003" );
	m_tagger->send( temp_buf_ );

}

void ModuleConstructionDumbReceiverNet::syncModuleStarted(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0004" );
	m_tagger->send( temp_buf_ );

}

void ModuleConstructionDumbReceiverNet::syncModuleFinished(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0005" );
	m_tagger->send( temp_buf_ );

}

