#pragma once

#include "stdafx.h"
#include "Rtmp/RtmpApp/RtmpRoom/RtmpClient/RtmpMessages/RtmpMessage/Chunk/chunk.h"
#include "Rtmp/RtmpApp/RtmpRoom/RtmpClient/RtmpMessages/RtmpMessage/RtmpMsg.h"



class CRtmpMessages
{
public:
	CRtmpMessages();
	~CRtmpMessages();

public:
	int OnReceive(char *buff, const int buffLen);

private:
	int DeMultiplexing(char *buff, const int buffLen);
	int DeMultiplexingChunkHeader(char *buff, const int buffLen);
	int DeMultiplexingChunkData( CChunk* pChunk, char *buff, const int buffLen);


private:
	vector<ChunkHeaderInfo> m_ChunkInfors;
	vector<CRtmpMsg*> m_Msgs;

private:
	int m_ChunkSize;
};