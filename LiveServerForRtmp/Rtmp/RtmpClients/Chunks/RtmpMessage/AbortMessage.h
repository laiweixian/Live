#pragma once
#include "../Receive/BaseMessage.h"

class CAbortMessage
{
protected:
	CAbortMessage();
	 ~CAbortMessage();

public:
	struct Object { uint32_t csid; };
	static Object* Decode(CBaseMessage* pMsg);
	static void FreeObject(Object** ppObj);
private:
	static uint8_t* TranslatePayload(uint32_t csid,uint32_t* outLength);


};