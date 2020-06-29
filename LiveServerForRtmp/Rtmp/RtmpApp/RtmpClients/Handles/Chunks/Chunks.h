#pragma once

#include "ReceChunk/ReceChunk.h"
#include "Message/RtmpMessage.h"

class CInstanceManager;

class CChunks : public CRtmpMessage,
				public CReceiveChunk
				
{
protected:
	CChunks(uint32_t chunkSize,CInstanceManager* appInstance);
	virtual ~CChunks();
	
private:
	uint32_t GetChunkSize();

private:
	int HandleMessage(CBaseMessage* pMsg);
	int SetAbortMessage(uint32_t csid);
	int SetSequenceNumber(uint32_t sequenceNumber);
	int SetWinAckSize(uint32_t winAckSize);
	int SetChunkSize(uint32_t chunkSize);
	int SetAudioMessage(CBaseMessage* pMsg);
	int SetVideoMessage(CBaseMessage* pMsg);

	//command message
	
private:
	CInstanceManager* m_AppInstance;
	uint32_t m_ChunkSize;
};
