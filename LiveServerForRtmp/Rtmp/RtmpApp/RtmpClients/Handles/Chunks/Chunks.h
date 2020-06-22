#pragma once

#include "ReceChunk/ReceChunk.h"
#include "Message/RtmpMessage.h"

class CInstanceManager;

class CChunks : public CRtmpMessage,
				public CReceiveChunk
				
{
protected:
	CChunks(uint32_t chunkSize);
	virtual ~CChunks();
	
private:
	uint32_t GetChunkSize();
protected:
	int HandleMessage(CBaseMessage* pMsg);

	virtual CInstanceManager* GetRtmpInstance() = 0;
private:
	//receive message
	int SetAbortMessage(uint32_t csid);
	int SetSequenceNumber(uint32_t sequenceNumber);
	int SetWinAckSize(uint32_t winAckSize);
	int SetChunkSize(uint32_t chunkSize);
	int SetConnectCmd(const char* app,const char* instance);

	int SetAudioMessage(CBaseMessage* pMsg);
	int SetVideoMessage(CBaseMessage* pMsg);
private:

	uint32_t m_ChunkSize;
};
