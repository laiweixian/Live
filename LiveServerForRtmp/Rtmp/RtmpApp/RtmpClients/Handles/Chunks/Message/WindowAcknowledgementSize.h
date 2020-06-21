#pragma once

#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

class CWindowAcknowledgementSize
{
protected:
	CWindowAcknowledgementSize();
	virtual ~CWindowAcknowledgementSize();
protected:
	virtual int HandleWindowAcknowledgementSize(CBaseMessage* pMsg) final;
};