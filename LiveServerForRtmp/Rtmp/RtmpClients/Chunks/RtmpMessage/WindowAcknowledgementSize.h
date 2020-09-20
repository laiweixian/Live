#pragma once

#include "../Receive/BaseMessage.h"


class CWindowAcknowledgementSize
{
protected:
	CWindowAcknowledgementSize();
	 ~CWindowAcknowledgementSize();


public:
	struct Object { uint32_t winAckSize; };
	static Object* Decode(CBaseMessage* pMsg);
	static CBaseMessage* Encode(uint32_t timestamp,uint32_t msid, Object obj);
	static void FreeObject(Object** ppObj);

private:
	static uint8_t* TranslatePayload(Object obj, uint32_t* outLength);
};