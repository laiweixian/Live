#include "ReceiveMessage.h"


CReceiveMessage::CReceiveMessage()
{

}

CReceiveMessage::~CReceiveMessage()
{

}

int CReceiveMessage::HandleMessage(CBaseMessage* pMsg)
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

int CReceiveMessage::AcknowledgementHandle(CAcknowledgement::Object *pObj) { return -1; }
int CReceiveMessage::AggregateMessageHandle(CAggregateMessage::Object *pObj) { return -1; }
int CReceiveMessage::AudioMessageHandle() { return -1; }
int CReceiveMessage::CommandMessageHandle(CCommandMessage::Object *pObj) { return -1; }
int CReceiveMessage::DataMessageHandle() { return -1; }
int CReceiveMessage::SetPeerBandwidthHandle(CSetPeerBandwidth::Object *pObj) { return -1; }
int CReceiveMessage::SharedObjectMessageHandle() { return -1; }
int CReceiveMessage::UserControlMessagesHandle() { return -1; }
int CReceiveMessage::VideoMessageHandle() { return -1; }
int CReceiveMessage::WindowAcknowledgementSizeHandle(CWindowAcknowledgementSize::Object  *pObj) { return -1; }





int CReceiveMessage::CMConnectHandle(CCommandConnect *pCmd)
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
int CReceiveMessage::CMCallHandle() { return -1; }
int CReceiveMessage::CMCloseHandle() { return -1; }
int CReceiveMessage::CMCloseStreamHandle() { return -1; }
int CReceiveMessage::CMCreateStreamHandle() { return -1; }
int CReceiveMessage::CMPlayHandle() { return -1; }
int CReceiveMessage::CMPlay2Handle() { return -1; }
int CReceiveMessage::CMDeleteStreamHandle() { return -1; }
int CReceiveMessage::CMReceiveAudioHandle() { return -1; }
int CReceiveMessage::CMReceiveVideoHandle() { return -1; }
int CReceiveMessage::CMReceivePublishHandle() { return -1; }
int CReceiveMessage::CMSeekHandle() { return -1; }
int CReceiveMessage::CMPauseHandle() { return -1; }

