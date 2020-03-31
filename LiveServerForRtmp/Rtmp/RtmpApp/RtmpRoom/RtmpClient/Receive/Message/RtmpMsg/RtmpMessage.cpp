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

CBaseMsg* CRtmpMessage::CreateMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform)
{
	CBaseMsg* pMsg = NULL;

	switch (msgTypeId)
	{
	case SET_CHUNK_SIZE_TYPE_ID:
		pMsg = new CSetChunkSize(ts,msgLength,msgTypeId,msgStreamId,inform);
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
}