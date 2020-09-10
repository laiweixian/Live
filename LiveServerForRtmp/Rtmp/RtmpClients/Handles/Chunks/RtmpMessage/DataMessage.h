#pragma once

#include "../Receive/BaseMessage.h"


class CDataMessage
{
protected:
	CDataMessage();
	virtual ~CDataMessage() ;
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int DataMessageHandle() = 0;

};
