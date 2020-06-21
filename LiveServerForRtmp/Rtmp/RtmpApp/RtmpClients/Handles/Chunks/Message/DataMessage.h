#pragma once

#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

class CDataMessage
{
protected:
	CDataMessage();
	virtual ~CDataMessage() ;
protected:
	virtual int HandleDataMessage(CBaseMessage* pMsg) final;
};
