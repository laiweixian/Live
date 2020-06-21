#pragma once
#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

class CAggregateMessage
{
protected:
	CAggregateMessage();
	virtual ~CAggregateMessage();
protected:
	virtual int HandleAggregateMessage(CBaseMessage* pMsg) final;
protected:
};