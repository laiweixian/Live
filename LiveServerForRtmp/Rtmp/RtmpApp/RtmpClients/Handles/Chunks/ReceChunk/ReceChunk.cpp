#include "ReceChunk.h"

#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}

CReceiveChunk::CReceiveChunk() : m_ChunkHeader(NULL),m_Message(NULL)
{

}

CReceiveChunk::~CReceiveChunk()
{

}

int CReceiveChunk::OnChunks(uint8_t* src, const int srcLength)
{
	ReceiveMsg(src,srcLength,NULL);
}

int CReceiveChunk::ReceiveMsg(uint8_t* src, const int srcLength, CBaseMessage* pMsg)
{
	CChunkHeader *pHeader = NULL;
	CChunkHeader::Head header;
	bool newMsg = false;
	int headerLen = 0, dataLen = 0;

	//receive chunk head
	headerLen = ReadChunkHeader(src, srcLength, &pHeader);
	if (pHeader == NULL || headerLen == 0)
		goto failure;

	header = pHeader->GetHead();
	switch (header.fmt)
	{
	case 0x00:	newMsg = true;	break;
	case 0x01:	newMsg = true;	break;
	case 0x02:	newMsg = true;	break;
	case 0x03:	
		if (pMsg == NULL)
			newMsg = true;
		else
			newMsg = false;
		break;
	}

	

	

failure:
	return 0;
}



int CReceiveChunk::ReadChunk(uint8_t* src, const int srcLength)
{
	CChunkHeader *pHeader = NULL;
	int headerLen = 0, dataLen = 0;
	bool newMsg = false;
	CChunkHeader::Head header;
	CBaseMessage *pMsg = NULL;


	//receive chunk head
	headerLen = ReadChunkHeader(src, srcLength,&pHeader);
	if (pHeader == NULL || headerLen == 0)
		goto failure;

	//receive chunk data
	dataLen = ReadChunkBody(pHeader, src + headerLen, srcLength - headerLen,&newMsg);
	if (dataLen <= 0)
		goto failure;

	//refersh
	RefreshHeader(pHeader);

	if (newMsg)
	{
		header = pHeader->GetHead();
		pMsg = CRtmpMessage::CreateMessage(header.csid, header.timestamp, header.messageLength, header.messageTypeID, header.messageStreamID);
		RefreshMessage(pMsg);
	}

	return (headerLen + dataLen);

failure:
	DELETE_PTR(pHeader)
		return 0;
}

int CReceiveChunk::ReadChunkHeader(uint8_t* src, const int srcLength, CChunkHeader **ppHeader)
{
	CChunkHeader *pHeader = NULL;
	CChunkHeader::Head header = { 0 };
	int headerLen = 0;

	if (src == NULL || srcLength == 0 || ppHeader == NULL)
		goto null_chunk;
	

	pHeader = CChunkHeader::Parse(src, srcLength, &headerLen);
	if (pHeader == NULL)
		goto null_chunk;
	pHeader->CopyFrom(m_ChunkHeader);

	*ppHeader = pHeader;
	return headerLen;
null_chunk:
	*ppHeader = NULL;
	return 0;
}

int CReceiveChunk::ReadChunkBody(CChunkHeader* pHeader, uint8_t* src, const int srcLen,bool *outNewMsg)
{
	const CChunkHeader::Head header = pHeader->GetHead();
	const uint32_t chunkSize = GetChunkSize();
	bool newMsg = false;
	int bodyLen = 0;

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

	if (newMsg == true)
		bodyLen = header.messageLength;
	else
		bodyLen = m_Message->GetRemainSize();

	bodyLen = bodyLen > chunkSize ? chunkSize : bodyLen;
	if (bodyLen > srcLen)
		goto failure;

	*outNewMsg = newMsg;
	return bodyLen;
failure:
	*outNewMsg = false;
	return 0;
}

void CReceiveChunk::RefreshMessage(CBaseMessage *pMsg)
{
	if (!pMsg)	return;
	DELETE_PTR(m_Message)
	m_Message = pMsg;
}

void CReceiveChunk::RefreshHeader(CChunkHeader *pHeader)
{
	if (!pHeader)	return;
	DELETE_PTR(pHeader)
	m_ChunkHeader = pHeader;
}

void CReceiveChunk::HandleMessage(CBaseMessage* pMsg)
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

void CReceiveChunk::HandleAbortMessage(CAbortMessage* pMsg)
{

}