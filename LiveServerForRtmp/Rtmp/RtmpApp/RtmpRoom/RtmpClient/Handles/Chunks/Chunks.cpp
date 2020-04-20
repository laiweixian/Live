#include "Chunks.h"

#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}
	
CChunks::CChunks(IMessageCall* pCall, IMessageEvent* pEvent, const uint32_t chunkSize) : \
	m_pCall(pCall),m_pEvent(pEvent),m_ChunkSize(chunkSize),\
	m_NewHeader(NULL),m_NewMsg(NULL)
{

}

CChunks::~CChunks()
{
	DELETE_PTR(m_NewMsg)
	DELETE_PTR(m_NewHeader)
}

int CChunks::OnChunks(uint8_t* src, const int srcLength)
{
	int chunkLen = 0;
	int offset = 0;

	if (srcLength <= 0 || src == NULL)
		return 0;

	while (srcLength > offset)
	{
		chunkLen = this->OnChunk(src+offset,srcLength-offset);
		if (chunkLen == 0)
			break;
		offset += chunkLen;
	}
	return offset;
}

int CChunks::OnChunk(uint8_t* src, const int srcLength)
{
	CChunkHeader *pHeader = NULL;
	CBaseMessage *pMsg = NULL ,*pTempMsg = NULL;
	int headerLen = 0 , dataLen = 0;

	//check chunk header is complete
	pHeader = OnChunkHeader(src,srcLength,&headerLen);
	if (pHeader == NULL)
		goto failure;

	//check new message
	pMsg = OnMessage(pHeader);
	pTempMsg = (pMsg == NULL ? m_NewMsg : pMsg);
	
	//check chunk data is complete
	dataLen = OnChunkData(pTempMsg,srcLength-headerLen);
	if (dataLen == 0)
		goto failure;

	//success,refresh m_NewHeader and m_NewMsg
	DELETE_PTR(m_NewHeader)
	m_NewHeader = pHeader;
	if (pMsg)		//new msg
	{
		DELETE_PTR(m_NewMsg)
		m_NewMsg = pMsg;
	}

	//append chunk data into m_NewMsg
	m_NewMsg->Append(src+headerLen,dataLen);
	if (m_NewMsg->GetRemainSize() == 0)
	{
		HandleMessage(m_NewMsg);
		m_NewMsg = NULL;
	}

	return (headerLen + dataLen);

failure:
	DELETE_PTR(pHeader)
	DELETE_PTR(pMsg)
	return 0;
}

CChunkHeader* CChunks::OnChunkHeader(uint8_t* src, const int srcLength, int* outHeadLen)
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
		header.timestamp = m_NewHeader->GetHead().timestamp + header.timestampDelta;
		header.messageStreamID = m_NewHeader->GetHead().messageStreamID;

		delete pHeader;
		pHeader = CChunkHeader::Parse(header);
		break;

	case 0x02:
		header.timestamp = m_NewHeader->GetHead().timestamp + header.timestampDelta;
		header.messageLength = m_NewHeader->GetHead().messageLength;
		header.messageTypeID = m_NewHeader->GetHead().messageTypeID;
		header.messageStreamID = m_NewHeader->GetHead().messageStreamID;

		delete pHeader;
		pHeader = CChunkHeader::Parse(header);
		break;

	case 0x03:
		header.timestamp = m_NewHeader->GetHead().timestamp + m_NewHeader->GetHead().timestampDelta;
		header.timestampDelta = m_NewHeader->GetHead().timestampDelta;
		header.messageLength = m_NewHeader->GetHead().messageLength;
		header.messageTypeID = m_NewHeader->GetHead().messageTypeID;
		header.messageStreamID = m_NewHeader->GetHead().messageStreamID;
		header.extendedTimestamp = m_NewHeader->GetHead().extendedTimestamp;

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

CBaseMessage* CChunks::OnMessage(CChunkHeader* pHeader)
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
		if (m_NewMsg == NULL)
			isNewMsg = true;
		else 
			isNewMsg = false;
		break;
	default:
		return false;
		break;
	}

	if (isNewMsg)
		pNewMsg = CRtmpMessage::CreateMessage( header.csid,		 \
												header.timestamp,	  \
												header.messageLength, \
												header.messageTypeID, \
												header.messageStreamID);
	return pNewMsg;
}

int CChunks::OnChunkData(CBaseMessage *pMsg,const int srcLength)
{
	int dataLen = 0;
	
	dataLen = pMsg->GetRemainSize() > m_ChunkSize ? m_ChunkSize : pMsg->GetRemainSize();
	return (dataLen > srcLength ? 0:dataLen);
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

	if (m_pEvent)	m_pEvent->SetChunkSize();
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