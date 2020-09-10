#include "Chunks.h"
#include "Rtmp/Util/RtmpUtils.h"
#include "Rtmp/RtmpApp/RtmpInstance/InstanceManager.h"


int CChunks::AbortMessageHandle(uint32_t csid)
{
	return CReceiveChunk::Abort(csid);
}

int CChunks::AcknowledgementHandle(uint32_t sequenceNumber)
{
	return -1;
}

int CChunks::AggregateMessageHandle(uint32_t sequenceNumber)
{
	return -1;
}

int CChunks::AudioMessageHandle()
{
	return -1;
}

int CChunks::CommandMessageHandle()
{
	return -1;
}

int CChunks::DataMessageHandle()
{
	return -1;
}

int CChunks::SetChunkSizeHandle(uint32_t chunkSize)
{
	m_ChunkSize = chunkSize;
	return 0;
}

int CChunks::SetPeerBandwidthHandle() 
{
	return -1;
}

int CChunks::SharedObjectMessageHandle()
{
	return -1;
}

int CChunks::UserControlMessagesHandle()
{
	return -1;
}

int CChunks::VideoMessageHandle()
{
	return -1;
}

int CChunks::WindowAcknowledgementSizeHandle(uint32_t winAckSize)
{
	return -1;
}
