#include "SendMessage.h"

CSendMessage::CSendMessage():m_ChunkSize(128),m_Prev(NULL)
{

}

CSendMessage::~CSendMessage()
{

}


int CSendMessage::Send2MySelf(CBaseMessage* pMsg)
{
	const uint32_t chunkSize = m_ChunkSize;
	uint32_t chunksLength = 0;
	uint8_t *chunks = NULL;
	CChunking *chunking = NULL;
	int length = 0;
	int ret = -1;
	char name[200] = {0};
	sprintf(name, "Send_Type_%d", pMsg->GetHeader().msgType);
	
	chunking = CChunking::Create(m_Prev,pMsg,chunkSize);
	chunks = chunking->GetChunksBuffer(&chunksLength);
	length = Send2Peer(chunks, chunksLength);
	if (length != chunksLength)
	{
		ret = -1;
	}
	else
	{
		if (m_Prev) m_Prev->Destroy();
		m_Prev = chunking;
		ret = 0;
		SendSuccess(pMsg);

		write2file(name, chunks, length);
	}

	TRACE("%s,%d\n", name,ret);
	return ret;
}

void CSendMessage::SendSuccess(CBaseMessage* pMsg)
{
	switch (pMsg->GetHeader().msgType)
	{
	case ACKNOWLEDGEMENT_TYPE_ID:
		OnSendAcknowledgement(pMsg);
		break;
	case WINDOW_ACKNOWLEDGEMENT_SIZE_TYPE_ID:
		OnSendWindowAcknowledgementSize(pMsg);
		break;
	case SET_PEER_BADNWIDTH_TYPE_ID:
		OnSendSetPeerBandwidth(pMsg);
		break;
	case USER_CONTROL_MESSAGES_TYPE_ID:
		OnSendUserControlMessages(pMsg);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF0:
		OnSendCommandMessage(pMsg);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF3:
		OnSendCommandMessage(pMsg);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF0:
		OnSendDataMessage(pMsg);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF3:
		OnSendDataMessage(pMsg);
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF0:
		OnSendSharedObjectMessage(pMsg);
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF3:
		OnSendSharedObjectMessage(pMsg);
		break;
	case AUDIO_MESSAGE_TYPE_ID:
		OnSendAudioMessage(pMsg);
		break;
	case VIDEO_MESSAGE_TYPE_ID:
		OnSendVideoMessage(pMsg);
		break;
	case AGGREGATE_MESSAGE_TYPE_ID:
		OnSendAggregateMessage(pMsg);
		break;
	default:
		break;
	}
}

void CSendMessage::OnSendAcknowledgement(CBaseMessage* pMsg)
{
	
}

void CSendMessage::OnSendAggregateMessage(CBaseMessage* pMsg)
{
	
}

void CSendMessage::OnSendAudioMessage(CBaseMessage* pMsg)
{

}

void CSendMessage::OnSendCommandMessage(CBaseMessage* pMsg)
{
	
}

void CSendMessage::OnSendAbortMessage(CBaseMessage* pMsg)
{

}

void CSendMessage::OnSendSetChunkSize(CBaseMessage* pMsg)
{

}

void CSendMessage::OnSendDataMessage(CBaseMessage* pMsg)
{
	
}

void CSendMessage::OnSendSetPeerBandwidth(CBaseMessage* pMsg)
{
	
}

void CSendMessage::OnSendSharedObjectMessage(CBaseMessage* pMsg)
{
	
}

void CSendMessage::OnSendUserControlMessages(CBaseMessage* pMsg)
{
	
}

void CSendMessage::OnSendVideoMessage(CBaseMessage* pMsg)
{
	
}

void CSendMessage::OnSendWindowAcknowledgementSize(CBaseMessage* pMsg)
{
	
}