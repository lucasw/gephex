#include "moduleclassinforeceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModuleClassInfoReceiverNet::ModuleClassInfoReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

ModuleClassInfoReceiverNet::~ModuleClassInfoReceiverNet()
{}

void ModuleClassInfoReceiverNet::moduleClassLoaded( const std::string& moduleClassName, const utils::Buffer& buf )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(moduleClassName) << ' '  << buf;
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void ModuleClassInfoReceiverNet::moduleClassUnloaded( const std::string& moduleClassID )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(moduleClassID);
	bs.flush();
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void ModuleClassInfoReceiverNet::syncStarted(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

void ModuleClassInfoReceiverNet::syncFinished(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0003" );
	m_tagger->send( temp_buf_ );

}

