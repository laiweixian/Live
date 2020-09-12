#pragma once
#include "../Receive/BaseMessage.h"


class CAudioMessage 
{
protected:
	CAudioMessage();
	virtual ~CAudioMessage();

protected:
	virtual int Handle(CBaseMessage* pMsg) final;

protected:
	virtual int AudioMessageHandle(CBaseMessage* pMsg) = 0;
};