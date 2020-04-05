#include "AbortMessage.h"

CAbortMessage::CAbortMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :
	CBaseMessage(ts, msgLength, msgTypeId, msgStreamId)
{

}

CAbortMessage::~CAbortMessage()
{

}

int CAbortMessage::GetProperty(uint32_t* pChunkStreamID)
{
	uint32_t chunkStreamID = 0;
	memcpy(&chunkStreamID,m_Payload.buff,m_Payload.buffLength);

	chunkStreamID = ::BigToHost32(&chunkStreamID);
	
	*pChunkStreamID = chunkStreamID;
	return SAR_OK;
}

RtmpMessageType CAbortMessage::GetType()
{
	return RtmpMessageType::ABORT_MESSAGE;
}

