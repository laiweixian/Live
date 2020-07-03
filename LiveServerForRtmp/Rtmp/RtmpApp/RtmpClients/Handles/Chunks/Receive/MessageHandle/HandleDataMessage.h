#pragma once

#include "../BaseMessage.h"


class CHandleDataMessage
{
protected:
	CHandleDataMessage();
	virtual ~CHandleDataMessage() ;
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
};
