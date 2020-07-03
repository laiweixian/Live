#pragma once
#include "../BaseMessage.h"


class CHandleAggregateMessage 
{
protected:
	CHandleAggregateMessage();
	virtual ~CHandleAggregateMessage();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
};