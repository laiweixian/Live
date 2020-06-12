#include "AbortMessage.h"

CAbortMessage::CAbortMessage(uint32_t csid,uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :
	CBaseMessage(csid,ts, msgLength, msgTypeId, msgStreamId),m_Content({0})
{

}

CAbortMessage::~CAbortMessage()
{

}

CAbortMessage::Content CAbortMessage::GetContent()
{
	uint32_t chunkStreamID = 0;
	memcpy(&chunkStreamID,m_Payload.buff,m_Payload.buffLength);

	m_Content.chunkStreamID = ::BigToHost32(&chunkStreamID);
	return m_Content;
}

CBaseMessage::MessageType CAbortMessage::GetType()
{
	return CBaseMessage::MessageType::ABORT_MESSAGE;
}

