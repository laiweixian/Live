#pragma once
#include "../RtmpMessage/CommandMessage.h"

//Process ,when createStream done
//1.


class CPublishMission
{
public:
	struct Object {};

protected:
	CPublishMission();
	virtual ~CPublishMission();

protected:
	void Active();
	void InActive();
	int Continue();
	bool Complete();

	virtual int SendMessage(CBaseMessage* pMsg) = 0;
};
