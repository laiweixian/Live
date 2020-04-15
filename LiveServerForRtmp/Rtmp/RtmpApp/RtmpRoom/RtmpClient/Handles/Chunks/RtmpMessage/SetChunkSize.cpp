#include "SetChunkSize.h"

CSetChunkSize::CSetChunkSize(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId):\
	CBaseMessage(csid,ts,msgLength,msgTypeId,msgStreamId),m_Content({0})
{

}

CSetChunkSize::~CSetChunkSize()
{

}

CBaseMessage::MessageType CSetChunkSize::GetType()
{
	return CBaseMessage::MessageType::SET_CHUNK_SIZE;
}

CSetChunkSize::Content CSetChunkSize::GetContent()
{
	uint32_t chunkSize = 0;
	memcpy(&chunkSize, m_Payload.buff, m_Payload.buffLength);
	m_Content.chunkSize = ::BigToHost32(&chunkSize);
	return m_Content;
}

