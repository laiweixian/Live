#pragma once
#include "../Receive/BaseMessage.h"

class CAbortMessage
{
protected:
	CAbortMessage();
	virtual ~CAbortMessage();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
public:
	static uint8_t* TranslatePayload(uint32_t csid,uint32_t* outLength);
protected:
	virtual int AbortMessageHandle(uint32_t csid) = 0;
};