#include "renderercontrolreceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
RendererControlReceiverNet::RendererControlReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

RendererControlReceiverNet::~RendererControlReceiverNet()
{}

void RendererControlReceiverNet::start(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void RendererControlReceiverNet::stop(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void RendererControlReceiverNet::setInputValue( const std::string& graphName, int nodeID, int inputIndex, const utils::Buffer& buf )
{
	utils::Buffer temp_buf_(64);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphName) << ' '  << nodeID << ' '  << inputIndex << ' '  << buf;
	bs.flush();
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

void RendererControlReceiverNet::syncInputValue( const std::string& graphName, int nodeID, int inputIndex )
{
	utils::Buffer temp_buf_(48);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphName) << ' '  << nodeID << ' '  << inputIndex;
	bs.flush();
	m_tagger->setTag( "0003" );
	m_tagger->send( temp_buf_ );

}

void RendererControlReceiverNet::synchronizeInputValues( const std::string& graphName )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphName);
	bs.flush();
	m_tagger->setTag( "0004" );
	m_tagger->send( temp_buf_ );

}

