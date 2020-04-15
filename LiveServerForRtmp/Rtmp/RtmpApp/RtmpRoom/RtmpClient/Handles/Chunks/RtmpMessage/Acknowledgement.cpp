#include "Acknowledgement.h"

CAcknowledgement::CAcknowledgement(uint32_t csid,uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(csid,ts, msgLength, msgTypeId, msgStreamId),m_Content({0})
{

}

CAcknowledgement::~CAcknowledgement()
{

}

CAcknowledgement::Content CAcknowledgement::GetContent()
{
	uint32_t sequenceNumber = 0;
	memcpy(&sequenceNumber,m_Payload.buff,4);
	
	m_Content.sequenceNumber = ::BigToHost32(&sequenceNumber);
	return m_Content;
}

CBaseMessage::MessageType CAcknowledgement::GetType()
{
	return CBaseMessage::MessageType::ACKNOWLEDGEMENT;
}

