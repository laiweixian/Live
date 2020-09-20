#pragma once

#include "stdafx.h"
#include "../../Receive/BaseMessage.h"

#define E_T_PING_REQUEST ((uint16_t)6)

class CPingRequest
{
protected:
	CPingRequest();
	virtual ~CPingRequest();

public:
	struct Object { uint32_t timestamp; };
	static Object* Decode(CBaseMessage* pMsg);
	static void FreeObject(Object** ppObj);
	static uint8_t* TranslatePayload(Object obj,uint32_t *outLen);
};
