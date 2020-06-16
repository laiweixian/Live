#pragma once

#include "BaseMessage.h"


/*-----------------------------------------------------------------------------------------*/
class CRtmpMessage
{
private:
	CRtmpMessage();
	~CRtmpMessage();
public:
	static CBaseMessage* CreateMessage(CBaseMessage* prev, uint32_t chunkSize, uint8_t *src, const uint32_t len, int *outLen);
};