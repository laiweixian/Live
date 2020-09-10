#pragma once

#include "Receive/ReceiveChunk.h"
#include "Send/SendMessage.h"
#include "RtmpMessage/RtmpMessage.h"

class CInstanceManager;
class CRtmpInstance;

class CChunks : public CSendMessage,
				public CRtmpMessage,
				public CReceiveChunk
		
{
protected:
	CChunks(uint32_t chunkSize,CInstanceManager* appInstance);
	virtual ~CChunks();

protected:
	int OnChunks(uint8_t* src, const int srcLength);

private:
	uint32_t GetChunkSize();

	//处理RTMP协议的消息
private:
	int HandleMessage(CBaseMessage* pMsg);
	int AbortMessageHandle(uint32_t csid);
	int AcknowledgementHandle(uint32_t sequenceNumber);
	int AggregateMessageHandle(uint32_t sequenceNumber);
	int AudioMessageHandle();
	int CommandMessageHandle();
	int DataMessageHandle();
	int SetChunkSizeHandle(uint32_t chunkSize);
	int SetPeerBandwidthHandle();
	int SharedObjectMessageHandle();
	int UserControlMessagesHandle();
	int VideoMessageHandle();
	int WindowAcknowledgementSizeHandle(uint32_t winAckSize);
private:
	CInstanceManager* m_InstanceManager;
	uint32_t m_ChunkSize;
	CRtmpInstance* m_Instance;
};
