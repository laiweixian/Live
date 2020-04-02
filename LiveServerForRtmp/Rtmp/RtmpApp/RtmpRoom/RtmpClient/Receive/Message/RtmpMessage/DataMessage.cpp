#include "DataMessage.h"

CDataMessage::CDataMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(ts, msgLength, msgTypeId, msgStreamId)
{

}

CDataMessage::~CDataMessage()
{

}

RtmpMessageType CDataMessage::GetType()
{
	return RtmpMessageType::DATA_MESSAGE;
}

