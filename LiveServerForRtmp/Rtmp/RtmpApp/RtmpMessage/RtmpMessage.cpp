#include "RtmpMessage.h"

CRtmpMessage::CRtmpMessage()
{

}

CRtmpMessage::~CRtmpMessage()
{

}

CBaseMessage* CRtmpMessage::CreateMessage(uint32_t csid,uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId)
{
	CBaseMessage* pMsg = NULL;

	switch (msgTypeId)
	{
	case SET_CHUNK_SIZE_TYPE_ID:
		pMsg = new CSetChunkSize(csid,ts,msgLength,msgTypeId,msgStreamId);
		break;
	case ABORT_MESSAGE_TYPE_ID:
		pMsg = new CAbortMessage(csid, ts,msgLength,msgTypeId,msgStreamId);
		break;
	case ACKNOWLEDGEMENT_TYPE_ID:
		pMsg = new CAcknowledgement(csid, ts,msgLength, msgTypeId, msgStreamId);
		break;
	case WINDOW_ACKNOWLEDGEMENT_SIZE_TYPE_ID:
		pMsg = new CWindowAcknowledgementSize(csid, ts,msgLength, msgTypeId, msgStreamId);
		break;
	case SET_PEER_BADNWIDTH_TYPE_ID:
		pMsg = new CSetPeerBandwidth(csid, ts,msgLength, msgTypeId, msgStreamId);
		break;
	case USER_CONTROL_MESSAGES_TYPE_ID:
		pMsg = new CUserControlMessages(csid, ts,msgLength, msgTypeId, msgStreamId);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF0:
		pMsg = new CCommandMessage(csid, ts,msgLength, msgTypeId, msgStreamId);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF3:
		pMsg = new CCommandMessage(csid, ts,msgLength, msgTypeId, msgStreamId);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF0:
		pMsg = new CDataMessage(csid, ts,msgLength, msgTypeId, msgStreamId);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF3:
		pMsg = new CDataMessage(csid, ts,msgLength, msgTypeId, msgStreamId);
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF0:
		pMsg = new CSharedObjectMessage(csid, ts,msgLength, msgTypeId, msgStreamId);
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF3:
		pMsg = new CSharedObjectMessage(csid, ts,msgLength, msgTypeId, msgStreamId);
		break;
	case AUDIO_MESSAGE_TYPE_ID:
		pMsg = new CAudioMessage(csid, ts,msgLength, msgTypeId, msgStreamId);
		break;
	case VIDEO_MESSAGE_TYPE_ID:
		pMsg = new CVideoMessage(csid, ts,msgLength, msgTypeId, msgStreamId);
		break;
	case AGGREGATE_MESSAGE_TYPE_ID:
		pMsg = new CAggregateMessage(csid, ts,msgLength, msgTypeId, msgStreamId);
		break;
	default:
		pMsg = NULL;
		break;
	}

	return pMsg;
}