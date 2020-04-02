#include "SetChunkSize.h"

CSetChunkSize::CSetChunkSize(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId):\
	CBaseMessage(ts,msgLength,msgTypeId,msgStreamId)
{

}

CSetChunkSize::~CSetChunkSize()
{

}

RtmpMessageType CSetChunkSize::GetType()
{
	return RtmpMessageType::SET_CHUNK_SIZE;
}

uint32_t CSetChunkSize::GetChunkSize()
{
	uint32_t chunkSize = 0;

	memcpy(&chunkSize,m_Payload.buff, m_Payload.buffLength);
	chunkSize = ::BigToHost32(&chunkSize);
	return chunkSize;
}