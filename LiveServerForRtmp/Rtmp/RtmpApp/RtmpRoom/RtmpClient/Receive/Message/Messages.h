#pragma once


#include "RtmpMessage/RtmpMessage.h"
#include "Chunk/Chunk.h"

class IMessageRespose
{
protected:
	~IMessageRespose() = default;
private:
	IMessageRespose() = default;

	virtual void SetChunkSize(uint32_t chunkSize) = 0;
	virtual void AbortMessage(uint32_t chunkStreamID) = 0;
	virtual void Acknowledgement(uint32_t sequenceNumber) = 0;
	virtual void WindowAcknowledgementSize(uint32_t acknowledgeWindowSize) = 0;
	virtual void SetPeerBandwidth(uint32_t acknowledgeWindowSize, uint8_t limitType) = 0;
	virtual void UserControlMessages(void* dst, const int dstLen) = 0;
	virtual void CommandMessage(void* dst, const int dstLen) = 0;
	virtual void DataMessage(void* dst, const int dstLen) = 0;
	virtual void SharedObjectMessage(void* dst, const int dstLen) = 0;
	virtual void AudioMessage(uint8_t* buff, const int buffLen) = 0;
	virtual void VideoMessage(uint8_t* buff, const int buffLen) = 0;
	virtual void AggregateMessage(void* dst, const int dstLen) = 0;
};

class CMessages 
{
public:
	CMessages(const int chunkSize = 128);
	~CMessages();


	int OnRtmpMessage(uint8_t* src, const int srcLength);
private:
	int ParseChunk(void* src, const int srcLength);

private:
	uint32_t m_ChunkSize;

	CChunkHeader *m_ChunkHeader;
	CBaseMessage *m_Message;
};
