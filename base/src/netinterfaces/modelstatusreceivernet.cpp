#include "modelstatusreceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModelStatusReceiverNet::ModelStatusReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

ModelStatusReceiverNet::~ModelStatusReceiverNet()
{}

void ModelStatusReceiverNet::editGraphChanged( const std::string& graphID, const std::string& snapID )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID) << ' '  << utils::String(snapID);
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

