#include "HandleMessage.h"

CHandleMessage::CHandleMessage()
{

}

CHandleMessage::~CHandleMessage()
{

}

int CHandleMessage::HandleMessage(CBaseMessage* pMsg)
{
	CChunkHeader::Head header;
	int ret = 0;

	header = pMsg->GetHead()->GetHead();
	switch (header.messageTypeID)
	{
	case SET_CHUNK_SIZE_TYPE_ID:	
		ret = CHandleSetChunkSize::Handle(pMsg);
		break;
	case ABORT_MESSAGE_TYPE_ID:	
		ret = CHandleAbortMessage::Handle(pMsg);
		break;
	case ACKNOWLEDGEMENT_TYPE_ID:	
		ret = CHandleAcknowledgement::Handle(pMsg);
		break;
	case WINDOW_ACKNOWLEDGEMENT_SIZE_TYPE_ID:
		ret = CHandleWindowAcknowledgementSize::Handle(pMsg);	
		break;
	case SET_PEER_BADNWIDTH_TYPE_ID:	
		ret = CHandleSetPeerBandwidth::Handle(pMsg);
		break;
	case USER_CONTROL_MESSAGES_TYPE_ID:	
		ret = CHandleUserControlMessages::Handle(pMsg);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF0:	
		ret = CHandleCommandMessage::Handle(pMsg);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF3:	
		ret = CHandleCommandMessage::Handle(pMsg);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF0:	
		ret = CHandleDataMessage::Handle(pMsg);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF3:	
		ret = CHandleDataMessage::Handle(pMsg);
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF0:
		ret = CHandleSharedObjectMessage::Handle(pMsg);
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF3:
		ret = CHandleSharedObjectMessage::Handle(pMsg);
		break;
	case AUDIO_MESSAGE_TYPE_ID:	
		ret = CHandleAudioMessage::Handle(pMsg);
		break;
	case VIDEO_MESSAGE_TYPE_ID:	
		ret = CHandleVideoMessage::Handle(pMsg);
		break;
	case AGGREGATE_MESSAGE_TYPE_ID:	
		ret = CHandleAggregateMessage::Handle(pMsg);
		break;
	default:
		break;
	}

	return ret ;
}