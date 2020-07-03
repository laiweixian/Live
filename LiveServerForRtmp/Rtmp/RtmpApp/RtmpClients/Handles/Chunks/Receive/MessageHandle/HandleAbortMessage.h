#pragma once
#include "../BaseMessage.h"


class CHandleAbortMessage
{
protected:
	CHandleAbortMessage();
	virtual ~CHandleAbortMessage();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int SetAbortMessage(uint32_t csid) = 0;
};