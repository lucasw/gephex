#include "modulestatisticsreceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModuleStatisticsReceiverNet::ModuleStatisticsReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

ModuleStatisticsReceiverNet::~ModuleStatisticsReceiverNet()
{}

void ModuleStatisticsReceiverNet::modExecTimeSignal( int nodeID, double execTime )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << nodeID << ' '  << execTime;
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

