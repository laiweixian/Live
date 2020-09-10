#include "Chunks.h"


#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}
	
CChunks::CChunks(uint32_t chunkSize,CInstanceManager* appInstance) : \
				 m_ChunkSize(chunkSize), m_InstanceManager(appInstance),m_Instance(NULL)
{

}

CChunks::~CChunks()
{
	
}

int CChunks::OnChunks(uint8_t* src, const int srcLength)
{
	CBaseMessage* msg = NULL;
	int totalLen = 0, chunkLen = 0;
	int result = 0;

	while (totalLen < srcLength)
	{
		msg = Receive(src + totalLen, srcLength, &chunkLen);
		if (msg == NULL)
			break;
		totalLen += chunkLen;
		result = HandleMessage(msg);
		if (result != 0)
			TRACE("RtmpMessage Handle Failure,result:%d,id:%d\n",result,msg->GetHead()->GetHead().messageTypeID);
	}
	return totalLen;
}

uint32_t CChunks::GetChunkSize()
{
	return m_ChunkSize;
}

int CChunks::HandleMessage(CBaseMessage* pMsg)
{
	CChunkHeader::Head header;
	int ret = 0;

	header = pMsg->GetHead()->GetHead();
	switch (header.messageTypeID)
	{
	case SET_CHUNK_SIZE_TYPE_ID:
		ret = CSetChunkSize::Handle(pMsg);
		break;
	case ABORT_MESSAGE_TYPE_ID:
		ret = CAbortMessage::Handle(pMsg);
		break;
	case ACKNOWLEDGEMENT_TYPE_ID:
		ret = CAcknowledgement::Handle(pMsg);
		break;
	case WINDOW_ACKNOWLEDGEMENT_SIZE_TYPE_ID:
		ret = CWindowAcknowledgementSize::Handle(pMsg);
		break;
	case SET_PEER_BADNWIDTH_TYPE_ID:
		ret = CSetPeerBandwidth::Handle(pMsg);
		break;
	case USER_CONTROL_MESSAGES_TYPE_ID:
		ret = CUserControlMessages::Handle(pMsg);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF0:
		ret = CCommandMessage::Handle(pMsg);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF3:
		ret = CCommandMessage::Handle(pMsg);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF0:
		ret = CDataMessage::Handle(pMsg);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF3:
		ret = CDataMessage::Handle(pMsg);
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF0:
		ret = CSharedObjectMessage::Handle(pMsg);
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF3:
		ret = CSharedObjectMessage::Handle(pMsg);
		break;
	case AUDIO_MESSAGE_TYPE_ID:
		ret = CAudioMessage::Handle(pMsg);
		break;
	case VIDEO_MESSAGE_TYPE_ID:
		ret = CVideoMessage::Handle(pMsg);
		break;
	case AGGREGATE_MESSAGE_TYPE_ID:
		ret = CAggregateMessage::Handle(pMsg);
		break;
	default:
		break;
	}

	return ret;
}

