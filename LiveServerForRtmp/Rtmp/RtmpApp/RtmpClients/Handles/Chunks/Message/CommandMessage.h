#pragma once
#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

class CCommandMessage
{
protected:
	CCommandMessage();
	virtual ~CCommandMessage() ;

protected:
	virtual int HandleCommandMessage(CBaseMessage* pMsg) final;

};
