#include "Acknowledgement.h"

CAcknowledgement::CAcknowledgement(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(ts, msgLength, msgTypeId, msgStreamId)
{

}

CAcknowledgement::~CAcknowledgement()
{

}

int CAcknowledgement::GetProperty(uint32_t* pSequenceNumber)
{
	uint32_t sequenceNumber = 0;
	memcpy(&sequenceNumber,m_Payload.buff,4);
	
	*pSequenceNumber = ::BigToHost32(&sequenceNumber);
	return SAR_OK;
}

RtmpMessageType CAcknowledgement::GetType()
{
	return RtmpMessageType::ACKNOWLEDGEMENT;
}

