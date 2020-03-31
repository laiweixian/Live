#include "RtmpMessage.h"

#define SET_CHUNK_SIZE_TYPE_ID				((uint8_t)1)
#define ABORT_MESSAGE_TYPE_ID				((uint8_t)2)
#define ACKNOWLEDGEMENT_TYPE_ID				((uint8_t)3)
#define WINDOW_ACKNOWLEDGEMENT_SIZE_TYPE_ID	((uint8_t)5)
#define SET_PEER_BADNWIDTH_TYPE_ID			((uint8_t)6)
#define USER_CONTROL_MESSAGES_TYPE_ID		((uint8_t)4)
#define COMMAND_MESSAGE_TYPE_ID_AMF0		((uint8_t)20)
#define COMMAND_MESSAGE_TYPE_ID_AMF3		((uint8_t)17)
#define DATA_MESSAGE_TYPE_ID_AMF0			((uint8_t)18)
#define DATA_MESSAGE_TYPE_ID_AMF3			((uint8_t)15)
#define SHARED_OBJECT_MESSAGE_TYPE_ID_AMF0	((uint8_t)19)
#define SHARED_OBJECT_MESSAGE_TYPE_ID_AMF3	((uint8_t)16)
#define AUDIO_MESSAGE_TYPE_ID				((uint8_t)8)
#define VIDEO_MESSAGE_TYPE_ID				((uint8_t)9)
#define AGGREGATE_MESSAGE_TYPE_ID			((uint8_t)22)

CRtmpMessage::CRtmpMessage()
{

}

CRtmpMessage::~CRtmpMessage()
{

}

CBaseMessage* CRtmpMessage::CreateMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform)
{
	CBaseMessage* pMsg = NULL;

	switch (msgTypeId)
	{
	case SET_CHUNK_SIZE_TYPE_ID:
		pMsg = new CSetChunkSize(ts,msgLength,msgTypeId,msgStreamId,inform);
		break;
	case ABORT_MESSAGE_TYPE_ID:
		pMsg = new CAbortMessage(ts,msgLength,msgTypeId,msgStreamId,inform);
		break;
	case ACKNOWLEDGEMENT_TYPE_ID:
		pMsg = new CAcknowledgement(ts, msgLength, msgTypeId, msgStreamId, inform);
		break;
	case WINDOW_ACKNOWLEDGEMENT_SIZE_TYPE_ID:
		pMsg = new CWindowAcknowledgementSize(ts, msgLength, msgTypeId, msgStreamId, inform);
		break;
	case SET_PEER_BADNWIDTH_TYPE_ID:
		pMsg = new CSetPeerBandwidth(ts, msgLength, msgTypeId, msgStreamId, inform);
		break;
	case USER_CONTROL_MESSAGES_TYPE_ID:
		pMsg = new CUserControlMessages(ts, msgLength, msgTypeId, msgStreamId, inform);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF0:
		pMsg = new CCommandMessage(ts, msgLength, msgTypeId, msgStreamId, inform);
		break;
	case COMMAND_MESSAGE_TYPE_ID_AMF3:
		pMsg = new CCommandMessage(ts, msgLength, msgTypeId, msgStreamId, inform);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF0:
		pMsg = new CDataMessage(ts, msgLength, msgTypeId, msgStreamId, inform);
		break;
	case DATA_MESSAGE_TYPE_ID_AMF3:
		pMsg = new CDataMessage(ts, msgLength, msgTypeId, msgStreamId, inform);
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF0:
		pMsg = new CSharedObjectMessage(ts, msgLength, msgTypeId, msgStreamId, inform);
		break;
	case SHARED_OBJECT_MESSAGE_TYPE_ID_AMF3:
		pMsg = new CSharedObjectMessage(ts, msgLength, msgTypeId, msgStreamId, inform);
		break;
	case AUDIO_MESSAGE_TYPE_ID:
		pMsg = new CAudioMessage(ts, msgLength, msgTypeId, msgStreamId, inform);
		break;
	case VIDEO_MESSAGE_TYPE_ID:
		pMsg = new CVideoMessage(ts, msgLength, msgTypeId, msgStreamId, inform);
		break;
	case AGGREGATE_MESSAGE_TYPE_ID:
		pMsg = new CAggregateMessage(ts, msgLength, msgTypeId, msgStreamId, inform);
		break;
	default:
		pMsg = NULL;
		break;
	}

	return pMsg;
}