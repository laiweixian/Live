#pragma once

#include "BaseMessage.h"

class CSetPeerBandwidth : public CBaseMessage
{
public:
	CSetPeerBandwidth(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CSetPeerBandwidth();

	//property
	int GetProperty(uint32_t* pAcknowledgementWindowSize,uint8_t* pLimitType);

	//CBaseMessage
	RtmpMessageType GetType();
	
};