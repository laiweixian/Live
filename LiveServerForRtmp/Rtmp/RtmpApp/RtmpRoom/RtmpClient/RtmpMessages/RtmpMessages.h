#pragma once

#include "stdafx.h"
#include "Rtmp/RtmpApp/RtmpRoom/RtmpClient/RtmpMessages/RtmpMessage/Chunk/chunk.h"
#include "Rtmp/RtmpApp/RtmpRoom/RtmpClient/RtmpMessages/RtmpMessage/RtmpMsg.h"

#define DEFAULT_CHUNK_SIZE 128

class CRtmpMessages
{
public:
	CRtmpMessages();
	~CRtmpMessages();

public:
	int OnReceive(char *buff, const int buffLen);

private:
	int DeMultiplexing(char *buff, const int buffLen);
	CChunk*  DeMultiplexingChunkHeader(char *buff, const int buffLen,int* outHeaderLen);
	int DeMultiplexingChunkData( CChunk* pChunk, char *buff, const int buffLen);

private:
	int HandMessage(CRtmpMsg *pMsg);

	//protocol control message
	int SetChunkSize(const uint8_t* buff,const int buffLen);
	int AbortMessage(const uint8_t* buff, const int buffLen);
	int Acknowledgement(const uint8_t* buff, const int buffLen);
	int WindowAcknowledgementSize(const uint8_t* buff, const int buffLen);
	int SetPeerBandwidth(const uint8_t* buff, const int buffLen);

	//user control messages
	int UserControlMessages(const uint8_t* buff, const int buffLen);
	
	int CommandMessage(const uint8_t msgTypeId, const uint8_t* buff, const int buffLen);
	int DataMessage(const uint8_t msgTypeId, const uint8_t* buff, const int buffLen);
	int SharedObjectdMessage(const uint8_t msgTypeId, const uint8_t* buff, const int buffLen);
	int AudioMessage(const uint8_t* buff, const int buffLen);
	int VideoMessage(const uint8_t* buff, const int buffLen);
	int AggregateMessage(const uint8_t* buff, const int buffLen);


private:
	vector<ChunkHeaderInfo> m_ChunkInfos;
	vector<CRtmpMsg*> m_Msgs;

private:
	uint32_t m_ChunkSize;
	uint32_t m_WindowAcknowledgementSize;

private:
	uint32_t m_ReceiveByteLength;
};


