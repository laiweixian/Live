#pragma once
#include "../Receive/BaseMessage.h"
class CSetChunkSize 
{
protected:
	CSetChunkSize();
	virtual ~CSetChunkSize();
protected:
	virtual int Handle(CBaseMessage* pMsg) final;
public:
	static uint8_t* TranslatePayload(uint32_t chunkSize, uint32_t* outLength);
protected:
	virtual int SetChunkSizeHandle(uint32_t chunkSize) = 0;
};
