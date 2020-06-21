#pragma once
#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

class CAudioMessage
{
protected:
	CAudioMessage();
	virtual ~CAudioMessage();

protected:
	virtual int HandleAudioMessage(CBaseMessage* pMsg) final;
};