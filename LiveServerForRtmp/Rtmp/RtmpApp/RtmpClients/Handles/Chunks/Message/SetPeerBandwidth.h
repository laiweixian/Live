#pragma once
#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

class CSetPeerBandwidth
{
protected:
	CSetPeerBandwidth();
	virtual ~CSetPeerBandwidth();
protected:
	virtual int HandleSetPeerBandwidth(CBaseMessage* pMsg) final;

};