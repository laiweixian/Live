#pragma once

#include "ReceChunk/ReceChunk.h"
#include "Message/RtmpMessage.h"
#include "../../Player.h"
#include "../../Publisher.h"

class CChunks : public CRtmpMessage,
				public CReceiveChunk
				
{
protected:
	CChunks(string appName,uint32_t chunkSize);
	virtual ~CChunks();
	
private:
	uint32_t GetChunkSize();
protected:
	int HandleMessage(CBaseMessage* pMsg);

protected:
	int AbortMessage(uint32_t csid);
	int SetChunkSize(uint32_t chunkSize);

private:
	string m_Application;
	uint32_t m_ChunkSize;
};
