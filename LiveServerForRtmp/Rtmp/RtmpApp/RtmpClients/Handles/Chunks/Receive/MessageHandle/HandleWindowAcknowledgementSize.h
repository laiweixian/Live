#pragma once

#include "../BaseMessage.h"


class CHandleWindowAcknowledgementSize
{
protected:
	CHandleWindowAcknowledgementSize();
	virtual ~CHandleWindowAcknowledgementSize();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int SetWinAckSize(uint32_t winAckSize) = 0;
};