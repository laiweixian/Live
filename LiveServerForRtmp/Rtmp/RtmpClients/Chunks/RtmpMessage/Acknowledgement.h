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
	static void FreeObject(Object** ppObj);
	static CBaseMessage* Encode(uint32_t timestamp, uint32_t msid, Object obj);
private:
	static uint8_t* TranslatePayload(Object obj, uint32_t* outLength);

};
