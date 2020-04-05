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
	int headerLen = 0 , dataLen = 0;
	int ret = 0;
	int offset = 0;
	CBaseMessage *pMsg = NULL;

	while (1)
	{
		headerLen = 0;
		dataLen = 0;
		pMsg = NULL;

		if (offset >= srcLength)
			break;

		ret = ParseChunk(src+offset,srcLength-offset,&headerLen,&dataLen,&pMsg);
		if (ret != 0)
			break;
		
		//refresh message
		if (pMsg)
			m_Message = pMsg;

		//handle rtmp message
		m_Message->Append(src+offset+headerLen,dataLen);
		if (m_Message->GetRemainSize() == 0)
		{
			HandleMessage(m_Message);
			m_Message = NULL;
		}

		offset += (headerLen + dataLen);
	}

	return offset;
}

int CMessages::ParseChunk(uint8_t* src, const int srcLength, int* outHeaderLen, int* outDataLen, CBaseMessage** outMsg)
{
	int headerLen = 0, dataLen = 0;
	CChunkHeader* pHeader = NULL;
	CBaseMessage* pMsg = NULL;
	bool newMsg = false;

	if (src == NULL || srcLength <= 0)	goto parse_failure;

	//chunk header
	pHeader = ParseChunkHeader(src, srcLength, &headerLen);
	if (pHeader == NULL)				goto parse_failure;

	//chunk data
	pMsg = ParseMessage(pHeader, src + headerLen, srcLength - headerLen);
	if (pMsg == NULL)
		dataLen = m_Message->GetRemainSize() > m_ChunkSize ? m_ChunkSize : m_Message->GetRemainSize();
	else 
		dataLen = pMsg->GetRemainSize() > m_ChunkSize ? m_ChunkSize : pMsg->GetRemainSize();

	//check length
	if (srcLength < headerLen + dataLen)
	{
		delete pHeader;
		if (!pMsg)	delete pMsg;
		goto parse_failure;
	}
	
	//refresh header
	if (m_ChunkHeader)
		delete m_ChunkHeader;
	m_ChunkHeader = pHeader;

	//out value
	*outHeaderLen = headerLen;
	*outDataLen = dataLen;
	*outMsg = pMsg;
	return 0;

parse_failure:
	*outHeaderLen = 0;
	*outDataLen = 0;
	*outMsg = NULL;
	return -1;
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

void CMessages::HandleMessage(CBaseMessage* pMsg)
{
	switch (pMsg->GetType())
	{
	case RtmpMessageType::INVALID:
		break;
	case RtmpMessageType::SET_CHUNK_SIZE:
		HandleSetChunkSize(dynamic_cast<CSetChunkSize*>(pMsg));
		break;
	case RtmpMessageType::ABORT_MESSAGE:
		HandleAbortMessage(dynamic_cast<CAbortMessage*>(pMsg));
		break;
	case RtmpMessageType::ACKNOWLEDGEMENT:
		HandleAcknowledgement(dynamic_cast<CAcknowledgement*>(pMsg));
		break;
	case RtmpMessageType::WINDOW_ACKNOWLEDGEMENT_SIZE:
		HandleWindowAcknowledgementSize(dynamic_cast<CWindowAcknowledgementSize*>(pMsg));
		break;
	case RtmpMessageType::SET_PEER_BADNWIDTH:
		HandleSetPeerBandwidth(dynamic_cast<CSetPeerBandwidth*>(pMsg));
		break;
	case RtmpMessageType::USER_CONTROL_MESSAGES:
		HandleUserControlMessages(dynamic_cast<CUserControlMessages*>(pMsg));
		break;
	case RtmpMessageType::COMMAND_MESSAGE:
		HandleCommandMessage(dynamic_cast<CCommandMessage*>(pMsg));
		break;
	case RtmpMessageType::DATA_MESSAGE:
		HandleDataMessage(dynamic_cast<CDataMessage*>(pMsg));
		break;
	case RtmpMessageType::SHARED_OBJECT_MESSAGE:
		HandleSharedObjectMessage(dynamic_cast<CSharedObjectMessage*>(pMsg));
		break;
	case RtmpMessageType::AUDIO_MESSAGE:
		HandleAudioMessage(dynamic_cast<CAudioMessage*>(pMsg));
		break;
	case RtmpMessageType::VIDEO_MESSAGE:
		HandleVideoMessage(dynamic_cast<CVideoMessage*>(pMsg));
		break;
	case RtmpMessageType::AGGREGATE_MESSAGE:
		HandleAggregateMessage(dynamic_cast<CAggregateMessage*>(pMsg));
		break;
	default:
		break;
	}
}

void CMessages::HandleSetChunkSize(CSetChunkSize* pMsg)
{
	if (!pMsg)	return ;

	m_ChunkSize = pMsg->GetChunkSize();
	delete pMsg;
}

void CMessages::HandleAbortMessage(CAbortMessage* pMsg)
{
	if (!pMsg)	return;

	uint32_t chunkStreamID = pMsg->GetChunkStreamID();
	

}

void CMessages::HandleAcknowledgement(CAcknowledgement* pMsg)
{
	if (!pMsg)	return;
}

void CMessages::HandleWindowAcknowledgementSize(CWindowAcknowledgementSize* pMsg)
{
	if (!pMsg)	return;
}

void CMessages::HandleSetPeerBandwidth(CSetPeerBandwidth* pMsg)
{
	if (!pMsg)	return;
}

void CMessages::HandleUserControlMessages(CUserControlMessages* pMsg)
{
	if (!pMsg)	return;
}

void CMessages::HandleCommandMessage(CCommandMessage* pMsg)
{
	if (!pMsg)	return;
}

void CMessages::HandleDataMessage(CDataMessage* pMsg)
{
	if (!pMsg)	return;
}

void CMessages::HandleSharedObjectMessage(CSharedObjectMessage* pMsg)
{
	if (!pMsg)	return;
}

void CMessages::HandleAudioMessage(CAudioMessage* pMsg)
{
	if (!pMsg)	return;
}

void CMessages::HandleVideoMessage(CVideoMessage* pMsg)
{
	if (!pMsg)	return;
}

void CMessages::HandleAggregateMessage(CAggregateMessage* pMsg)
{
	if (!pMsg)	return;
}