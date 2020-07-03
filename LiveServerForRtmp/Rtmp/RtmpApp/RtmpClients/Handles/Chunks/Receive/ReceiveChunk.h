 #pragma once
#include "BaseMessage.h"

class CReceiveChunk
{
protected:
	CReceiveChunk() ;
	virtual ~CReceiveChunk();

protected:
	virtual int OnChunks(uint8_t* src, const int srcLength) final;
private:
	int ReceiveMessage(uint8_t* src,const int srcLen);
protected:
	virtual uint32_t GetChunkSize() = 0;
	virtual int HandleMessage(CBaseMessage* pMsg) = 0;

protected:
	int AbortMessage(uint32_t csid);
private:
	CBaseMessage *m_Lastest;
};
