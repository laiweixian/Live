#pragma once

#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

class CSharedObjectMessage
{
protected:
	CSharedObjectMessage();
	virtual ~CSharedObjectMessage() ;
protected:
	virtual int HandleSharedObjectMessage(CBaseMessage* pMsg) final;
};
