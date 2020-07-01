#include "ReceiveMessage.h"

CReceiveMessage::CReceiveMessage()
{

}

CReceiveMessage::~CReceiveMessage()
{

}

int CReceiveMessage::HandleMessage(CBaseMessage* pMsg)
{
	CChunkHeader::Head header;
	int ret = 0;

	header = pMsg->GetHead()->GetHead();
	switch (header.messageTypeID)
	{
	case SET_CHUNK_SIZE_TYPE_ID:	
		ret = HandleSetChunkSize(pMsg);
		break;
	case ABORT_MESSAGE_TYPE_ID:	
		ret = HandleAbortMessage(pMsg);
		break;
	case ACKNOWLEDGEMENT_TYPE_ID:	
		ret = HandleAcknowledgement(pMsg);
		break;
	case WINDOW_ACKNOWLEDGEMENT_SIZE_TYPE_ID:
		ret = HandleWindowAcknowledgementSize(pMsg);	
		break;
	case SET_PEER_BADNWIDTH_TYPE_ID:	
		ret = HandleSetPeerBandwidth(pMsg);
		break;
	case USER_CONTROL_MESSAGES_TYPE_ID:	
		ret = HandleUserControlMessages(pMsg);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF0:	
		ret = HandleCommandMessage(pMsg);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF3:	
		ret = HandleCommandMessage(pMsg);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF0:	
		ret = HandleDataMessage(pMsg);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF3:	
		ret = HandleDataMessage(pMsg);
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF0:
		ret = HandleSharedObjectMessage(pMsg);	
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF3:
		ret = HandleSharedObjectMessage(pMsg);	
		break;
	case AUDIO_MESSAGE_TYPE_ID:	
		ret = HandleAudioMessage(pMsg);
		break;
	case VIDEO_MESSAGE_TYPE_ID:	
		ret = HandleVideoMessage(pMsg);
		break;
	case AGGREGATE_MESSAGE_TYPE_ID:	
		ret = HandleAggregateMessage(pMsg);
		break;
	default:
		break;
	}

	return ret ;
}