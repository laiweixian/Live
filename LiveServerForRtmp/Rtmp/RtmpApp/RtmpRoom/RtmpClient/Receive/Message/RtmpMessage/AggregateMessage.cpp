#include "AggregateMessage.h"

CAggregateMessage::CAggregateMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) : CBaseMessage(ts, msgLength, msgTypeId, msgStreamId)
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