#pragma once
#include "../Receive/BaseMessage.h"


class CAggregateMessage 
{
protected:
	CAggregateMessage();
	virtual ~CAggregateMessage();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
public:
	static uint8_t* TranslatePayload(uint32_t sequenceNumber, uint32_t* outLength);
protected:
	virtual int AggregateMessageHandle(uint32_t sequenceNumber) = 0;
};