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


int CHandleMessage::AcknowledgementHandle(uint32_t sequenceNumber)
{
	TRACE("Handle Acknowledgement\n");
	return -1;
}

int CHandleMessage::AggregateMessageHandle(uint32_t sequenceNumber)
{
	TRACE("Handle AggregateMessage\n");
	return -1;
}

int CHandleMessage::AudioMessageHandle(CBaseMessage* pMsg)
{
	TRACE("Handle AudioMessage\n");
	return -1;
}

int CHandleMessage::CommandMessageHandle(CommandEnum cType, void *pCls)
{
	TRACE("Handle CommandMessage,Type:%d\n", cType);
	int ret = 0;

	switch (cType)
	{
	case CONNECT:
		ret = CMConnectHandle(static_cast<CCommandConnect*>(pCls));
		break;
	case CALL:
		ret = 1;
		break;
	case CLOSE:
		ret = 2;
		break;
	case CLOSE_STREAM:
		ret = 3;
		break;
	case CREATE_STREAM:
		ret = 4;
		break;

	case PLAY:
		ret = 5;
		break;
	case PLAY2:
		ret = 6;
		break;
	case DELETE_STREAM:
		ret = 7;
		break;
	case RECEIVE_AUDIO:
		ret = 8;
		break;
	case RECEIVE_VIDEO:
		ret = 9;
		break;
	case PUBLISH:
		ret = 10;
		break;
	case SEEK:
		ret = 11;
		break;
	case PAUSE:
		ret = 12;
		break;
	default:
		ret = -1;
		break;

	}

	return ret;
}

int CHandleMessage::DataMessageHandle()
{
	TRACE("Handle DataMessage\n");
	return -1;
}

int CHandleMessage::SetPeerBandwidthHandle()
{
	TRACE("Handle SetPeerBandwidth\n");
	return -1;
}

int CHandleMessage::SharedObjectMessageHandle()
{
	TRACE("Handle SharedObjectMessage\n");
	return -1;
}

int CHandleMessage::UserControlMessagesHandle()
{
	TRACE("Handle UserControlMessages\n");
	return -1;
}

int CHandleMessage::VideoMessageHandle()
{
	TRACE("Handle VideoMessage\n");
	return -1;
}

int CHandleMessage::WindowAcknowledgementSizeHandle(uint32_t winAckSize)
{
	TRACE("Handle WindowAcknowledgementSize\n");
	return -1;
}


int CHandleMessage::CMConnectHandle(CCommandConnect *pCmd)
{
	ConnectObject* obj = pCmd->GetObject();
	return -1;
}

int CHandleMessage::CMCallHandle()
{
	return -1;
}

int CHandleMessage::CMCloseHandle()
{
	return -1;
}

int CHandleMessage::CMCloseStreamHandle()
{
	return -1;
}

int CHandleMessage::CMCreateStreamHandle()
{
	return -1;
}

int CHandleMessage::CMPlayHandle()
{
	return -1;
}

int CHandleMessage::CMPlay2Handle()
{
	return -1;
}

int CHandleMessage::CMDeleteStreamHandle()
{
	return -1;
}

int CHandleMessage::CMReceiveAudioHandle()
{
	return -1;
}

int CHandleMessage::CMReceiveVideoHandle()
{
	return -1;
}

int CHandleMessage::CMReceivePublishHandle()
{
	return -1;
}

int CHandleMessage::CMSeekHandle()
{
	return -1;
}

int CHandleMessage::CMPauseHandle()
{
	return -1;
}