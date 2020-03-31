#pragma once
#include "BaseMsg.h"

class CSetChunkSize : public CBaseMsg
{
public:
	CSetChunkSize(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform);
	~CSetChunkSize();

	//CBaseMsg
	RtmpMessageType GetType();
	void Inform();
};