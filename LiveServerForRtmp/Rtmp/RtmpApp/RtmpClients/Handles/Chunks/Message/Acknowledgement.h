#pragma once
#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

class CAcknowledgement
{
protected:
	CAcknowledgement();
	virtual ~CAcknowledgement();
protected:
	virtual int HandleAcknowledgement(CBaseMessage* pMsg) final;
protected:
	
};
