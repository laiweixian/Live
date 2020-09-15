#pragma once

#include "../Receive/BaseMessage.h"


class CWindowAcknowledgementSize
{
protected:
	CWindowAcknowledgementSize();
	 ~CWindowAcknowledgementSize();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
	static uint8_t* TranslatePayload(uint32_t winAckSize, uint32_t* outLength);

public:
	struct Object { uint32_t winAckSize; };
	static Object* Decode(CBaseMessage* pMsg);
	static CBaseMessage* Encode(uint32_t timestamp,uint32_t msid, Object obj);
};