#include "SetPeerBandwidth.h"

CSetPeerBandwidth::CSetPeerBandwidth(uint32_t csid,uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(csid,ts, msgLength, msgTypeId, msgStreamId)
{

}

CSetPeerBandwidth::~CSetPeerBandwidth()
{

}



CBaseMessage::MessageType CSetPeerBandwidth::GetType()
{
	return CBaseMessage::MessageType::SET_PEER_BADNWIDTH;
}

CSetPeerBandwidth::Content CSetPeerBandwidth::GetContent()
{
	uint32_t ackWinSize = 0;
	uint8_t limitType = 0;

	memcpy(&ackWinSize, m_Payload.buff, 4);
	ackWinSize = ::BigToHost32(&ackWinSize);
	limitType = m_Payload.buff[4];

	m_Content.acknowledgementWindowSize = ackWinSize;
	m_Content.limitType = limitType;
	return m_Content;
}

