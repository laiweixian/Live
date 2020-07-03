#pragma once
#include "../BaseMessage.h"

class CHandleSetPeerBandwidth 
{
protected:
	CHandleSetPeerBandwidth();
	virtual ~CHandleSetPeerBandwidth();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;

};