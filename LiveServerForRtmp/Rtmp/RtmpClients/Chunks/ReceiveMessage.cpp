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

	CSetChunkSize::Object *pObj0 = NULL;
	CAbortMessage::Object *pObj1 = NULL;
	CAcknowledgement::Object *pObj2 = NULL;
	CWindowAcknowledgementSize::Object *pObj3 = NULL;
	CSetPeerBandwidth::Object *pObj4 = NULL;
	CCommandMessage::Object *pObj6 = NULL;


	header = pMsg->GetHeader();
	switch (header.msgType)
	{
	case SET_CHUNK_SIZE_TYPE_ID:
		pObj0 = CSetChunkSize::Decode(pMsg);
		ret = SetChunkSizeHandle(pObj0);
		CSetChunkSize::FreeObject(&pObj0);
		break;
	case ABORT_MESSAGE_TYPE_ID:
		pObj1 = CAbortMessage::Decode(pMsg);
		ret = AbortMessageHandle(pObj1);
		CAbortMessage::FreeObject(&pObj1);
		break;
	case ACKNOWLEDGEMENT_TYPE_ID:
		pObj2 = CAcknowledgement::Decode(pMsg);
		ret = AcknowledgementHandle(pObj2);
		CAcknowledgement::FreeObject(&pObj2);
		break;
	case WINDOW_ACKNOWLEDGEMENT_SIZE_TYPE_ID:
		pObj3 = CWindowAcknowledgementSize::Decode(pMsg);
		ret = WindowAcknowledgementSizeHandle(pObj3);
		CWindowAcknowledgementSize::FreeObject(&pObj3);
		break;
	case SET_PEER_BADNWIDTH_TYPE_ID:
		pObj4 = CSetPeerBandwidth::Decode(pMsg);
		ret = SetPeerBandwidthHandle(pObj4);
		CSetPeerBandwidth::FreeObject(&pObj4);
		break;
	case USER_CONTROL_MESSAGES_TYPE_ID:
		
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF0:
		pObj6 = CCommandMessage::Decode(pMsg);
		ret = CommandMessageHandle(pObj6);
		CCommandMessage::FreeObject(&pObj6);
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

int CReceiveMessage::CommandMessageHandle(CCommandMessage::Object *pObj) 
{
	const CommandType cType = pObj->cType;
	CCommandConnect::Object* pObj0 = NULL;
	int ret = 0;
	
	switch (cType)
	{
	case NONE:
		break;

	case CONNECT:
		pObj0 = (CCommandConnect::Object*)pObj->pCmdObj;
		ret = CMConnectHandle(pObj0);
		break; 
	case CALL:
		break; 
	case CLOSE:
		break; 
	case CLOSE_STREAM:
		break; 
	case CREATE_STREAM:
		break;

	case PLAY:
		break; 
	case PLAY2:
		break; 
	case DELETE_STREAM:
		break; 
	case RECEIVE_AUDIO:
		break; 
	case RECEIVE_VIDEO:
		break; 
	case PUBLISH:
		break; 
	case SEEK:
		break; 
	case PAUSE:
		break;

	}

	return ret;
}
int CReceiveMessage::DataMessageHandle() { return -1; }
int CReceiveMessage::SetPeerBandwidthHandle(CSetPeerBandwidth::Object *pObj) { return -1; }
int CReceiveMessage::SharedObjectMessageHandle() { return -1; }
int CReceiveMessage::UserControlMessagesHandle() { return -1; }
int CReceiveMessage::VideoMessageHandle() { return -1; }
int CReceiveMessage::WindowAcknowledgementSizeHandle(CWindowAcknowledgementSize::Object  *pObj) { return -1; }

int CReceiveMessage::CMConnectHandle(CCommandConnect::Object *pObj)
{
	

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

