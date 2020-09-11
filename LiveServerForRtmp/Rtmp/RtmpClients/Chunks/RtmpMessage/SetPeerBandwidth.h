#pragma once
#include "../Receive/BaseMessage.h"

class CSetPeerBandwidth 
{
protected:
	CSetPeerBandwidth();
	virtual ~CSetPeerBandwidth();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int SetPeerBandwidthHandle() = 0;
};