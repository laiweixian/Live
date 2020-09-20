#pragma once


#include "stdafx.h"
#include "../../Receive/BaseMessage.h"

#define E_T_PING_RESPONSE ((uint16_t)7)

class CPingResponse
{
protected:
	CPingResponse();
	virtual ~CPingResponse();

public:
	struct Object { uint32_t timestamp; };
	static Object* Decode(CBaseMessage* pMsg);
	static void FreeObject(Object** ppObj);
	static uint8_t* TranslatePayload(Object obj, uint32_t *outLen);
};
