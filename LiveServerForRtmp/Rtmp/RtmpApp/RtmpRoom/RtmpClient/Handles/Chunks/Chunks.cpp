#include "Chunks.h"

#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}
	
CChunks::CChunks(IMessageCall* pCall, IMessageEvent* pEvent, const uint32_t chunkSize) : \
	m_pCall(pCall),m_pEvent(pEvent),m_ChunkSize(chunkSize),\
	m_ChunkHeader(NULL), m_Message(NULL)
{

}

CChunks::~CChunks()
{
	DELETE_PTR(m_ChunkHeader)
	DELETE_PTR(m_Message)
}

int CChunks::OnChunks(uint8_t* src, const int srcLength)
{
	int chunkLen = 0;
	int offset = 0;

	if (srcLength <= 0 || src == NULL)
		return 0;

	while (srcLength > offset)
	{
		chunkLen = this->ReceChunk(src+offset,srcLength-offset);
		if (chunkLen == 0)
			break;

		if(m_Message->GetRemainSize() == 0)
			HandleMessage(m_Message);
		
		offset += chunkLen;
	}
	return offset;
}

int CChunks::ReceChunk(uint8_t* src, const int srcLength)
{
	CChunkHeader *pHeader = NULL;
	CBaseMessage *pMsg = NULL ,*pTempMsg = NULL;
	int headerLen = 0 , dataLen = 0;

	//check chunk header is complete
	pHeader = ReceChunkHeader(src,srcLength,&headerLen);
	if (pHeader == NULL)
		goto failure;

	//check new message
	pMsg = ReceMessage(pHeader);
	pTempMsg = (pMsg == NULL ? m_Message : pMsg);
	
	//check chunk data is complete
	dataLen = ReceMessagePayload(pTempMsg,src+headerLen,srcLength-headerLen);
	if (dataLen == 0)
		goto failure;

	//refersh
	PushChunkHeader(pHeader);
	if (pMsg)
		PushMessage(pMsg);

	return (headerLen + dataLen);

failure:
	DELETE_PTR(pHeader)
	DELETE_PTR(pMsg)
	return 0;
}

CChunkHeader* CChunks::ReceChunkHeader(uint8_t* src, const int srcLength, int* outHeadLen)
{
	CChunkHeader *pHeader = NULL;
	CChunkHeader::Head header = { 0 };
	int headerLen = 0;

	if (src == NULL || srcLength == 0)
		goto null_chunk;

	pHeader = CChunkHeader::Parse(src, srcLength, &headerLen);
	if (pHeader == NULL)
		goto null_chunk;

	header = pHeader->GetHead();
	switch (header.fmt)
	{
	case 0x00:
		break;
	case 0x01:
		header.timestamp = m_ChunkHeader->GetHead().timestamp + header.timestampDelta;
		header.messageStreamID = m_ChunkHeader->GetHead().messageStreamID;

		delete pHeader;
		pHeader = CChunkHeader::Parse(header);
		break;

	case 0x02:
		header.timestamp = m_ChunkHeader->GetHead().timestamp + header.timestampDelta;
		header.messageLength = m_ChunkHeader->GetHead().messageLength;
		header.messageTypeID = m_ChunkHeader->GetHead().messageTypeID;
		header.messageStreamID = m_ChunkHeader->GetHead().messageStreamID;

		delete pHeader;
		pHeader = CChunkHeader::Parse(header);
		break;

	case 0x03:
		header.timestamp = m_ChunkHeader->GetHead().timestamp + m_ChunkHeader->GetHead().timestampDelta;
		header.timestampDelta = m_ChunkHeader->GetHead().timestampDelta;
		header.messageLength = m_ChunkHeader->GetHead().messageLength;
		header.messageTypeID = m_ChunkHeader->GetHead().messageTypeID;
		header.messageStreamID = m_ChunkHeader->GetHead().messageStreamID;
		header.extendedTimestamp = m_ChunkHeader->GetHead().extendedTimestamp;

		delete pHeader;
		pHeader = CChunkHeader::Parse(header);
		break;

	default:
		break;
	}

	*outHeadLen = headerLen;
	return pHeader;
null_chunk:
	*outHeadLen = 0;
	return NULL;
}

