#pragma once
#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

class CAbortMessage
{
protected:
	CAbortMessage();
	virtual ~CAbortMessage();
protected:
	virtual int HandleAbortMessage(CBaseMessage* pMsg) final;
protected:
	virtual int AbortMessage(uint32_t csid) = 0;
};