#include "Message.h"

CMessage::CMessage(SendToPeer sendToPeer):IReceive(sendToPeer) ,m_ChunkSize(CHUNK_SIZE)
{
	m_Msg = NULL;
	m_PrevHeader = NULL;
}

CMessage::~CMessage()
{
	delete m_Msg;
	delete m_PrevHeader;
}

int CMessage::OnReceive(void* src, const int srcLength)
{
	
}

int CMessage::ParseChunk(void* src, const int srcLength)
{
	CChunkHeader *pHeader = NULL;
	CRtmpMsg *pMsg = NULL;
	bool newMsg = false;
	int headerLength = 0;
	int dataLength = 0;

	pHeader = CChunk::Parse(src, srcLength, &headerLength);
	if (pHeader == NULL)
		return 0;

	switch (pHeader->fmt)
	{
	case 0x00:
		newMsg = true;
		break;
	case 0x01:
		pHeader->timestamp		 = m_PrevHeader->timestamp + pHeader->timestampDelta;
		pHeader->messageStreamID = m_PrevHeader->messageStreamID;
		newMsg = true;
		break;

	case 0x02:	
		pHeader->timestamp		 = m_PrevHeader->timestamp + pHeader->timestampDelta;
		pHeader->messageLength	 = m_PrevHeader->messageLength;
		pHeader->messageTypeID	 = m_PrevHeader->messageTypeID;
		pHeader->messageStreamID = m_PrevHeader->messageStreamID;
		newMsg = true;
		break;

	case 0x03:
		pHeader->timestamp		   = m_PrevHeader->timestamp + m_PrevHeader->timestampDelta;
		pHeader->timestampDelta    = m_PrevHeader->timestampDelta;
		pHeader->messageLength     = m_PrevHeader->messageLength;
		pHeader->messageTypeID     = m_PrevHeader->messageTypeID;
		pHeader->messageStreamID   = m_PrevHeader->messageStreamID;
		pHeader->extendedTimestamp = pHeader->extendedTimestamp;
		
		if (m_Msg->GetRemainSize() > 0)
			newMsg = false;
		else
			newMsg = true;
		break;
	default:
		break;
	}
	delete m_PrevHeader;
	m_PrevHeader = pHeader;
	
	if (newMsg)
	{
		delete m_Msg;
		pMsg = new CRtmpMsg(pHeader->timestamp, pHeader->messageLength, pHeader->messageTypeID, pHeader->messageStreamID);
		m_Msg = pMsg;
	}
	else 
		pMsg = m_Msg;

	dataLength = pMsg->GetRemainSize() > m_ChunkSize ? m_ChunkSize : pMsg->GetRemainSize();
	pMsg->Append((uint8_t*)src+headerLength,dataLength);

	if (pMsg->GetRemainSize() == 0)
	{

	}

	return (headerLength+dataLength);
}