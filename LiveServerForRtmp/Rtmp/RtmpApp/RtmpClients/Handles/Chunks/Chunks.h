#pragma once

#include "Receive/ReceiveChunk.h"
#include "Receive/HandleMessage.h"
#include "Send/SendMessage.h"

class CInstanceManager;
class CRtmpInstance;

class CChunks : public CReceiveChunk,
				public CHandleMessage,
				public CSendMessage
		
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
	int SetAudioMessage(CRtmpMessage* pMsg);
	int SetVideoMessage(CRtmpMessage* pMsg);

	//command message
	int SetConnect(const char* rtmpurl, CRtmpMessage* response);
	
private:
	CInstanceManager* m_InstanceManager;
	uint32_t m_ChunkSize;
	CRtmpInstance* m_Instance;
};
