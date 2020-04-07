#include "SetPeerBandwidth.h"

CSetPeerBandwidth::CSetPeerBandwidth(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(ts, msgLength, msgTypeId, msgStreamId)
{

}

CSetPeerBandwidth::~CSetPeerBandwidth()
{

}

int CSetPeerBandwidth::GetProperty(uint32_t* pAcknowledgementWindowSize, uint8_t* pLimitType)
{
	uint32_t ackWinSize = 0;
	uint8_t limitType = 0;

	memcpy(&ackWinSize,m_Payload.buff,4);
	ackWinSize = ::BigToHost32(&ackWinSize);
	limitType = m_Payload.buff[4];

	*pAcknowledgementWindowSize = ackWinSize;
	*pLimitType = limitType;
	return SAR_OK;
}

RtmpMessageType CSetPeerBandwidth::GetType()
{
	return RtmpMessageType::SET_PEER_BADNWIDTH;
}

