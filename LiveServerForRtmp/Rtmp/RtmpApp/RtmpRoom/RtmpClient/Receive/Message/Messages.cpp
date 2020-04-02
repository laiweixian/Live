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


int CMessages::ParseChunk(uint8_t* src, const int srcLength)
{
	int headerLen = 0 , dataLen = 0 ;
	CChunkHeader* pHeader = NULL;
	CBaseMessage* pMsg = NULL;
	bool newMsg = false;

	if (src == NULL || srcLength <= 0)
		return 0;

	//chunk header
	pHeader = ParseChunkHeader(src,srcLength,&headerLen);
	if (pHeader == NULL)
		return 0;

	//chunk data
	pMsg = ParseMessage(pHeader,src+headerLen,srcLength-headerLen);
	if (pMsg == NULL)
		pMsg = m_Message;
	dataLen = pMsg->GetRemainSize() > m_ChunkSize ? m_ChunkSize : pMsg->GetRemainSize();
		
	//
	if (srcLength < headerLen + dataLen)
	{
		delete pHeader;
		if (pMsg != m_Message)
			delete pMsg;
		return 0;
	}
	
	return (headerLen+dataLen);
}

CChunkHeader* CMessages::ParseChunkHeader(uint8_t* src, const int srcLength, int* outLen)
{
	CChunkHeader *pHeader = NULL;
	int headerLen = 0;

	if (src == NULL || srcLength == 0)
		goto null_chunk;

	pHeader = CChunk::Parse(src, srcLength, &headerLen);
	if (pHeader == NULL)
		goto null_chunk;

	switch (pHeader->fmt)
	{
	case 0x00:
		break;
	case 0x01:
		pHeader->timestamp		 = m_ChunkHeader->timestamp + pHeader->timestampDelta;
		pHeader->messageStreamID = m_ChunkHeader->messageStreamID;
		break;

	case 0x02:	
		pHeader->timestamp		 = m_ChunkHeader->timestamp + pHeader->timestampDelta;
		pHeader->messageLength	 = m_ChunkHeader->messageLength;
		pHeader->messageTypeID	 = m_ChunkHeader->messageTypeID;
		pHeader->messageStreamID = m_ChunkHeader->messageStreamID;
		break;

	case 0x03:
		pHeader->timestamp		   = m_ChunkHeader->timestamp + m_ChunkHeader->timestampDelta;
		pHeader->timestampDelta    = m_ChunkHeader->timestampDelta;
		pHeader->messageLength     = m_ChunkHeader->messageLength;
		pHeader->messageTypeID     = m_ChunkHeader->messageTypeID;
		pHeader->messageStreamID   = m_ChunkHeader->messageStreamID;
		pHeader->extendedTimestamp = pHeader->extendedTimestamp;
		break;

	default:
		break;
	}

	*outLen = headerLen;
	return pHeader;
null_chunk:
	*outLen = 0;
	return NULL;
}

CBaseMessage* CMessages::ParseMessage(CChunkHeader* pHeader, uint8_t* src, const int srcLength)
{
	CBaseMessage* pMsg = NULL;
	int dataLen = 0;
	bool newMsg = false;

	switch (pHeader->fmt)
	{
	case 0x00:	newMsg = true; break;
	case 0x01:	newMsg = true; break;
	case 0x02:	newMsg = true; break;
	case 0x03:
		if (m_Message == NULL)
			newMsg = true;
		else
			newMsg = false;
		break;
	default:
		break;
	}

	if (newMsg == false)
		return NULL;

	pMsg = CRtmpMessage::CreateMessage(pHeader->timestamp, pHeader->messageLength, pHeader->messageTypeID, pHeader->messageStreamID);
	return pMsg;
}
