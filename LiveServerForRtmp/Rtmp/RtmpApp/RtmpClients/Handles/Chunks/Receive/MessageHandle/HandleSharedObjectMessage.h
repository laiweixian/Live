#pragma once

#include "../BaseMessage.h"


class CHandleSharedObjectMessage 
{
protected:
	CHandleSharedObjectMessage();
	virtual ~CHandleSharedObjectMessage() ;
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
};
