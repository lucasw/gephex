#include "rendererstatusreceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
RendererStatusReceiverNet::RendererStatusReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

RendererStatusReceiverNet::~RendererStatusReceiverNet()
{}

void RendererStatusReceiverNet::started(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void RendererStatusReceiverNet::stopped(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void RendererStatusReceiverNet::renderedGraphChanged( const std::string& graphID )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID);
	bs.flush();
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

