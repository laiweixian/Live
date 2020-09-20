#pragma once

#include "stdafx.h"
#include "../../Receive/BaseMessage.h"

#define E_T_STREAM_EOF	((uint16_t)1)

class CStreamEOF
{
protected:
	CStreamEOF();
	~CStreamEOF();

public:
	struct Object { uint32_t streamID; };
	static Object* Decode(CBaseMessage* pMsg);
	static void FreeObject(Object** ppObj);

	static uint8_t* TranslatePayload(Object obj, uint32_t *outLen);
};