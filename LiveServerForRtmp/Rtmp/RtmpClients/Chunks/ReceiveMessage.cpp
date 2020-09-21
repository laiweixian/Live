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

int CReceiveMessage::AcknowledgementHandle(CAcknowledgement::Object *pObj) 
{ 
	TRACE("Handle Acknowledgement\n");
	return -1; 
}

int CReceiveMessage::AggregateMessageHandle(CAggregateMessage::Object *pObj) 
{ 
	TRACE("Handle AggregateMessage\n");
	return -1; 
}

int CReceiveMessage::AudioMessageHandle() 
{ 
	TRACE("Handle AudioMessage\n");
	return -1; 
}

int CReceiveMessage::CommandMessageHandle(CCommandMessage::Object *pObj) 
{
	TRACE("Handle CommandMessage\n");
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

int CReceiveMessage::DataMessageHandle() 
{
	TRACE("Handle DataMessage\n");
	return -1; 
}

int CReceiveMessage::SetPeerBandwidthHandle(CSetPeerBandwidth::Object *pObj) 
{ 
	TRACE("Handle SetPeerBandwidth\n");
	return -1; 
}

int CReceiveMessage::SharedObjectMessageHandle() 
{ 
	TRACE("Handle SharedObjectMessage\n");
	return -1; 
}

int CReceiveMessage::UserControlMessagesHandle() 
{ 
	TRACE("Handle UserControlMessages\n");
	return -1; 
}

int CReceiveMessage::VideoMessageHandle() 
{ 
	TRACE("Handle VideoMessage\n");
	return -1; 
}

int CReceiveMessage::WindowAcknowledgementSizeHandle(CWindowAcknowledgementSize::Object  *pObj) 
{ 
	TRACE("Handle WindowAcknowledgementSize\n");
	return -1; 
}

int CReceiveMessage::CMConnectHandle(CCommandConnect::Object *pObj)
{
	TRACE("Handle CMConnect\n");
	int ret = -1;
	CConnectMission::Activate();
	CConnectMission::SetCommandConnect(pObj);
	ret = CConnectMission::Run();
	return ret;
}

int CReceiveMessage::CMCallHandle() 
{ 
	TRACE("Handle CMCall\n");
	return -1; 
}

int CReceiveMessage::CMCloseHandle() 
{ 
	TRACE("Handle CMClose\n");
	return -1; 
}

int CReceiveMessage::CMCloseStreamHandle() 
{ 
	TRACE("Handle CMCloseStream\n");
	return -1; 
}

int CReceiveMessage::CMCreateStreamHandle()
{ 
	TRACE("Handle CMCreateStream\n");
	return -1; 
}

int CReceiveMessage::CMPlayHandle() 
{ 
	TRACE("Handle CMPlay\n");
	return -1; 
}

int CReceiveMessage::CMPlay2Handle() 
{ 
	TRACE("Handle CMPlay2\n");
	return -1; 
}

int CReceiveMessage::CMDeleteStreamHandle() 
{ 
	TRACE("Handle CMDeleteStream\n");
	return -1; 
}

int CReceiveMessage::CMReceiveAudioHandle() 
{ 
	TRACE("Handle CMReceiveAudio\n");
	return -1; 
}

int CReceiveMessage::CMReceiveVideoHandle() 
{
	TRACE("Handle CMReceiveVideo\n");
	return -1; 
}

int CReceiveMessage::CMReceivePublishHandle() 
{ 
	TRACE("Handle CMReceivePublish\n");
	return -1;
}

int CReceiveMessage::CMSeekHandle() 
{ 
	TRACE("Handle CMSeek\n");
	return -1;
}

int CReceiveMessage::CMPauseHandle() 
{ 
	TRACE("Handle :CMPause\n");
	return -1; 
}

