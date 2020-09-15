#include "HandleMessage.h"


CHandleMessage::CHandleMessage()
{

}

CHandleMessage::~CHandleMessage()
{

}

int CHandleMessage::HandleMessage(CBaseMessage* pMsg)
{
	CBaseMessage::Header header;
	int ret = 0;

	header = pMsg->GetHeader();
	switch (header.msgType)
	{
	case SET_CHUNK_SIZE_TYPE_ID:

		break;
	case ABORT_MESSAGE_TYPE_ID:

		break;
	case ACKNOWLEDGEMENT_TYPE_ID:

		break;
	case WINDOW_ACKNOWLEDGEMENT_SIZE_TYPE_ID:

		break;
	case SET_PEER_BADNWIDTH_TYPE_ID:

		break;
	case USER_CONTROL_MESSAGES_TYPE_ID:

		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF0:

		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF3:

		break;
	case DATA_MESSAGE_TYPE_ID_AMF0:

		break;
	case DATA_MESSAGE_TYPE_ID_AMF3:

		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF0:

		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF3:

		break;
	case AUDIO_MESSAGE_TYPE_ID:

		break;
	case VIDEO_MESSAGE_TYPE_ID:

		break;
	case AGGREGATE_MESSAGE_TYPE_ID:

		break;
	default:
		break;
	}

	return ret;
}

int CHandleMessage::AcknowledgementHandle(CAcknowledgement::Object *pObj) { return -1; }
int CHandleMessage::AggregateMessageHandle(CAggregateMessage::Object *pObj) { return -1; }
int CHandleMessage::AudioMessageHandle() { return -1; }
int CHandleMessage::CommandMessageHandle(CCommandMessage::Object *pObj) { return -1; }
int CHandleMessage::DataMessageHandle() { return -1; }
int CHandleMessage::SetPeerBandwidthHandle(CSetPeerBandwidth::Object *pObj) { return -1; }
int CHandleMessage::SharedObjectMessageHandle() { return -1; }
int CHandleMessage::UserControlMessagesHandle() { return -1; }
int CHandleMessage::VideoMessageHandle() { return -1; }
int CHandleMessage::WindowAcknowledgementSizeHandle(CWindowAcknowledgementSize::Object  *pObj) { return -1; }





int CHandleMessage::CMConnectHandle(CCommandConnect *pCmd)
{
	ConnectObject* obj = pCmd->GetObject();

	//Handle
	//1.(Send)Window Acknowledgement Size
	//2.(Send)Set Peer Bandwidth
	//3.(Receive)Window Acknowledgement Size 
	//4.(Send)User Control Message(StreamBegin) 
	//5.(Send)Command Message(_result- connect response)
	return -1;
}
int CHandleMessage::CMCallHandle() { return -1; }
int CHandleMessage::CMCloseHandle() { return -1; }
int CHandleMessage::CMCloseStreamHandle() { return -1; }
int CHandleMessage::CMCreateStreamHandle() { return -1; }
int CHandleMessage::CMPlayHandle() { return -1; }
int CHandleMessage::CMPlay2Handle() { return -1; }
int CHandleMessage::CMDeleteStreamHandle() { return -1; }
int CHandleMessage::CMReceiveAudioHandle() { return -1; }
int CHandleMessage::CMReceiveVideoHandle() { return -1; }
int CHandleMessage::CMReceivePublishHandle() { return -1; }
int CHandleMessage::CMSeekHandle() { return -1; }
int CHandleMessage::CMPauseHandle() { return -1; }

