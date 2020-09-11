 #pragma once
#include "BaseMessage.h"

class CReceiveChunk
{
protected:
	CReceiveChunk() ;
	virtual ~CReceiveChunk();

protected:
	CBaseMessage* Receive(uint8_t* src, const int srcLength,int *outChunkLength);
	int Abort(uint32_t csid);

protected:
	virtual uint32_t GetChunkSize() = 0;
	
private:
	CBaseMessage *m_Lastest;
};
