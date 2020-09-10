#pragma once
#include "../Receive/BaseMessage.h"


class CAggregateMessage 
{
protected:
	CAggregateMessage();
	virtual ~CAggregateMessage();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int AggregateMessageHandle(uint32_t sequenceNumber) = 0;
};