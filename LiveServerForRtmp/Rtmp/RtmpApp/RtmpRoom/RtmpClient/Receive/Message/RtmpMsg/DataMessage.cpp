#include "DataMessage.h"

CDataMessage::CDataMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform) :\
CBaseMsg(ts, msgLength, msgTypeId, msgStreamId, inform)
{

}

CDataMessage::~CDataMessage()
{

}

RtmpMessageType CDataMessage::GetType()
{
	return RtmpMessageType::DATA_MESSAGE;
}

void CDataMessage::Inform()
{

}