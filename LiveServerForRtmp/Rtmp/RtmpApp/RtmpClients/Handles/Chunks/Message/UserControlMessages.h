#pragma once
#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

class CUserControlMessages
{
protected:
	CUserControlMessages();
	virtual ~CUserControlMessages();
protected:
	virtual int HandleUserControlMessages(CBaseMessage* pMsg) final;
};