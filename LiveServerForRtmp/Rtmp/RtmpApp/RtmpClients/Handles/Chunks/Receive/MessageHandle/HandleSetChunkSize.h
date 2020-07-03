#pragma once
#include "../BaseMessage.h"


class CHandleSetChunkSize 
{
protected:
	CHandleSetChunkSize();
	virtual ~CHandleSetChunkSize();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
protected:
	virtual int SetChunkSize(uint32_t chunkSize) = 0;
};
