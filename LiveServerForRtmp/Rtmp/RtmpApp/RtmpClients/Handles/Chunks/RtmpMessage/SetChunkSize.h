#pragma once
#include "../Receive/BaseMessage.h"
class CSetChunkSize 
{
protected:
	CSetChunkSize();
	virtual ~CSetChunkSize();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int SetChunkSizeHandle(uint32_t chunkSize) = 0;
};
