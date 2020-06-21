#pragma once

#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

class CVideoMessage
{
protected:
	CVideoMessage();
	virtual ~CVideoMessage() ;

protected:
	virtual int HandleVideoMessage(CBaseMessage* pMsg) final;
};