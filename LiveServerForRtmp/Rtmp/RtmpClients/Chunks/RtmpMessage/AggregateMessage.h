#pragma once
#include "../Receive/BaseMessage.h"


class CAggregateMessage 
{
protected:
	CAggregateMessage();
	 ~CAggregateMessage();
public:
	struct Object { uint32_t sequenceNumber; };
	static Object* Decode(CBaseMessage* pMsg);
private:
	static uint8_t* TranslatePayload(uint32_t sequenceNumber, uint32_t* outLength);

};