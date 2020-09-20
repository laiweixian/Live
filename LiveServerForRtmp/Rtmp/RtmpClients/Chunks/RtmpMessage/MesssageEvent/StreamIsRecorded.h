#pragma once

#include "stdafx.h"
#include "../../Receive/BaseMessage.h"

#define E_T_STREAM_IS_RECORDED ((uint16_t)4)

class CStreamIsRecorded
{
protected:
	CStreamIsRecorded();
	virtual ~CStreamIsRecorded();

public:
	struct Object { uint32_t streamID; };

	static Object* Decode(CBaseMessage* pMsg);
	static void FreeObject(Object** ppObj);

	static uint8_t* TranslatePayload(Object obj, uint32_t *outLen);
};
