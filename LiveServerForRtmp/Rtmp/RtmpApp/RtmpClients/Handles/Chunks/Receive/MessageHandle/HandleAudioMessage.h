#pragma once
#include "../BaseMessage.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

class CHandleAudioMessage 
{
protected:
	CHandleAudioMessage();
	virtual ~CHandleAudioMessage();

protected:
	virtual int Handle(CBaseMessage* pMsg) final;

protected:
	virtual int SetAudioMessage(CRtmpMessage* pMsg) = 0;
};