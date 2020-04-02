#include "Messages.h"

CMessages::CMessages(const int chunkSize) : m_ChunkSize(chunkSize)
{
	m_ChunkHeader = NULL;
	m_Message = NULL;
}

CMessages::~CMessages()
{
	delete m_ChunkHeader;
	delete m_Message;
}

int CMessages::OnRtmpMessage(uint8_t* src, const int srcLength)
{
	
}

int CMessages::ParseChunk(void* src, const int srcLength)
{
	CChunkHeader *pHeader = NULL;
	CBaseMessage *pMsg = NULL;
	bool newMsg = false;
	int headerLength = 0;
	int dataLength = 0;

	if (src == NULL || srcLength == 0)
		return 0;

	pHeader = CChunk::Parse(src, srcLength, &headerLength);
	if (pHeader == NULL)
		return 0;

	switch (pHeader->fmt)
	{
	case 0x00:
		newMsg = true;
		break;
	case 0x01:
		pHeader->timestamp		 = m_ChunkHeader->timestamp + pHeader->timestampDelta;
		pHeader->messageStreamID = m_ChunkHeader->messageStreamID;
		newMsg = true;
		break;

	case 0x02:	
		pHeader->timestamp		 = m_ChunkHeader->timestamp + pHeader->timestampDelta;
		pHeader->messageLength	 = m_ChunkHeader->messageLength;
		pHeader->messageTypeID	 = m_ChunkHeader->messageTypeID;
		pHeader->messageStreamID = m_ChunkHeader->messageStreamID;
		newMsg = true;
		break;

	case 0x03:
		pHeader->timestamp		   = m_ChunkHeader->timestamp + m_ChunkHeader->timestampDelta;
		pHeader->timestampDelta    = m_ChunkHeader->timestampDelta;
		pHeader->messageLength     = m_ChunkHeader->messageLength;
		pHeader->messageTypeID     = m_ChunkHeader->messageTypeID;
		pHeader->messageStreamID   = m_ChunkHeader->messageStreamID;
		pHeader->extendedTimestamp = pHeader->extendedTimestamp;
		
		if (m_Message->GetRemainSize() > 0)
			newMsg = false;
		else
			newMsg = true;
		break;
	default:
		break;
	}
	delete m_ChunkHeader;
	m_ChunkHeader = pHeader;
	
	if (newMsg)
	{
		delete m_Message;
		pMsg = CRtmpMessage::CreateMessage(pHeader->timestamp, pHeader->messageLength, pHeader->messageTypeID, pHeader->messageStreamID);
		m_Message = pMsg;
	}
	else 
		pMsg = m_Message;

	dataLength = pMsg->GetRemainSize() > m_ChunkSize ? m_ChunkSize : pMsg->GetRemainSize();
	pMsg->Append((uint8_t*)src+headerLength,dataLength);

	if (pMsg->GetRemainSize() == 0)
	{
		
	}

	return (headerLength+dataLength);
}