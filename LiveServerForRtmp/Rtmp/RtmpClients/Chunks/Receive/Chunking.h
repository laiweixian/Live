#pragma once

#include "BaseMessage.h"

class CChunking 
{
protected:
	CChunking();
	~CChunking();
public:
	static uint8_t* Create(CBaseMessage* prev,CBaseMessage* cur,uint32_t chunkSize,uint32_t *outLength);
};

