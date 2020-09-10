#pragma once
#include "../Receive/BaseMessage.h"

class CAbortMessage
{
protected:
	CAbortMessage();
	virtual ~CAbortMessage();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int AbortMessageHandle(uint32_t csid) = 0;
};