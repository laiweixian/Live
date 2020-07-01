#pragma once

#include "ReceiveChunk.h"
#include "ReceiveMessage.h"

class CInstanceManager;
class CRtmpInstance;

class CChunks : public CReceiveChunk,
				public CReceiveMessage	
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
	int SetConnect(const char* rtmpurl);
	
private:
	CInstanceManager* m_InstanceManager;
	uint32_t m_ChunkSize;
	CRtmpInstance* m_Instance;
};
