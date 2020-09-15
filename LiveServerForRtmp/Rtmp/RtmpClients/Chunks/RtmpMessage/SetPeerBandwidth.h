#pragma once
#include "../Receive/BaseMessage.h"

class CSetPeerBandwidth 
{
protected:
	CSetPeerBandwidth();
	~CSetPeerBandwidth();
public:
	struct Object { uint32_t ackWinSize; uint8_t limitType; };
	static Object* Decode(CBaseMessage* pMsg);
	
};