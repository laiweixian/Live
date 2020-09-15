#pragma once
#include "../Receive/BaseMessage.h"

class CAcknowledgement
{
protected:
	CAcknowledgement();
	 ~CAcknowledgement();
public:
	struct Object { uint32_t sequenceNumber; };
	static Object* Decode(CBaseMessage* pMsg);
public:
	static uint8_t* TranslatePayload(uint32_t sequenceNumber, uint32_t* outLength);

};
