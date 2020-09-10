#pragma once

#include "stdafx.h"

#include "../Receive/BaseMessage.h"

class CSendMessage 
{
protected:
	CSendMessage();
	virtual ~CSendMessage();
protected:
	int Send(CBaseMessage* pSend);

protected:
	virtual uint32_t GetChunkSize() = 0;
	virtual int Send2Peer(uint8_t* src, const int srcLength) = 0;
private:
	CBaseMessage* prev;
};