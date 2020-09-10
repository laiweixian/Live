#pragma once

#include "../Receive/BaseMessage.h"


class CSharedObjectMessage 
{
protected:
	CSharedObjectMessage();
	virtual ~CSharedObjectMessage() ;
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int SharedObjectMessageHandle() = 0;
};
