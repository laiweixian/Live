#include "AggregateMessage.h"

CAggregateMessage::CAggregateMessage(uint32_t csid,uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) : 
	CBaseMessage(csid,ts, msgLength, msgTypeId, msgStreamId)
{

}

CAggregateMessage::~CAggregateMessage()
{

}

CBaseMessage::MessageType CAggregateMessage::GetType()
{
	return CBaseMessage::MessageType::AGGREGATE_MESSAGE;
}

