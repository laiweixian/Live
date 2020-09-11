#pragma once

#include "../Receive/BaseMessage.h"


class CWindowAcknowledgementSize
{
protected:
	CWindowAcknowledgementSize();
	virtual ~CWindowAcknowledgementSize();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int WindowAcknowledgementSizeHandle(uint32_t winAckSize) = 0;
};