#pragma once
#include "../Receive/BaseMessage.h"
class CSetChunkSize 
{
protected:
	CSetChunkSize();
	 ~CSetChunkSize();
public:
	struct Object { uint32_t chunkSize; };
	static Object* Decode(CBaseMessage* pMsg);
	static void FreeObject(Object** ppObj);
	static CBaseMessage* Encode(uint32_t timestamp, uint32_t msid, Object obj);
protected:
	static uint8_t* TranslatePayload(Object obj, uint32_t* outLength);
};
