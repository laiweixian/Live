#pragma once
#include "../BaseMessage.h"

class CHandleAcknowledgement
{
protected:
	CHandleAcknowledgement();
	virtual ~CHandleAcknowledgement();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int SetSequenceNumber(uint32_t sequenceNumber) = 0;
public:
	
};
