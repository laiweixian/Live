#pragma once

#include "stdafx.h"
#include "../../Receive/BaseMessage.h"

#define E_T_STREAM_BEGIN	((uint16_t)0)

class CStreamBegin
{
protected:
	CStreamBegin();
	~CStreamBegin();

public:
	struct Object { uint32_t streamID; };
	static Object* Decode(CBaseMessage* pMsg);
	static void FreeObject(Object** ppObj);

	static uint8_t* TranslatePayload(Object obj, uint32_t *outLen);


};
