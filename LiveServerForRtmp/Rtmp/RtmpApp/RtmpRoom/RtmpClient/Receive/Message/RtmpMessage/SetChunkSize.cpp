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

