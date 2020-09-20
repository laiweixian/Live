#pragma once
#include "stdafx.h"
#include "../../Receive/BaseMessage.h"

#define E_T_SET_BUFFER_LENGTH ((uint16_t)3)

class CSetBufferLength
{
protected:
	CSetBufferLength();
	virtual ~CSetBufferLength();

public:
	struct Object { uint32_t streamID; uint32_t bufferLength; };
	static Object* Decode(CBaseMessage* pMsg);
	static void FreeObject(Object** ppObj);

	static uint8_t* TranslatePayload(Object obj, uint32_t *outLen);
};