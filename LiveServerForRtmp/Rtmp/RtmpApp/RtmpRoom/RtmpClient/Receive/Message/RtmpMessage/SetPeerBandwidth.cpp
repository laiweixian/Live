#include "SetPeerBandwidth.h"

CSetPeerBandwidth::CSetPeerBandwidth(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(ts, msgLength, msgTypeId, msgStreamId)
{

}

CSetPeerBandwidth::~CSetPeerBandwidth()
{

}

RtmpMessageType CSetPeerBandwidth::GetType()
{
	return RtmpMessageType::SET_PEER_BADNWIDTH;
}

void CSetPeerBandwidth::Inform()
{

}