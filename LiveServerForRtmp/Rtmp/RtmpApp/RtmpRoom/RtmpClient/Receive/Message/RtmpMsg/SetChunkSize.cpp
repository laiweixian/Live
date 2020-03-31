#include "SetChunkSize.h"

CSetChunkSize::CSetChunkSize(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform):\
	CBaseMsg(ts,msgLength,msgTypeId,msgStreamId,inform)
{

}

CSetChunkSize::~CSetChunkSize()
{

}

RtmpMessageType CSetChunkSize::GetType()
{
	return RtmpMessageType::SET_CHUNK_SIZE;
}

void CSetChunkSize::Inform()
{

}