#include "AggregateMessage.h"

CAggregateMessage::CAggregateMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform) :\
CBaseMsg(ts, msgLength, msgTypeId, msgStreamId, inform)
{

}

CAggregateMessage::~CAggregateMessage()
{

}

RtmpMessageType CAggregateMessage::GetType()
{
	return RtmpMessageType::AGGREGATE_MESSAGE;
}

void CAggregateMessage::Inform()
{

}