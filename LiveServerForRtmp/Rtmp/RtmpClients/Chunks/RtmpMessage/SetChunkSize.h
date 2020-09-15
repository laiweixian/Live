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

protected:
	static uint8_t* TranslatePayload(uint32_t chunkSize, uint32_t* outLength);	
};
