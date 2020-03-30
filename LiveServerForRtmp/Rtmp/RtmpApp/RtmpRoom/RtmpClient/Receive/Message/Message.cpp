#include "Message.h"

CMessage::CMessage(SendToPeer sendToPeer):IReceive(sendToPeer)
{

}

CMessage::~CMessage()
{
	m_PrevHeader = NULL;
}

int CMessage::OnReceive(void* src, const int srcLength)
{
	
}

int CMessage::ParseChunk(void* src, const int srcLength)
{
	CChunkHeader *pHeader = NULL;
	int length = 0;

	pHeader = CChunk::Parse(src, srcLength, &length);
	if (pHeader == NULL)
		return 0;

	switch (pHeader->fmt)
	{
	case 0x00:
		break;
	case 0x01:
		pHeader->timestamp = m_PrevHeader->timestamp + pHeader->timestampDelta;
		pHeader->messageStreamID = m_PrevHeader->messageStreamID;
		break;
	case 0x02:	
		pHeader->timestamp = m_PrevHeader->timestamp + pHeader->timestampDelta;
		pHeader->messageLength = m_PrevHeader->messageLength;
		pHeader->messageTypeID = m_PrevHeader->messageTypeID;
		pHeader->messageStreamID = m_PrevHeader->messageStreamID;
		break;
	case 0x03:
		pHeader->timestamp = m_PrevHeader->timestamp + m_PrevHeader->timestampDelta;
		pHeader->timestampDelta = m_PrevHeader->timestampDelta;
		pHeader->messageLength = m_PrevHeader->messageLength;
		pHeader->messageTypeID = m_PrevHeader->messageTypeID;
		pHeader->messageStreamID = m_PrevHeader->messageStreamID;
		pHeader->extendedTimestamp = pHeader->extendedTimestamp;


		break;
	default:
		break;
	}

	delete m_PrevHeader;
	m_PrevHeader = pHeader;


	//
	


}