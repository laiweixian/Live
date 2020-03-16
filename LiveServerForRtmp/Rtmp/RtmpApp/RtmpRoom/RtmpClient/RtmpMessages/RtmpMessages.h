#pragma once

#include "stdafx.h"
#include "Rtmp/RtmpApp/RtmpRoom/RtmpClient/RtmpMessages/RtmpMessage/Chunk/chunk.h"
#include "Rtmp/RtmpApp/RtmpRoom/RtmpClient/RtmpMessages/RtmpMessage/RtmpMessage.h"

class CRtmpMessages
{
public:
	CRtmpMessages();
	~CRtmpMessages();

public:
	int OnReceive(char *buff, const int buffLen);

private:
	int DeMultiplexingChunk(char *buff, const int buffLen);
	


private:
	vector<CChunk*> m_Chunks;
	vector<CRtmpMessage*> m_Msgs;
	int m_ChunkSize;
	
};