CBaseMessage* CChunks::ReceMessage(CChunkHeader* pHeader)
{
	const CChunkHeader::Head header = pHeader->GetHead();
	bool isNewMsg = false;
	CBaseMessage* pNewMsg = NULL;

	switch (header.fmt)
	{
	case 0x00:	isNewMsg = true;	break;
	case 0x01:	isNewMsg = true;	break;
	case 0x02:	isNewMsg = true;	break;
	case 0x03:	
		if (m_Message == NULL)
			isNewMsg = true;
		else
			isNewMsg = (m_Message->GetRemainSize() == 0);
	
		break;
	default:
		return false;
		break;
	}

	if (isNewMsg)
		pNewMsg = CRtmpMessage::CreateMessage(header.csid,		 \
												header.timestamp,	  \
												header.messageLength, \
												header.messageTypeID, \
												header.messageStreamID);
	return pNewMsg;
}

int CChunks::ReceMessagePayload(CBaseMessage *pMsg, uint8_t* src, const int srcLen)
{
	int dataLen = 0;
	
	dataLen = pMsg->GetRemainSize() > m_ChunkSize ? m_ChunkSize : pMsg->GetRemainSize();
	if (dataLen > srcLen)
		return 0;
	pMsg->Append(src,dataLen);
	return dataLen;
}

void CChunks::PushChunkHeader(CChunkHeader *pHeader)
{
	if (!pHeader)	return;
	DELETE_PTR(pHeader)
	m_ChunkHeader = pHeader;
}

void CChunks::PushMessage(CBaseMessage *pMsg)
{
	if (!pMsg)	return;
	DELETE_PTR(m_Message)
		m_Message = pMsg;
}

void CChunks::HandleMessage(CBaseMessage* pMsg)
{
	switch (pMsg->GetType())
	{
	case CBaseMessage::MessageType::INVALID:
		break;
	case CBaseMessage::MessageType::SET_CHUNK_SIZE:
		HandleSetChunkSize(dynamic_cast<CSetChunkSize*>(pMsg));
		break;
	case CBaseMessage::MessageType::ABORT_MESSAGE:
		HandleAbortMessage(dynamic_cast<CAbortMessage*>(pMsg));
		break;
	case CBaseMessage::MessageType::ACKNOWLEDGEMENT:
		HandleAcknowledgement(dynamic_cast<CAcknowledgement*>(pMsg));
		break;
	case CBaseMessage::MessageType::WINDOW_ACKNOWLEDGEMENT_SIZE:
		HandleWindowAcknowledgementSize(dynamic_cast<CWindowAcknowledgementSize*>(pMsg));
		break;
	case CBaseMessage::MessageType::SET_PEER_BADNWIDTH:
		HandleSetPeerBandwidth(dynamic_cast<CSetPeerBandwidth*>(pMsg));
		break;
	case CBaseMessage::MessageType::USER_CONTROL_MESSAGES:
		HandleUserControlMessages(dynamic_cast<CUserControlMessages*>(pMsg));
		break;
	case CBaseMessage::MessageType::COMMAND_MESSAGE:
		HandleCommandMessage(dynamic_cast<CCommandMessage*>(pMsg));
		break;
	case CBaseMessage::MessageType::DATA_MESSAGE:
		HandleDataMessage(dynamic_cast<CDataMessage*>(pMsg));
		break;
	case CBaseMessage::MessageType::SHARED_OBJECT_MESSAGE:
		HandleSharedObjectMessage(dynamic_cast<CSharedObjectMessage*>(pMsg));
		break;
	case CBaseMessage::MessageType::AUDIO_MESSAGE:
		HandleAudioMessage(dynamic_cast<CAudioMessage*>(pMsg));
		break;
	case CBaseMessage::MessageType::VIDEO_MESSAGE:
		HandleVideoMessage(dynamic_cast<CVideoMessage*>(pMsg));
		break;
	case CBaseMessage::MessageType::AGGREGATE_MESSAGE:
		HandleAggregateMessage(dynamic_cast<CAggregateMessage*>(pMsg));
		break;
	default:
		break;
	}
}

void CChunks::HandleSetChunkSize(CSetChunkSize* pMsg)
{
	if (!pMsg)	return ;

	m_ChunkSize = pMsg->GetContent().chunkSize;
	delete pMsg;

	if (m_pEvent)	m_pEvent->OnSetChunkSize();
}

void CChunks::HandleAbortMessage(CAbortMessage* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleAcknowledgement(CAcknowledgement* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleWindowAcknowledgementSize(CWindowAcknowledgementSize* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleSetPeerBandwidth(CSetPeerBandwidth* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleUserControlMessages(CUserControlMessages* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleCommandMessage(CCommandMessage* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleDataMessage(CDataMessage* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleSharedObjectMessage(CSharedObjectMessage* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleAudioMessage(CAudioMessage* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleVideoMessage(CVideoMessage* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleAggregateMessage(CAggregateMessage* pMsg)
{
	if (!pMsg)	return;
}