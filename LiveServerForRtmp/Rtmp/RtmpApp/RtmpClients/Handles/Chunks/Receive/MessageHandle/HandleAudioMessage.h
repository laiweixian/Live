#pragma once
#include "../BaseMessage.h"


class CHandleAudioMessage 
{
protected:
	CHandleAudioMessage();
	virtual ~CHandleAudioMessage();

protected:
	virtual int Handle(CBaseMessage* pMsg) final;

protected:
	virtual int SetAudioMessage(CBaseMessage* pMsg) = 0;
};