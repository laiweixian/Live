#include "ReceChunk.h"

#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}

CReceiveChunk::CReceiveChunk() :m_Lastest(NULL)
{

}

CReceiveChunk::~CReceiveChunk()
{

}

int CReceiveChunk::OnChunks(uint8_t* src, const int srcLength)
{
	uint8_t buf[1024] = {0};
	int len = srcLength > 1024 ? 1024 : srcLength;

	memcpy(buf,src, len);
	return len;
	//return ReceiveMessage(src,srcLength);
}

int CReceiveChunk::ReceiveMessage(uint8_t* src, const int srcLen)
{
	const uint32_t chunkSize = GetChunkSize();
	CBaseMessage *pMsg = NULL;
	int chunkLen = 0;
	
	pMsg = CBaseMessage::Create(m_Lastest, chunkSize,src,srcLen,&chunkLen);
	if (pMsg == NULL && chunkLen == -1)
		return 0;
	
	if (pMsg)
	{
		if (m_Lastest) m_Lastest->Destroy();
		m_Lastest =  pMsg;
	}
	else
	{
		chunkLen = m_Lastest->AppendChunk(src,srcLen);
		if (chunkLen == 0)
			return 0;
	}

	if (m_Lastest->Full())
		HandleMessage(m_Lastest);
	
	if (srcLen > chunkLen)
		return (chunkLen+ReceiveMessage(src+chunkLen,srcLen-chunkLen));
	else 
		return chunkLen;
}

void CReceiveChunk::HandleMessage(CBaseMessage* pMsg)
{
	const uint8_t msgTypeId = pMsg->GetHead()->GetHead().messageTypeID;

	switch (msgTypeId)
	{
	case SET_CHUNK_SIZE_TYPE_ID:	
		HandleSetChunkSize(pMsg);
		break;
	case ABORT_MESSAGE_TYPE_ID:
		HandleAbortMessage(pMsg);
		break;
	case ACKNOWLEDGEMENT_TYPE_ID:
		HandleAcknowledgement(pMsg);
		break;
	case WINDOW_ACKNOWLEDGEMENT_SIZE_TYPE_ID:
		HandleWindowAcknowledgementSize(pMsg);
		break;
	case SET_PEER_BADNWIDTH_TYPE_ID:
		HandleSetPeerBandwidth(pMsg);
		break;
	case USER_CONTROL_MESSAGES_TYPE_ID:
		HandleUserControlMessages(pMsg);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF0:
		HandleCommandMessage(pMsg,false);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF3:
		HandleCommandMessage(pMsg,true);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF0:
		HandleDataMessage(pMsg,false);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF3:
		HandleDataMessage(pMsg,true);
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF0:
		HandleSharedObjectMessage(pMsg,false);
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF3:
		HandleSharedObjectMessage(pMsg,true);
		break;
	case AUDIO_MESSAGE_TYPE_ID:
		HandleAudioMessage(pMsg);
		break;
	case VIDEO_MESSAGE_TYPE_ID:
		HandleVideoMessage(pMsg);
		break;
	case AGGREGATE_MESSAGE_TYPE_ID:
		HandleAggregateMessage(pMsg);
		break;
	default:
		break;
	}
}

void CReceiveChunk::HandleAbortMessage(CBaseMessage* pMsg)
{

}