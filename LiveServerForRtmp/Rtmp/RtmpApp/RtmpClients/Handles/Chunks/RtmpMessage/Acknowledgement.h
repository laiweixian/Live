#pragma once
#include "../Receive/BaseMessage.h"

class CAcknowledgement
{
protected:
	CAcknowledgement();
	virtual ~CAcknowledgement();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int AcknowledgementHandle(uint32_t sequenceNumber) = 0;
};
