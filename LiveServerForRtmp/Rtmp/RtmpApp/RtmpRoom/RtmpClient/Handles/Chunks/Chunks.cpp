#include "Chunks.h"

#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}
	
CChunks::CChunks( const uint32_t chunkSize) : m_ChunkSize(chunkSize),m_ChunkHeader(NULL), m_Message(NULL)
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

		if (m_Message->GetRemainSize() == 0)
		{
			HandleMessage(m_Message);
			
		}
			
		
		offset += chunkLen;
	}
	return offset;
}

int CChunks::ReceChunk(uint8_t* src, const int srcLength)
{
	CChunkHeader *pHeader = NULL;
	bool receMsg = false;
	int headerLen = 0 , dataLen = 0;

	//receive chunk head
	pHeader = ReceChunkHeader(src,srcLength,&headerLen);
	if (pHeader == NULL)
		goto failure;

	//receive chunk data
	receMsg = ReceChunkData(pHeader,src+headerLen,srcLength-headerLen,&dataLen);
	if (!receMsg)
		goto failure;

	//refersh
	PushChunkHeader(pHeader);
	return (headerLen + dataLen);

failure:
	DELETE_PTR(pHeader)
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
	pHeader->CopyFrom(m_ChunkHeader);

	*outHeadLen = headerLen;
	return pHeader;
null_chunk:
	*outHeadLen = 0;
	return NULL;
}

bool CChunks::ReceChunkData(CChunkHeader* pHeader, uint8_t* src, const int srcLen, int* outDataLen)
{
	const CChunkHeader::Head header = pHeader->GetHead();
	bool newMsg = false;
	CBaseMessage* pMsg = NULL;
	int dataLen = 0;

	switch (header.fmt)
	{
	case 0x00:	newMsg = true;	break;
	case 0x01:	newMsg = true;	break;
	case 0x02:	newMsg = true;	break;
	case 0x03:	
		if (m_Message == NULL)
			newMsg = true;
		else
			newMsg = (m_Message->GetRemainSize() == 0);
		break;
	default:
		goto failure;
		break;
	}

	if (newMsg)
		pMsg = CRtmpMessage::CreateMessage(header.csid,header.timestamp,header.messageLength,header.messageTypeID,header.messageStreamID);
	else 
		pMsg = m_Message;

	dataLen = pMsg->GetRemainSize() > m_ChunkSize ? m_ChunkSize : pMsg->GetRemainSize();
	if (dataLen > srcLen)
		goto failure;

	pMsg->Append(src,dataLen);
	*outDataLen = dataLen;	
	if (newMsg) PushMessage(pMsg);
	return true;

failure:
	if (newMsg) delete pMsg;
	*outDataLen = 0;
	return false;
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
	const CSetChunkSize::Content content = pMsg->GetContent();

	m_ChunkSize = content.chunkSize;

}

void CChunks::HandleAbortMessage(CAbortMessage* pMsg)
{
	if (!pMsg)	return;

	const CAbortMessage::Content content = pMsg->GetContent();

}

void CChunks::HandleAcknowledgement(CAcknowledgement* pMsg)
{
	if (!pMsg)	return;
	const CAcknowledgement::Content content = pMsg->GetContent();
}

void CChunks::HandleWindowAcknowledgementSize(CWindowAcknowledgementSize* pMsg)
{
	if (!pMsg)	return;
	const CWindowAcknowledgementSize::Content content = pMsg->GetContent();
}

void CChunks::HandleSetPeerBandwidth(CSetPeerBandwidth* pMsg)
{
	if (!pMsg)	return;
	const CSetPeerBandwidth::Content content = pMsg->GetContent();
}

void CChunks::HandleUserControlMessages(CUserControlMessages* pMsg)
{
	if (!pMsg)	return;
	const CUserControlMessages::Content content = pMsg->GetContent();
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