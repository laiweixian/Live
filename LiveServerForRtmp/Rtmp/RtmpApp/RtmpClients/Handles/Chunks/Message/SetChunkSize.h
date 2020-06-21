#pragma once
#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

class CSetChunkSize
{
protected:
	CSetChunkSize();
	virtual ~CSetChunkSize();
protected:
	virtual int HandleSetChunkSize(CBaseMessage* pMsg) final;
protected:
	virtual int SetChunkSize(uint32_t chunkSize) = 0;
};
