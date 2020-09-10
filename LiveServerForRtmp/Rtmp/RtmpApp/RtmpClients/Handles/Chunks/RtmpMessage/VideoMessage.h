#pragma once

#include "../Receive/BaseMessage.h"

class CVideoMessage
{
protected:
	CVideoMessage();
	virtual ~CVideoMessage() ;
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int VideoMessageHandle() = 0;
};