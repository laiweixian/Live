#pragma once

#include "../BaseMessage.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"


class CHandleVideoMessage
{
protected:
	CHandleVideoMessage();
	virtual ~CHandleVideoMessage() ;

protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int SetVideoMessage(CRtmpMessage* pMsg) = 0;
};