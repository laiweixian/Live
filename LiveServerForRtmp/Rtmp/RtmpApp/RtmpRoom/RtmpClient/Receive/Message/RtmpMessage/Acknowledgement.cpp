#include "Acknowledgement.h"

CAcknowledgement::CAcknowledgement(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(ts, msgLength, msgTypeId, msgStreamId)
{

}

CAcknowledgement::~CAcknowledgement()
{

}

RtmpMessageType CAcknowledgement::GetType()
{
	return RtmpMessageType::ACKNOWLEDGEMENT;
}

