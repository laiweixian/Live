#pragma once

#include "BaseMsg.h"

class CSetPeerBandwidth : public CBaseMsg
{
public:
	CSetPeerBandwidth(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform);
	~CSetPeerBandwidth();

	//CBaseMsg
	RtmpMessageType GetType();
	void Inform();
};