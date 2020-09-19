#pragma once

#include "stdafx.h"
#include "../../Receive/BaseMessage.h"
#define E_T_STREAM_DRY	((uint16_t)2)

class CStreamDry
{
protected:
	CStreamDry();
	virtual ~CStreamDry();

public:
	struct Object { uint32_t streamID; };
	static Object* Decode(CBaseMessage* pMsg);
	static void FreeObject(Object** ppObj);
};