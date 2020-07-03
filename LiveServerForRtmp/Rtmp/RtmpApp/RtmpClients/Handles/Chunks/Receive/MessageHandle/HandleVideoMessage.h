#pragma once

#include "../BaseMessage.h"


class CHandleVideoMessage
{
protected:
	CHandleVideoMessage();
	virtual ~CHandleVideoMessage() ;

protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int SetVideoMessage(CBaseMessage* pMsg) = 0;
};